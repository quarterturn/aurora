/*
 * Aurora: https://github.com/pixelmatix/aurora
 * Copyright (c) 2014 Jason Coon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef PatternInvaders_H
#define PatternInvaders_H

class PatternInvaders : public Drawable {
private:

public:

    unsigned int drawFrame() {
        matrix.fillScreen(CRGB(CRGB::Black));

        CRGB color1 = effects.ColorFromCurrentPalette(random(0, 255));

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 5; y++) {
                CRGB color = CRGB::Black;

                if (random(0, 2) == 1) {
                    color = color1;
                }

                matrix.fillRectangle(1 + x * 6, 1 + y * 6, 5 + x * 6, 5 + y * 6, color);

                if (x < 2)
                    matrix.fillRectangle(1 + (4 - x) * 6, 1 + y * 6, 5 + (4 - x) * 6, 5 + y * 6, color);
            }
        }

        return 2000;
    }
};

#endif
