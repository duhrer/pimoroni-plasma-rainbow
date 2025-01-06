#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Adafruit_NeoPixel.hpp"

#include "colours.h"

// TODO: Pin for plasma unit

// See: https://shop.pimoroni.com/products/plasma-2350?variant=42092628279379
#define PLASMA_PIN 15

// See: https://shop.pimoroni.com/products/10m-addressable-rgb-led-star-wire?variant=41375620530259
#define STAR_WIRE_PIXELS 66

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(STAR_WIRE_PIXELS, PLASMA_PIN, NEO_GRB + NEO_KHZ800);

bool keep_running = true;

int ticks = 0;

int brightness = 127;

void setup () {
    // NeoPixel Init
    pixels.begin();
    pixels.clear();
    pixels.show();
}

#define DIRECTION 1

#define R_TICKS 25
#define G_TICKS 20
#define B_TICKS 20

#define BAND_WIDTH 33

int r_index = 0;
int g_index = 22;
int b_index = 44;

// This was brightness in another IMPL, we're trying to use the NeoPixel
// brightness for now.
int dot_intensity = 255;
void fill_band_values (int numPixels, int band_width, int index, int values[]) {
    values[index] = dot_intensity;

    int bands = ((band_width -1) / 2);

    for (int a = 1; a <= bands; a++) {
        int band_intensity = (dot_intensity / (a + 1));
        int leading_band_index = (index + a) % numPixels;
        values[leading_band_index] = band_intensity;

        int trailing_band_index = (index - a + numPixels) % numPixels;
        values[trailing_band_index] = band_intensity;
    }
}

int next_index (int current_index, int direction, int numPixels) {
    int raw_index = current_index + direction;
    return (raw_index + numPixels) % numPixels;
}

void redraw_rainbow_colours () {
    bool isDirty = false;

    if ((ticks % R_TICKS) == 0 ) {
        isDirty = true;
        r_index = next_index(r_index, DIRECTION, STAR_WIRE_PIXELS);
    }

    if ((ticks % G_TICKS) == 0) {
        isDirty = true;
        g_index = next_index(g_index, DIRECTION, STAR_WIRE_PIXELS);
    }

    if ((ticks % B_TICKS) == 0) {
        isDirty = true;
        b_index = next_index(b_index, DIRECTION, STAR_WIRE_PIXELS);
    }

    if (isDirty) {
        int r_values[STAR_WIRE_PIXELS] = {0};
        fill_band_values (STAR_WIRE_PIXELS, BAND_WIDTH, r_index, r_values);

        int g_values[STAR_WIRE_PIXELS] = {0};
        fill_band_values (STAR_WIRE_PIXELS, BAND_WIDTH, g_index, g_values);

        int b_values[STAR_WIRE_PIXELS] = {0};
        fill_band_values (STAR_WIRE_PIXELS, BAND_WIDTH, b_index, b_values);

        pixels.clear();
        for (int i = 0; i < STAR_WIRE_PIXELS; i++) {
            int r = r_values[i];
            int g = g_values[i];
            int b = b_values[i];

            if (r + g + b > 0) {
                pixels.setPixelColor(i, pixels.Color(r, g, b));
            }
        }

        pixels.show();
    }
}

#define MS_PER_TICK 10
#define TICKS_PER_CONTINUOUS_COLOUR_CHANGE 20

int continuous_colour_change_index = -1;

int main() {
    setup();

    while (keep_running) {
        redraw_rainbow_colours();

        ticks++;
        sleep_ms(MS_PER_TICK);
    }
}