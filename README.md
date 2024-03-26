# PokemonAGBMovementTest
My first proper C project! Entirely made with only C.  
( this means memory leaks are iminent )

use `./build/PokemonAGBMovement` to run

## What is this?
a simple SDL2 application which tries to simulate the Pokemon Firered/Leafgreen movement system as accurately as I can without stealing code from the decomp of Pokemon Firered/Leafgreen.  
It's got it all, grid snapping, running, both genders, and most importantly, a random 3x3 block of water!
  
https://github.com/memyboi/PokemonAGBMovementTest/assets/75206733/a6f4847c-0b48-47ec-afd3-8174941923e2

The greenscreen option can be used to do things like this:  
(ignore the top-tier editing)  

https://github.com/memyboi/PokemonAGBMovementTest/assets/75206733/f8294a87-e476-4c3f-9be8-dff0e766ef86

Controls:  
W,A,S,D,Left,Up,Down,Right - movement  
Shift - sprint  
R - freeze / unfreeze camera  
G - toggle male/female sprite  
T - reset player position  
K - toggle greenscreen  

## How to compile?
made for linux, a little unstable on mac os.
i do not know how to compile for windows.
(trust me, i tried)
  
### install dependencies:
Libraries:  
Windows: ¯\\\_(ツ)\_/¯ good luck  
Mac OS (install homebrew first) `brew install sdl2 sdl2_image`  
Arch based distro (eg. Arch, Endeavor OS): `sudo pacman -S sdl2 sdl2_image`  
Fedora based distro (eg. Fedora, Nobara): `sudo dnf install SDL2 SDL2-devel SDL2_image SDL2_image-devel`  
Debian based distro (eg. Debian, Ubuntu): `sudo apt-get install libsdl2-dev libsdl2-image-dev`  
Other: figure it out lol :p  

Compilation requirements:  
Windows: ¯\\\_(ツ)\_/¯ good luck  
Mac OS (install homebrew first) `brew install meson ninja make`  
Arch based distro (eg. Arch, Endeavor OS): `sudo pacman -S gcc git meson make ninja`  
Fedora based distro (eg. Fedora, Nobara): `sudo dnf install gcc git meson make ninja-build`  
Debian based distro (eg. Debian, Ubuntu): `sudo apt-get install gcc git meson make ninja-build`  
Other: figure it out lol :p  

### compilation:
once you clone the repo, just run `make`.  
note: this project uses the meson build system in combination with a makefile, simply for convenience. if you'd like to directly use the meson build system, run these commands:
```
meson setup build --wipe
ninja -C build
```
  
### step-by-step instructions:  
```
git clone https://github.com/memyboi/PokemonAGBMovementTest.git
cd PokemonAGBMovementTest
make
./build/PokemonAGBMovement
```
assuming you have the correct dependencies, it should go off without a hitch.
