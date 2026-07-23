<font size=+0>

# Cannonball - OutRun Engine

CannonBall is a souped up game engine for the OutRun arcade game. The original 68000 and Z80 assembler code has been rewritten in C++. This makes it possible to make improvements suitable for modern platforms, including a higher frame-rate and widescreen support. It requires the original ROMs, as these contain elements including the graphics and audio data.

* For an overview of CannonBall and its features, please read the [manual](https://github.com/djyt/cannonball/wiki).
* [Reassembler Blog](http://reassembler.blogspot.co.uk/)
* [Twitter](https://twitter.com/djyt)

Please note that I  maintain the Windows build of CannonBall. Whilst I strive to ensure this is a fully cross-platform project that compiles across Linux, Wii, Mac, Pi4 etc. I do not maintain those ports. Port specific issues should be raised with the respective person.

Thank you!
Chris White (Project Creator).

### Addendum

This version of CannonBall is being moved away from the [original version](https://github.com/djyt/cannonball) by djyt, with the file tree flattened and out renamed, with more evocative names and the renaming retrofitted, including here.
Greater focus placed on the Linux version instead of Windows, the dependency on "cmake" removed in favor of "make", and support for the Windows version phased out.
These changes will eventually supersede the [Getting Started](#GettingStarted) and [Build](#Build) sections and render the [Visual Studio 2019 Community Edition](#VisualStudio2019) section superfluous.

For now, the "cmake" files are being retained, but only the Linux + OPENGL version has been verified.
The arcade game has "haptic" support, in which it responds to how hard you press, push or turn buttons, knobs and dials on input and jolts the game equipment on output.
Only the Windows versions supported this in the original and here.
You may try to add "haptic" support on the Linux versions, if you feel adventurous.
To facilitate this, further changes are going to be made to abstract out the platform dependencies and regularize the source code.

A movie version of the arcade game is in the works:
*   [Sega Arcade Racer OutRun Gets Surprise Movie Adaptation From Transformers Director Michael Bay and Madame Web Star Sydney Sweeney - IGN](https://www.ign.com/articles/sega-arcade-racer-outrun-gets-surprise-movie-adaptation-from-transformers-director-michael-bay-and-madame-web-star-sydney-sweeney)
*   [Michael Bay And Sydney Sweeney Team On Movie Adaptation Of ‘OutRun’ Video Game At Universal - Deadline](https://deadline.com/2025/04/sydney-sweeney-michael-bay-outrun-video-game-universal-1236373036/)
*   [OutRun Film in the Works at Universal Pictures with Michael Bay and Sydney Sweeney Attached to the Project - SegaBits](https://segabits.com/blog/2025/04/21/outrun-film-in-the-works-at-universal-pictures-with-michael-bay-and-sydney-sweeney-attached-to-the-project/)
*   [Sydney Sweeney and Michael Bay Set ‘OutRun’ Video Game Movie at Universal - Variety](https://variety.com/2025/film/news/michael-bay-sydney-sweeney-outrun-movie-1236374395/)

A re-translation from the binaries may also be carried out, and more variety may be added to the scene layout and music, particularly to include techno tracks.
I may also add in the ability and option for the female passenger to take the wheel, since she already seems to be rather assertive during the game.
Some of the extensions in the [cannonball-se](https://github.com/J1mbo/cannonball-se) version by J1mbo may be included in this version.

-- Darth Spectra 2026-07-22

<a name=GettingStarted></a>
## Getting Started

CannonBall is coded in C++ and makes use of the SDL 2 and Boost libraries.

CannonBall has been successfully built for Windows, Mac OS X, Linux, Open Pandora and the Raspberry Pi.

CannonBall can use OpenGL, OpenGLES (mobile platforms) or plain SDL2 for rendering.

I have recently deprecated support for SDL 1, to focus on SDL 2. But feel free to grab an older version from github if you need it.

* Install your favourite C++11 environment (e.g. GCC, Visual Studio, Xcode, MingGW etc.)
* Install [CMake](http://www.cmake.org/). This generates your platform and compiler build files.
* Extract the [Boost Library](http://www.boost.org/) somewhere, for example: c:\coding\lib\boost_1_74_0  Note that Boost does not need to be compiled, as only the header libraries are used. This keeps things nice and lightweight.
* Extract the [SDL Development Library](https://www.libsdl.org/download-2.0.php) somewhere, for example: c:\coding\lib\SDL2-2.0.12
* Read the SDL documentation & build the SDL Library for your system.
* Windows only: I needed to copy CannonBall/CMake/WindowsSdl2Fix/sdl2-config.cmake to c:\coding\lib\SDL2-2.0.12
* Windows only: download and install the [Direct 8.1 SDK](https://archive.org/details/dx81sdk_full). This is used for force-feedback and a legacy from when I was using SDL 1. I should update it sometime to use SDL 2 instead.
* Extract the Cannonball code somewhere, for example: c:\coding\CannonBall
* You may need to create a .cmake file for your system to configure specific options. See the cmake subdirectory for more details.

<a name=Build></a>
## Build

* Run CMake to generate the relevant build files for your compiler. You can optionally pass -DTARGET=filename to pass a custom .cmake file
* Compile using your chosen compiler. Further details below.

<a name=VisualStudio></a>
### Visual Studio 2019 Community Edition

* Create to the sub-directory you want to create your build files in (e.g. or vs_build)

    cmake -G "Visual Studio 16 2019" ../CMake

* Open the created CannonBall solution in VS 2019.
* Right click and choose 'Set as StartUp project'.
* Set working directory to something sensible. Right click -> Configuration properties -> Debugging
* Ensure Config.xml is in the working directory. _You can specify an alternate location on the command line_
* Edit Config.xml to reflect the paths of your ROMs and Res directories. By default, they should be in the working directory.
* Copy the OutRun revision B romset to the ROMs subdirectory.
* You can then compile, debug and run from Visual Studio as expected.

</font>
