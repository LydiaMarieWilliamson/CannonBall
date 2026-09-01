# -----------------------------------------------------------------------------
# CannonBall Windows Setup
# -----------------------------------------------------------------------------

# Library Locations
set(LibDir c:/coding/lib)
set(BoostDir ${LibDir}/boost_1_74_0)
set(Sdl2Dir ${LibDir}/SDL2-2.0.12)
set(DxDir c:/dxsdk)

# Use OpenGL for rendering.
set(OPENGL 1)

# Platform Specific Libraries
set(PlatformLinkLibs
    opengl32 # For OpenGL
    glu32    # For OpenGL
    dxguid   # Direct X Haptic Support
    dinput8  # Direct X Haptic Support
)

# Platform Specific Link Directories
set(PlatformLinkDirs
    "${DxDir}/lib"
)
