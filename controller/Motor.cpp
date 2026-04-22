#include "Motor.hpp"

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "hardware/regs/intctrl.h"
#include "hardware/sync.h"

static Motor *inst = nullptr;

static void globalOnIrqWrap()
{
  inst->onIrqWrap();
}

Motor::Motor(int stepPin, int dirPin)
  : stepPin(stepPin),
    dirPin(dirPin),
    stepSlice(pwm_gpio_to_slice_num((unsigned int)stepPin)),
    stepChannel(pwm_gpio_to_channel((unsigned int)stepPin)),
    remTicks(0)
{
  inst = this;
  gpio_set_function(stepPin, GPIO_FUNC_PWM);
  pwm_set_clkdiv(stepSlice, 62.5f);
  pwm_set_wrap(stepSlice, 20000);
  pwm_set_chan_level(stepSlice, stepChannel, 5);
  pwm_set_enabled(stepSlice, false);
  pwm_set_irq_enabled(stepSlice, true);
  irq_set_exclusive_handler(PWM_IRQ_WRAP, globalOnIrqWrap);
}

void Motor::onIrqWrap()
{
  if (--remTicks <= 0)
  {
    pwm_set_irq_enabled(stepSlice, false);
    remTicks = 0;
    __sev();
  }
}

void Motor::move(int ticks, int hz)
{
  remTicks = ticks;
  pwm_set_wrap(stepSlice, (int)(2000000.0f / hz));
  pwm_set_enabled(stepSlice, true);
}

void Motor::wait()
{
  while (remTicks)
  {
    __wfe();
  }
}
