#include "pico_display.h"

#include <stdbool.h>

#include "pico/stdlib.h"

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

  conf.bl_en = DEF_PIN_BL_EN;
  conf.lcd_mosi = DEF_PIN_LCD_MOSI;
  conf.lcd_sclk = DEF_PIN_LCD_SCLK;
  conf.lcd_cs = DEF_PIN_LCD_CS;
  conf.lcd_dc = DEF_PIN_LCD_DC;

  return conf;
}