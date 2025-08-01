/*
* Copyright (C) EdgeTx
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "edgetx.h"
#include "hal/rgbleds.h"
#include "definitions.h"

bool usbChargerLed() { return true; }
void ledRed() {}
void ledGreen() {}
void ledBlue() {}
void ledOff() {}
void rgbLedColorApply() {}

bool fsLedState(uint8_t i)
{
#if defined(FUNCTION_SWITCHES)
  return g_model.customSwitches[i].state;
#else
  return false;
#endif
}

uint8_t getRGBColorIndex(uint32_t color)
{
  for (uint8_t i = 0; i < DIM(colorTable); i++) {
    if (color == colorTable[i])
      return(i + 1);
  }
  return 0; // Custom value set with Companion
}

// RGB
#define WS2812_BYTES_PER_LED 3

// Maximum number of supported LEDs
#if !defined(WS2812_MAX_LEDS)
#  define WS2812_MAX_LEDS 48
#endif

// Pixel values
static uint8_t _led_colors[WS2812_BYTES_PER_LED * WS2812_MAX_LEDS];

void rgbSetLedColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t* pixel = &_led_colors[led * WS2812_BYTES_PER_LED];
  pixel[0] = g;
  pixel[1] = r;
  pixel[2] = b;
}

uint32_t rgbGetLedColor(uint8_t led)
{
  uint8_t* pixel = &_led_colors[led * WS2812_BYTES_PER_LED];
  return (pixel[1] << 16) + (pixel[0] << 8) + pixel[2];
}

void fsLedRGB(uint8_t idx, uint32_t color)
{
  rgbSetLedColor(idx, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
}

uint32_t fsGetLedRGB(uint8_t index)
{
  return rgbGetLedColor(index);
}
