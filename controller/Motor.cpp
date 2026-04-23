#include "Motor.hpp"

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "hardware/regs/intctrl.h"
#include "hardware/sync.h"
#include "motorSpeed.pio.h"

#define PIO_BLOCK pio0

static Motor *inst = nullptr;

static void pioIrqHandler()
{
  inst->onMotionDone();
  irq_clear(PIO0_IRQ_0);
}

Motor::Motor(int stepPin, int dirPin)
  : stepPin(stepPin),
    dirPin(dirPin),
    stepPioMachine(pio_claim_unused_sm(PIO_BLOCK, true)),
    motionInProgress(false)
{
  inst = this;
  initMotorSpeedProgram(
    PIO_BLOCK,
    stepPioMachine,
    pio_add_program(PIO_BLOCK, &motorSpeed_program),
    stepPin
  );
  irq_set_exclusive_handler(PIO0_IRQ_0, pioIrqHandler);
  gpio_set_function(dirPin, GPIO_FUNC_SIO);
  gpio_set_dir(dirPin, GPIO_OUT);
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
  while (motionInProgress)
  {
    __wfe();
  }
}
