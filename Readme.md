About
---------
We are creating an interactive game - using a Raspberry Pi, gyroscopes, and hardware buttons and LED's.
Software side we are using C++, [OpenCV](https://help.ubuntu.com/community/OpenCV) and [SDL](http://libsdl.org/). The firmware is facilitated with [WiringPi](http://wiringpi.com/reference/i2c-library/)
Here is the [Google Doc](https://docs.google.com/document/d/1TTdBHlfw9nqK5_OXADW4CyzqTXATi-f-pGh81lKu3uk/edit) roadmap and notes page. 


Compiling
---------
Ensure that you have SDL v2 installed.
```
// ARCH DEV - update me please
sudo pacman -S sdl2 opencv sdl2_gfx vtk sdl2_image 

// DEBIAN DEV - update me please
sudo apt-get install libsdl2-dev

// PI
sudo pacman -Syu
sudo pacman -S git python i2c-tools libi2c-dev opencv sdl2 sdl2_gfx vtk sdl2_image && git clone git://git.drogon.net/wiringPi && cd wiringPi && ./build
```
Run commands:

        make
        ./duckhaunt
