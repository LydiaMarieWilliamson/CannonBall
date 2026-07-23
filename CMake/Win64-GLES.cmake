# -----------------------------------------------------------------------------
# CannonBall Windows Setup
#
# Extra libraries are required to use OpenGLES on Windows.
# Quite a long install process.
# Download & Compile Angle: https://opensource.google/projects/angle
#
# Other notes:
# http://mickcharlesbeaver.blogspot.com/2017/11/using-opengl-es-20-with-sdl2-via-angle.html
# -----------------------------------------------------------------------------

# Library Locations
set(LibDir c:/coding/lib)
set(BoostDir ${LibDir}/boost_1_74_0)
set(Sdl2Dir ${LibDir}/SDL2-2.0.12)
set(AngleDir ${LibDir}/angle/out/Debug)
set(DxDir c:/dxsdk)

# Use OpenGLES for rendering.
set(OPENGLES 1)

# Platform Specific Libraries
set(PlatformLinkLibs
    "${AngleDir}/libEGL.dll.lib"
    "${AngleDir}/libGLESv2.dll.lib"
    dxguid   # Direct X Haptic Support
    dinput8  # Direct X Haptic Support
)

# Platform Specific Link Directories
set(PlatformLinkDirs
    "${DxDir}/lib"
)
