#include "Motor.hpp"

#include "motorSpeed.pio.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "hardware/regs/intctrl.h"
#include "hardware/sync.h"

#define PIO_BLOCK pio0

static Motor *inst = nullptr;

static void pioIrqHandler()
{
  inst->onMotionDone();
  irq_clear(PIO0_IRQ_0);
  pio_interrupt_clear(PIO_BLOCK, 0);
}

Motor::Motor(int stepPin, int dirPin)
  : stepPin(stepPin),
    dirPin(dirPin),
    stepPioMachine(pio_claim_unused_sm(PIO_BLOCK, true)),
    motionInProgress(false),
    flagLock(spin_lock_instance(spin_lock_claim_unused(true)))
{
  inst = this;
  initMotorSpeedProgram(
    PIO_BLOCK,
    stepPioMachine,
    pio_add_program(PIO_BLOCK, &motorSpeed_program),
    stepPin,
    pioIrqHandler
  );
  gpio_set_function(dirPin, GPIO_FUNC_SIO);
  gpio_set_dir(dirPin, GPIO_OUT);
  setDirection(true);
}

void Motor::onMotionDone()
{
  motionInProgress = false;
  __sev();
}

void Motor::move(unsigned int ticks, unsigned int hz)
{
  motionInProgress = true;
  beginMotorMotion(PIO_BLOCK, stepPioMachine, ticks, hz);
}

void Motor::setDirection(bool forward)
{
  gpio_put(dirPin, forward);
}

void Motor::wait()
{
  __sev(); // Prevent race?
  while (motionInProgress)
  {
    __wfe();
  }
}
