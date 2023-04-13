#include "pico_display.h"

#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "gamma.h"
#include "st7789_spi.h"

static void led_pwm_push(pico_display_led_t *led)
{
  uint16_t red = (UINT16_MAX - GAMMA_LUT_8[led->led_r] * led->brightness);
  uint16_t green = (UINT16_MAX - GAMMA_LUT_8[led->led_g] * led->brightness);
  uint16_t blue = (UINT16_MAX - GAMMA_LUT_8[led->led_b] * led->brightness);

  pwm_set_gpio_level(led->gpio_r, red);
  pwm_set_gpio_level(led->gpio_g, green);
  pwm_set_gpio_level(led->gpio_b, blue);
}

static void led_init(pico_display_config_spi_t *config, pico_display_t *disp)
{
  pico_display_led_t led;

  led.gpio_r = config->led_r;
  led.gpio_g = config->led_g;
  led.gpio_b = config->led_b;

  led.brightness = DEF_LED_BRIGHTNESS;
  led.led_r = DEF_LED_R;
  led.led_g = DEF_LED_G;
  led.led_b = DEF_LED_B;

  gpio_set_function(led.gpio_r, GPIO_FUNC_PWM);
  gpio_set_function(led.gpio_g, GPIO_FUNC_PWM);
  gpio_set_function(led.gpio_b, GPIO_FUNC_PWM);

  gpio_set_dir(led.gpio_r, GPIO_OUT);
  gpio_set_dir(led.gpio_g, GPIO_OUT);
  gpio_set_dir(led.gpio_b, GPIO_OUT);

  pwm_config pwm_conf = pwm_get_default_config();
  pwm_config_set_wrap(&pwm_conf, LED_PWM_WRAP);

  pwm_init(pwm_gpio_to_slice_num(led.gpio_r), &pwm_conf, true);
  pwm_init(pwm_gpio_to_slice_num(led.gpio_g), &pwm_conf, true);
  pwm_init(pwm_gpio_to_slice_num(led.gpio_b), &pwm_conf, true);

  led_pwm_push(&led);
  disp->led = led;
}

static void btn_init_single(uint gpio)
{
  gpio_set_function(gpio, GPIO_FUNC_SIO);
  gpio_set_dir(gpio, GPIO_IN);
  gpio_pull_up(gpio);
}

static void btn_init(pico_display_config_spi_t *config)
{
  btn_init_single(config->btn_a);
  btn_init_single(config->btn_b);
  btn_init_single(config->btn_x);
  btn_init_single(config->btn_y);
}

static void lcd_init(pico_display_config_spi_t *config, pico_display_t *disp)
{
  st7789_config_t conf = {
    .bl_enab = config->bl_enab,
    .pin_bl = config->bl,
    .pin_mosi = config->lcd_mosi,
    .pin_sclk = config->lcd_sclk,
    .pin_cs = config->lcd_cs,
    .pin_wr = config->lcd_wr,
  };

  st7789_t st7789 = st7789_init(&conf);
  disp->lcd = st7789;
}

pico_display_config_spi_t pico_display_get_default_config()
{
  pico_display_config_spi_t conf;

  conf.led_enab = true;
  conf.led_r = DEF_PIN_LED_R;
  conf.led_g = DEF_PIN_LED_G;
  conf.led_b = DEF_PIN_LED_B;

  conf.btn_enab = true;
  conf.btn_a = DEF_PIN_BTN_A;
  conf.btn_b = DEF_PIN_BTN_B;
  conf.btn_x = DEF_PIN_BTN_X;
  conf.btn_y = DEF_PIN_BTN_Y;

  conf.bl_enab = true;
  conf.bl = DEF_PIN_LCD_BL_EN;
  conf.lcd_mosi = DEF_PIN_LCD_MOSI;
  conf.lcd_sclk = DEF_PIN_LCD_SCLK;
  conf.lcd_cs = DEF_PIN_LCD_CS;
  conf.lcd_wr = DEF_PIN_LCD_WR;

  return conf;
}

pico_display_t pico_display_init(pico_display_config_spi_t *config)
{
  pico_display_t disp;

  if (config->led_enab)
  {
    led_init(config, &disp);
  }

  if (config->btn_enab)
  {
    btn_init(config);
  }

  lcd_init(config, &disp);

  return disp;
}

void pico_display_led_set_brightness(pico_display_t *display, uint8_t brightness)
{
  display->led.brightness = brightness;
  led_pwm_push(&display->led);
}

void pico_display_led_set_rgb(pico_display_t *display, uint8_t red, uint8_t green, uint8_t blue)
{
  display->led.led_r = red;
  display->led.led_g = green;
  display->led.led_b = blue;
  led_pwm_push(&display->led);
}