#include "pico_display.h"
#include "st7789_spi.h"

int main()
{
  pico_display_config_spi_t conf = pico_display_get_default_config();
  conf.bl_en = 26;
  conf.btn_enab = false;

  pico_display_t disp = pico_display_init(&conf);
  pico_display_led_set_rgb(&disp, 91, 65, 254);

  for (;;);
}