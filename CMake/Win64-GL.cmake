## CannonBall Windows Setup
## ────────────────────────
## Library Locations
set(LibDir c:/coding/lib)
set(BoostDir ${LibDir}/boost_1_74_0)
set(Sdl2Dir ${LibDir}/SDL2-2.0.12)
set(DxDir c:/dxsdk)

## Use OpenGL for rendering.
set(OPENGL 1)

## Platform Specific Libraries
## opengl32 and glu32 are for OpenGL.
## dxguid and dinput8 are for Direct X Haptic Support.
set(PlatformLinkLibs opengl32 glu32 dxguid dinput8)

## Platform Specific Link Directories
set(PlatformLinkDirs "${DxDir}/lib")
