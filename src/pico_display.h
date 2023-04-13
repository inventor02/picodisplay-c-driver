#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"

static const uint DEF_PIN_LED_R = 6;
static const uint DEF_PIN_LED_G = 7;
static const uint DEF_PIN_LED_B = 8;

static const uint DEF_PIN_BTN_A = 12;
static const uint DEF_PIN_BTN_B = 13;
static const uint DEF_PIN_BTN_X = 14;
static const uint DEF_PIN_BTN_Y = 15;

static const uint DEF_PIN_BL_EN = 20;
static const uint DEF_PIN_LCD_MOSI = 19;
static const uint DEF_PIN_LCD_SCLK = 18;
static const uint DEF_PIN_LCD_CS = 17;
static const uint DEF_PIN_LCD_DC = 16;

static const uint8_t DEF_LED_BRIGHTNESS = UINT8_MAX;
static const uint8_t DEF_LED_R = 0;
static const uint8_t DEF_LED_G = 0;
static const uint8_t DEF_LED_B = 0;

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

typedef struct pico_display_led
{
  uint gpio_r;
  uint gpio_g;
  uint gpio_b;

  uint8_t brightness;
  uint8_t led_r;
  uint8_t led_g;
  uint8_t led_b;
} pico_display_led_t;

typedef struct pico_display
{
  pico_display_led_t led;
} pico_display_t;

pico_display_config_spi_t pico_display_get_default_config();

pico_display_t pico_display_init(pico_display_config_spi_t *config);

void pico_display_led_set_brightness(pico_display_t *display, uint8_t brightness);
void pico_display_led_set_rgb(pico_display_t *display, uint8_t red, uint8_t green, uint8_t blue);