#include "Servo.hpp"

#include "hardware/gpio.h"
#include "hardware/pwm.h"

Servo::Servo(int pin, float servoOverOutRatio)
  : pin(pin),
    gearRatio(servoOverOutRatio)
{
  gpio_set_function(pin, GPIO_FUNC_PWM);
  pwm_config config = pwm_get_default_config();
  pwm_init(pwm_gpio_to_slice_num(pin), true);
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
  pwm_set_gpio_level(pin, (uint16_t)(0.05 * (angle * gearRatio / 180 + 1) * 0xffff));
}
