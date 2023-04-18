#include "st7789_spi.h"

#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"

#include "gamma.h"

static void st7789_command(st7789_t *st7789, st7789_cmd_t command, uint8_t *data, size_t data_len)
{
  gpio_put(st7789->pin_wr, 0);
  gpio_put(st7789->pin_cs, 0);

  spi_write_blocking(st7789->spi, ((uint8_t *) &command), 1);

  if (data && data_len > 0)
  {
    gpio_put(st7789->pin_wr, 1);
    spi_write_blocking(st7789->spi, data, data_len);
  }

  gpio_put(st7789->pin_cs, 1);
  gpio_put(st7789->pin_wr, 0);
}

static void st7789_spi_init(st7789_t *st7789)
{
  spi_init(st7789->spi, ST7789_BAUD);

  gpio_set_function(st7789->pin_sclk, GPIO_FUNC_SPI);
  gpio_set_function(st7789->pin_mosi, GPIO_FUNC_SPI);
}

static void st7789_sio_init(st7789_t *st7789)
{
  gpio_init(st7789->pin_cs);
  gpio_init(st7789->pin_wr);

  gpio_set_function(st7789->pin_cs, GPIO_FUNC_SIO);
  gpio_set_function(st7789->pin_wr, GPIO_FUNC_SIO);

  gpio_set_dir(st7789->pin_cs, GPIO_OUT);
  gpio_set_dir(st7789->pin_wr, GPIO_OUT);

  gpio_put(st7789->pin_cs, 1);
  gpio_put(st7789->pin_wr, 1);
}

static void st7789_pwm_bl_push(st7789_t *st7789)
{
  pwm_set_gpio_level(st7789->pin_bl, ((uint16_t) ST7789_GAMMA_LUT_8[st7789->bl_brightness]) * ST7789_BL_PWM_WRAP);
}

static void st7789_pwm_init(st7789_t *st7789)
{
  gpio_set_function(st7789->pin_bl, GPIO_FUNC_PWM);
  gpio_set_dir(st7789->pin_bl, GPIO_OUT);
  gpio_pull_down(st7789->pin_bl);

  pwm_config pwm_conf = pwm_get_default_config();
  pwm_config_set_wrap(&pwm_conf, ST7789_BL_PWM_WRAP);

  pwm_init(pwm_gpio_to_slice_num(st7789->pin_bl), &pwm_conf, true);
  st7789_pwm_bl_push(st7789);
}

st7789_t st7789_init(st7789_config_t *config)
{
  st7789_t st7789;

  st7789.spi = config->spi;
  st7789.pin_cs = config->pin_cs;
  st7789.pin_wr = config->pin_wr;
  st7789.pin_mosi = config->pin_mosi;
  st7789.pin_sclk = config->pin_sclk;

  st7789.bl_enab = config->bl_enab;
  st7789.pin_bl = config->pin_bl;
  st7789.bl_brightness = ST7789_DEF_BL_BRIGHTNESS;

  st7789_spi_init(&st7789);
  st7789_sio_init(&st7789);

  if (st7789.bl_enab)
  {
    st7789_pwm_init(&st7789);
  }

  st7789_command(&st7789, SWRESET, NULL, 0);

  sleep_ms(150);
  
  st7789_command(&st7789, TEON, NULL, 0);
  st7789_command(&st7789, COLMOD, "\x05", 1);

  sleep_ms(50);

  st7789_command(&st7789, INVON, NULL, 0);
  st7789_command(&st7789, SLPOUT, NULL, 0);
  st7789_command(&st7789, DISPON, NULL, 0);

  sleep_ms(50);

  uint16_t caset_xs = 52;
  uint16_t caset_xe = 186;
  uint8_t caset[4] = {
    (caset_xs & 0xff00) >> 8,
    caset_xs & 0x00ff,
    (caset_xe & 0xff00) >> 8,
    caset_xe & 0x00ff
  };

  uint16_t raset_ys = 40;
  uint16_t raset_ye = 279;
  uint8_t raset[4] = {
    (raset_ys & 0xff00) >> 8,
    raset_ys & 0x00ff,
    (raset_ye & 0xff00) >> 8,
    raset_ye & 0x00ff
  };
  uint8_t madctl = 0;

  st7789_command(&st7789, CASET, caset, 4);
  st7789_command(&st7789, RASET, raset, 4);
  st7789_command(&st7789, MADCTL, &madctl, 1);

  sleep_ms(150);

  return st7789;
}

void st7789_set_backlight(st7789_t *st7789, uint8_t backlight)
{
  st7789->bl_brightness = backlight;
  st7789_pwm_bl_push(st7789);
}

void st7789_set_display(st7789_t *st7789, rgb565_frame_buffer_t buffer)
{
  st7789_command(st7789, RAMWR, (uint8_t *) buffer, ST7789_FB_SIZE * sizeof(uint16_t));
}
