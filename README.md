# HP 82240 printer emulator

This project attempts to emulate an old HP 82240 IR printer.

## License

See LICENSE.md for license information. In short: Creative Commons Attribution-NonCommercial

## Hardware

* Thermal printer from Adafruit: https://www.adafruit.com/product/597
* Arduino Uno
* IR receiver circuit

The Arduino Uno expects to get IR signal on pin 3. This is either the 32768Hz carrier frequency sent by HP calculators, or just the rectified and smoothed signal from the IR signal. I would recommend a phototransistor in the 900-1000nm range and some form of simple amplification circuitry with an opamp.

The thermal printer is connected to pin 0 and 1 (RX and TX) on the Uno.

I'll put up some form of schematic here later.

## Compiling and using

The code is written using the platformio framework. It should, in theory, be as easy as installing platformio and then compiling the workspace.

The code is still being updated and there might be a few bugs left, but it should fully support all functions of the original printer (it prints text with the correct font, graphics, can do wide and underline etc.)

![](https://i.imgur.com/UuuNfDg.jpg)

## Schematic

![](https://github.com/dankar/redeye/blob/master/schematic/schematic.png?raw=true)