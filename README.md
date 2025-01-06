# Pimoroni Plasma Rainbow

This project configures a
[Pimoroni Plasma 2350](https://shop.pimoroni.com/products/plasma-2350?variant=42092628279379)
to control a
[10m wire of neopixels mounted in star diffusers](https://shop.pimoroni.com/products/10m-addressable-rgb-led-star-wire?variant=41375620530259).  

It might also work with a Plasma 2040 unit, but may need some adjustments.

You can see a demonstration [on my YouTube channel](https://youtu.be/s6Uyos-bfrg).

## Prerequisites

### Hardware

First, you need the right hardware, starting with a Plasma 2350 unit and some
neopixels to control. It should not matter whether you have the Plasma unit that
supports wireless or not.

### Software

You also need a working development environment. First, you need to set up the
basics, i.e. the tools to compile code and the libraries you need. I followed
the steps in the
[setup guide for the Pico](https://github.com/pimoroni/pimoroni-pico/blob/main/setting-up-the-pico-sdk.md).

If you want to work with VS Code, you'll also need to go through something like
[this guide from Digikey](https://www.digikey.be/en/maker/projects/raspberry-pi-pico-and-rp2040-cc-part-2-debugging-with-vs-code/470abc7efb07432b82c95f6f67f184c0),
which helpfully covers the non-obvious bits required to get openocd working.

If you're interested, the [first part in the DigiKey series](https://www.digikey.be/en/maker/projects/raspberry-pi-pico-and-rp2040-cc-part-1-blink-and-vs-code/7102fb8bca95452e9df6150f39ae8422)
provides a nice alternative to the Pico guide.

## Building

To build the application from the command line, you can use commands like the
following, starting at the root the
repository:

```
mkdir build
cd build
cmake -DPICO_BOARD=pimoroni_plasma2350 ..
make -j8
```

The last command assumes you have eight cores, adjust as needed. Once the build
completes, there are two ways to install the application.

### VS Code and a PiProbe

If you have a [PiProbe](https://www.raspberrypi.com/documentation/microcontrollers/debug-probe.html), 
you should be able to use the debugger configuration in this project to build,
install (and debug) the code in this project.

First, you should check the paths in `.vscode/launch.json`and
`.vscode/settings.json` and update them as needed to match your system. Then,
you should be able to just hit the debugger icon and choose the configuration
defined in `.vscode/launch.json`.

The application will be built, deployed, and will pause execution at the
beginning of the `main()` function.

## Installing



### Command Line Tools

To install manually, hit the reset button twice or reboot your Pico while
holding the "Bootsel" button.  A USB drive will appear. Copy or drag the
generated UF2 file `pico-explorer-ir.uf2` onto the USB drive that appears.

### PiProbe

If you have a PiProbe, you can install the program without resetting your Pico
using a command like:

```
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program pico-explorer-ir.elf verify reset exit"
```

## Usage

Once you've built and installed the binary, the lights should cycle through,
with bands of each color chasing each other and blending when they overlap.