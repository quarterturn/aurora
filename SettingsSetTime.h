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
#include "/Applications/Arduino-1.0.6.app/Contents/Resources/Java/libraries/Time/Time.h"
//#include "t:\stuff\arduino-1.0.6-windows\arduino-1.0.6\libraries\Time\Time.h"

#ifndef SettingsSetTime_H
#define SettingsSetTime_H

class SettingsSetTime : public Runnable {
private:
    SetTimeState state = SetHour;
    unsigned int currentStateIndex = 0;

public:

    void run() {
        while (true) {
            drawFrame();
            clockDisplay.drawFrame();
            clockDisplay.drawSetTimeIndicator(state);

            matrix.swapBuffers();
            matrix.displayForegroundDrawing(false);

            InputCommand command = readCommand(defaultHoldDelay);

            switch (command) {
                case InputCommand::Up:
                    adjust(1);
                    break;

                case InputCommand::Down:
                    adjust(-1);
                    break;

                case InputCommand::Left:
                    currentStateIndex--;
                    break;

                case InputCommand::Right:
                    currentStateIndex++;
                    break;

                case InputCommand::Select:
                case InputCommand::Back:
                    return;
            }

            if (currentStateIndex > SetTimeStatesCount)
                currentStateIndex = 0;
            else if (currentStateIndex < 0)
                currentStateIndex = SetTimeStatesCount - 1;

            state = SetTimeStates[currentStateIndex];
        }
    }

    unsigned int drawFrame() {
        matrix.fillScreen(CRGB(CRGB::Black));
        return 0;
    }

    void adjust(int d) {
        switch (state) {
            case SetHour:
                time.Hour += d;
                if (time.Hour > 24)
                    time.Hour = 0;
                else if (time.Hour < 0)
                    time.Hour = 23;
                //RTC.write(time);                                
                Teensy3Clock.set(makeTime(time));
                setTime(makeTime(time));
                break;

            case SetMinute:
                time.Minute += d;
                if (time.Minute > 59)
                    time.Minute = 1;
                else if (time.Minute < 1)
                    time.Minute = 59;
                //RTC.write(time);
                Teensy3Clock.set(makeTime(time));
                setTime(makeTime(time));
                break;
        }
    }
};

#endif
