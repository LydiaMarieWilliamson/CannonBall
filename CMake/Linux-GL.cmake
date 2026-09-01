# -----------------------------------------------------------------------------
# CannonBall Linux Setup
# -----------------------------------------------------------------------------

# Use OpenGL for rendering.
find_package(OpenGL REQUIRED)

# Platform Specific Libraries
set(PlatformLinkLibs
    ${OPENGL_LIBRARIES}
)
