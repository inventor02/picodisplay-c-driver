#include "st7789_spi.h"

#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"

#include "gamma.h"

void init_spi(st7789_t *st7789)
{
  gpio_set_function(st7789->pin_sck, GPIO_FUNC_SPI);
  gpio_set_function(st7789->pin_mosi, GPIO_FUNC_SPI);

  spi_init(st7789->spi, ST7789_BAUD);
}

void sio_init(st7789_t *st7789)
{
  gpio_set_function(st7789->pin_cs, GPIO_FUNC_SIO);
  gpio_set_function(st7789->pin_dc, GPIO_FUNC_SIO);

  gpio_set_dir(st7789->pin_cs, GPIO_OUT);
  gpio_set_dir(st7789->pin_dc, GPIO_OUT);

  gpio_pull_up(st7789->pin_cs);
  gpio_pull_down(st7789->pin_dc);
}

void pwm_init(st7789_t *st7789)
{
  gpio_set_function(st7789->pin_bl, GPIO_FUNC_PWM);
  gpio_pull_down(st7789->pin_bl);

  pwm_config pwm_conf = pwm_get_default_config();
  pwm_config_set_wrap(&pwm_conf, ST7789_BL_PWM_WRAP);

  pwm_init(pwm_gpio_to_slice_num(st7789->pin_bl), &pwm_conf, true);
  pwm_bl_push(&st7789);
}

void pwm_bl_push(st7789_t *st7789)
{
  pwm_set_gpio_level(st7789->pin_bl, ((uint16_t) ST7789_GAMMA_LUT_8[st7789->bl_brightness]) * ST7789_BL_PWM_WRAP);
}

st7789_t st7789_init(st7789_config_t *config)
{
  st7789_t st7789;

  st7789.spi = config->spi;
  st7789.pin_cs = config->pin_cs;
  st7789.pin_dc = config->pin_dc;
  st7789.pin_mosi = config->pin_mosi;
  st7789.pin_sck = config->pin_sck;

  st7789.bl_enab = config->pin_bl;
  st7789.bl_brightness = ST7789_DEF_BL_BRIGHTNESS;

  init_spi(&st7789);
  init_sio(&st7789);

  if (st7789.bl_enab)
  {
    init_pwm(&st7789);
  }

  return st7789;
}

void st7789_set_backlight(st7789_t *st7789, uint8_t backlight)
{
  st7789->bl_brightness = backlight;
  pwm_bl_push(&st7789);
}
