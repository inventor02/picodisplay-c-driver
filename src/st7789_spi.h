#pragma once

#include "pico/stdlib.h"

static const uint ST7789_BAUD = 62500000; // 16ns between SPI rising edges

typedef struct st7789
{
  uint spi_mosi;
  uint spi_sclk;
} st7789_t;