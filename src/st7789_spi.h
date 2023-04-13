#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#define ST7789_WIDTH    240
#define ST7789_HEIGHT   320
#define ST7789_FB_SIZE  ST7789_WIDTH * ST7789_HEIGHT

static const uint ST7789_BAUD = 62500000; // 16ns between SPI rising edges
static const uint ST7789_BL_PWM_WRAP = 65535;

static const uint ST7789_DEF_BL_BRIGHTNESS = 0;

typedef enum st7789_cmd
{
  // System Function Command Table 1
  NOP         = 0x00,
  SWRESET     = 0x01,
  RDDID       = 0x04,
  RDDST       = 0x09,
  RDDPM       = 0x0A,
  RDD_MADCTL  = 0x0B,
  RDD_COLMOD  = 0x0C,
  RDDIM       = 0x0D,
  RDDSM       = 0x0E,
  RDDSDR      = 0x0F,
  SLPIN       = 0x10,
  SLPOUT      = 0x11,
  PTLON       = 0x12,
  NORON       = 0x13,
  INVOFF      = 0x20,
  INVON       = 0x21,
  GAMSET      = 0x26,
  DISPOFF     = 0x28,
  DISPON      = 0x29,
  CASET       = 0x2A,
  RASET       = 0x2B,
  RAMWR       = 0x2C,
  RAMRD       = 0x2E,
  PTLAR       = 0x30,
  VSCRDEF     = 0x33,
  TEOFF       = 0x34,
  TEON        = 0x35,
  MADCTL      = 0x36,
  VSCRSADD    = 0x37,
  IDMOFF      = 0x38,
  IDMON       = 0x39,
  COLMOD      = 0x3A,
  RAMWRC      = 0x3C,
  RAMRDC      = 0x3E,
  TESCAN      = 0x44,
  RDTESCAM    = 0x45,
  WRDISBV     = 0x51,
  RDDISBV     = 0x52,
  WRCTRLD     = 0x53,
  RDCTRLD     = 0x54,
  WRCACE      = 0x55,
  RDCABC      = 0x56,
  WRCABCMB    = 0x5E,
  RDCABCMB    = 0x5F,
  RDABCSDR    = 0x68,
  RDID1       = 0xDA,
  RDID2       = 0xDB,
  RDID3       = 0xDC,

  // System Command Table 2
  RAMCTRL     = 0xB0,
  RGBCTRL     = 0xB1,
  PORCTRL     = 0xB2,
  FRCTRL1     = 0xB3,
  PARCTRL     = 0xB5,
  GCTRL       = 0xB7,
  GTADJ       = 0xB8,
  DGMEN       = 0xBA,
  VCOMS       = 0xBB,
  POWSAVE     = 0xBC,
  DLPOFFSAVE  = 0xBD,
  LCMCTRL     = 0xC0,
  IDSET       = 0xC1,
  VDVVRHEN    = 0xC2,
  VRHS        = 0xC3,
  VDVSET      = 0xC4,
  VCMOFSET    = 0xC5,
  FRCTR2      = 0xC6,
  CABCCTRL    = 0xC7,
  REGSEL1     = 0xC8,
  REGSEL2     = 0xCA,
  PWMFRSEL    = 0xCC,
  PWCTRL1     = 0xD0,
  VAPVANEN    = 0xD2,
  CMD2EN_1    = 0xDF,
  CMD2EN_2    = 0x5A,
  CMD2EN_3    = 0x69,
  CMD2EN_4    = 0x02,
  PVGAMCTRL   = 0xE0,
  NVGAMCTRL   = 0xE1,
  DGMLUTR     = 0xE2,
  DGMLUTB     = 0xE3,
  GATECTRL    = 0xE4,
  SPI2EN      = 0xE7,
  PWCTRL2     = 0xE8,
  EQCTRL      = 0xE9,
  PROMCTRL    = 0xEC,
  PROMEN      = 0xFA,
  NVMSET      = 0xFC,
  PROMACT     = 0xFE,
} st7789_cmd_t;

typedef struct st7789_config
{
  spi_inst_t *spi;
  uint pin_cs;
  uint pin_dc;
  uint pin_sck;
  uint pin_mosi;

  bool bl_enab;
  uint pin_bl;
} st7789_config_t;

typedef struct st7789
{
  spi_inst_t *spi;
  uint pin_cs;
  uint pin_dc;
  uint pin_sck;
  uint pin_mosi;

  bool bl_enab;
  uint pin_bl;

  uint8_t bl_brightness;
} st7789_t;

typedef uint16_t rgb565_frame_buffer_t[ST7789_FB_SIZE];

st7789_t st7789_init(st7789_config_t *config);

void st7789_set_backlight(st7789_t *st7789, uint8_t backlight);
