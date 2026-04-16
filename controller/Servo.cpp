#include "Servo.hpp"

#include <stdio.h>
#include "pico/stdio.h"
#include "pico/time.h"

#include "hardware/gpio.h"
#include "hardware/pwm.h"

Servo::Servo(int pin, float servoOverOutRatio)
  : pin(pin),
    gearRatio(servoOverOutRatio),
    slice(pwm_gpio_to_slice_num((unsigned int)pin)),
    channel(pwm_gpio_to_channel((unsigned int)pin))
{
  gpio_set_function(pin, GPIO_FUNC_PWM);
  pwm_set_clkdiv(slice, 125.0f);
  pwm_set_wrap(slice, 20000);
  pwm_set_chan_level(slice, channel, 0);
  pwm_set_enabled(slice, true);
  move(0);
}

void Servo::move(float angle)
{
  // outputAngle * servoOverOutRatio = servoAngle
  // 0deg -> 1/20 on
  // 180deg -> 2/20 on
  // servoAngle / 180 = frac
  // 1/20 * (frac + 1) = dutyFrac
  // floor(dutyFrac * 0xffff) = level
  uint16_t level = (uint16_t)(600 + angle * gearRatio / 180.0f * 2300);
  pwm_set_chan_level(slice, channel, level);
}
