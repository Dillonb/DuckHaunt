About
---------
We are creating an interactive game - using a Raspberry Pi, gyroscopes, and hardware buttons and LED's.
Software side we are using C++, and [SDL](http://libsdl.org/).
Here is the [Google Doc](https://docs.google.com/document/d/1TTdBHlfw9nqK5_OXADW4CyzqTXATi-f-pGh81lKu3uk/edit) roadmap and notes page. 


Compiling
---------


Ensure that you have SDL v2 installed.
```
sudo pacman -S sdl2 opencv sdl2_gfx vtk sdl2_image sdl2_ttf

sudo apt-get install libsdl2-dev
```
Run commands:

        make
        ./duckhaunt
