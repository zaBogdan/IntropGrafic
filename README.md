# Statically linked sdl2 library plus sdl_bgi
Two examples of hello world-ish windows, sdl2 statically linked.  
One example of bgi windows(with Graphics.h) - using sdl-bgi  
Uses latest stable release on unofficial github mirror for sdl2.  
Tested on: 
 * Windows 10, CLion 2020.2.4
 * MacOS Big Sur, CLion 2020.2.4
 * ArchLinux, CLion 2020.2.4
 
Usage options:
* git clone --recursive https://github.com/AntohiRobert/BGI-port and build with cmake
* In CLion, Get from Version control, cmake is default build tool in CLion

To add more source files, simply create .cpp file and add_executable(together with target_link_libraries)
in the CMakeLists.txt file.
 
Submodule sdl-bgi mirror isn't used at all, just copied sources to src, left sdl-bgi for documentation.  
To update sdl-bgi:
* Download new sdl-bgi release(source!!) either from a Github Mirror or http://libxbgi.sourceforge.net/
* Replace sdl-bgi folder with the new one(or don't,it isn't used)
* Copy graphics.h, SDL_bgi.h and SDL_bgi.c to src
* Remove "SDL2/" from include in the above mentioned files, leave just header files