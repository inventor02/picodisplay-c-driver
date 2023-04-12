#pragma once

#include <stdbool.h>

#include "pico/stdlib.h"

static const uint DEF_PIN_LED_R = 9;
static const uint DEF_PIN_LED_G = 10;
static const uint DEF_PIN_LED_B = 11;

static const uint DEF_PIN_BTN_A = 16;
static const uint DEF_PIN_BTN_B = 19;
static const uint DEF_PIN_BTN_X = 19;
static const uint DEF_PIN_BTN_Y = 20;

static const uint DEF_PIN_BL_EN = 26;
static const uint DEF_PIN_LCD_MOSI = 25;
static const uint DEF_PIN_LCD_SCLK = 24;
static const uint DEF_PIN_LCD_CS = 22;
static const uint DEF_PIN_LCD_DC = 21;

typedef struct pico_display_config_spi
{
  bool led_enab;
  uint led_r;
  uint led_g;
  uint led_b;

  bool btn_enab;
  uint btn_a;
  uint btn_b;
  uint btn_x;
  uint btn_y;

  uint bl_en;
  uint lcd_mosi;
  uint lcd_sclk;
  uint lcd_cs;
  uint lcd_dc;
} pico_display_config_spi_t;

pico_display_config_spi_t pico_display_get_default_config();
