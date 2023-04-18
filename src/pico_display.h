#ifndef PDCD_PICO_DISPLAY_INCLUDED
#define PDCD_PICO_DISPLAY_INCLUDED

#include <stdbool.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "st7789_spi.h"

static const uint DEF_PIN_LED_R = 6;
static const uint DEF_PIN_LED_G = 7;
static const uint DEF_PIN_LED_B = 8;

static const uint DEF_PIN_BTN_A = 12;
static const uint DEF_PIN_BTN_B = 13;
static const uint DEF_PIN_BTN_X = 14;
static const uint DEF_PIN_BTN_Y = 15;

static const uint DEF_PIN_LCD_WR = 16;
static const uint DEF_PIN_LCD_CS = 17;
static const uint DEF_PIN_LCD_SCLK = 18;
static const uint DEF_PIN_LCD_MOSI = 19;
static const uint DEF_PIN_LCD_BL_EN = 20; // (ab)uses SPI0 RX

static const uint8_t DEF_LED_BRIGHTNESS = UINT8_MAX;
static const uint8_t DEF_LED_R = 0;
static const uint8_t DEF_LED_G = 0;
static const uint8_t DEF_LED_B = 0;

static const uint16_t LED_PWM_WRAP = 255 * 255;

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

  bool bl_enab;
  uint bl;
  spi_inst_t *spi;
  uint lcd_mosi;
  uint lcd_sclk;
  uint lcd_cs;
  uint lcd_wr;
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
  st7789_t lcd;
} pico_display_t;

pico_display_config_spi_t pico_display_get_default_config();

pico_display_t pico_display_init(pico_display_config_spi_t *config);

void pico_display_led_set_brightness(pico_display_t *display, uint8_t brightness);
void pico_display_led_set_rgb(pico_display_t *display, uint8_t red, uint8_t green, uint8_t blue);

void pico_display_lcd_update(pico_display_t *display, rgb565_frame_buffer_t frame_buffer);
void pico_display_lcd_set_backlight(pico_display_t *display, uint8_t brightness);

#endif