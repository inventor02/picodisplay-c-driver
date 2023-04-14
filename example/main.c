#include <stdlib.h>

#include "pico/stdlib.h"

#include "pico_display.h"
#include "st7789_spi.h"

#include "bitmaps.h"

int main()
{
  pico_display_config_spi_t conf = pico_display_get_default_config();

  pico_display_t disp = pico_display_init(&conf);
  st7789_set_backlight(&disp.lcd, 255);

  uint16_t all_red[ST7789_FB_SIZE];

  for (int i = 0; i < ST7789_FB_SIZE; i++) all_red[i] = 0b000000000000000;

  pico_display_lcd_update(&disp, all_red);
  
  for (;;)
  {
    for (int i = 0; i < 255; i++)
    {
      pico_display_led_set_rgb(&disp, i, 0, 0);
      sleep_ms(10);
    }

    for (int i = 255; i >= 0; i--)
    {
      pico_display_led_set_rgb(&disp, i, 0, 0);
      sleep_ms(10);
    }

    for (int i = 0; i < 255; i++)
    {
      pico_display_led_set_rgb(&disp, 0, i, 0);
      sleep_ms(10);
    }

    for (int i = 255; i >= 0; i--)
    {
      pico_display_led_set_rgb(&disp, 0, i, 0);
      sleep_ms(10);
    }

    for (int i = 0; i < 255; i++)
    {
      pico_display_led_set_rgb(&disp, 0, 0, i);
      sleep_ms(10);
    }

    for (int i = 255; i >= 0; i--)
    {
      pico_display_led_set_rgb(&disp, 0, 0, i);
      sleep_ms(10);
    }
  }

  for (;;);
}