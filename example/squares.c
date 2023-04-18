#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"

#include "pico_display.h"
#include "st7789_spi.h"

static rgb565_frame_buffer_t buffer;

static uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b)
{
  uint16_t r5 = (r & 0b11111000) << 11;
  uint16_t g6 = (g & 0b11111100) << 3;
  uint16_t b5 = (b & 0b11111000) >> 3;

  return r5 | g6 | b5;
}

static void swap(void *p1, void *p2)
{
  void *tmp = p1;
  p1 = p2;
  p2 = tmp;
}

void main()
{
  pico_display_config_spi_t config = pico_display_get_default_config();
  pico_display_t display = pico_display_init(&config);

  for (int i = 0; i < ST7789_FB_SIZE; i++) buffer[i] = 0;
  pico_display_lcd_update(&display, buffer);
  pico_display_lcd_set_backlight(&display, 255);

  while (true)
  {
    uint16_t x1 = rand() % ST7789_WIDTH;
    uint16_t x2 = rand() % ST7789_WIDTH;
    uint16_t y1 = rand() % ST7789_HEIGHT;
    uint16_t y2 = rand() % ST7789_HEIGHT;

    if (x1 > x2) swap(&x1, &x2);
    if (y1 > y2) swap(&y1, &y2);

    uint8_t r = rand() % 255;
    uint8_t g = rand() % 255;
    uint8_t b = rand() % 255;

    for (int x = x1; x <= x2; x++)
    {
      for (int y = y1; y <= y2; y++)
      {
        buffer[y * ST7789_WIDTH + x] = rgb565(r, g, b);
      }
    }

    pico_display_lcd_update(&display, buffer);
    sleep_ms(500);
  }
}