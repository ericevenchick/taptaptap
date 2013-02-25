TapTapTap
============

TapTapTap is a simple tap synchronizing metronome. Tapping the button enters a tempo, which
is displayed on the LED and heard on the speaker.

## Hardware

The firmware is tested on an ATtiny13, but should also work with other ATtiny devices.
The pin mapping for the button, speaker, and LED can be set in main.c. The default values are:

* B0: Button
* B1: LED
* B2: Speaker

Note that the button must be on pin B0 for the interrupt to work.

## Building
To build the firmware, run `make`.

To flash the device, set your programmer and port in the Makefile and run `make flash`.

## Use

Tap the button at a tempo. After the timeout, the tempo will be set.
Tap more to change the tempo.

## License

Firmware is provided under MIT license

```
Copyright (C) 2013 Eric Evenchick

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
