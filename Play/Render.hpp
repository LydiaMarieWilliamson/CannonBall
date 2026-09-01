#pragma once
// Abstraction layer for technology-dependent video rendering.
// Exports: class Render and its member functions init(), disable(), start_frame(), finalize_frame() and draw_frame().
// Specializes: its member functions supports_window() and supports_vsync().

#include "RenderBase.hpp"

#if defined WITH_OPENGL // Rendering: Open GL desktop.
// Open GL Video Rendering.
//
// Useful References:
//	http://www.sdltutorials.com/sdl-opengl-tutorial-basics
//	http://www.opengl.org/wiki/Common_Mistakes
//	http://open.gl/textures
// Copyright Chris White.
// See License.txt for more details.
#include <SDL_opengl.h>

class Render: public RenderBase {
public:
   Render();
   bool init(int src_width, int src_height, int scale, int video_mode, int scanlines);
   void disable();
   bool start_frame();
   bool finalize_frame();
   void draw_frame(Num2 *pixels);
   bool supports_vsync();
private:
// Texture IDs
   const static int SCREEN = 0;
   const static int SCANLN = 1;
   GLuint textures[2];
   GLuint dlist; // GL display list
   SDL_GLContext glcontext;
};
#elif defined WITH_OPENGLES // Rendering: Open GL mobile.
// Open GL Video Rendering.
//
// Useful References:
//	http://www.sdltutorials.com/sdl-opengl-tutorial-basics
//	http://www.opengl.org/wiki/Common_Mistakes
//	http://open.gl/textures
// Copyright Chris White.
// See License.txt for more details.
#include <SDL_opengles2.h>

struct __ShaderInfo {
   GLuint program;
   GLint u_vp_matrix;
   GLint u_texture;
   GLint a_position; // vertex_coord;
   GLint a_texcoord; // tex_coord;
   GLint a_color; // color
   GLint lut_tex_coord;
   GLint input_size;
   GLint output_size;
   GLint texture_size;
   GLfloat scanline_bright;
};

class Render: public RenderBase {
public:
   Render();
   ~Render();
   bool init(int src_width, int src_height, int scale, int video_mode, int scanlines);
   void disable();
   bool start_frame();
   bool finalize_frame();
   void draw_frame(Num2 *pixels);
   bool supports_window() {
      return false;
   }
   bool supports_vsync();
private:
// Texture IDs
   const static int SCREEN = 0;
   GLuint buffers[3];
   GLuint texture;
   struct __ShaderInfo shader;
   void gles2_init_shaders(unsigned texture_width, unsigned texture_height, unsigned output_width, unsigned output_height, int scanlines);
   GLuint CreateProgram(const char *vertex_shader_src, const char *fragment_shader_src);
   GLuint CreateShader(GLenum type, const char *shader_src);
   void SetOrtho(float m[4][4], float left, float right, float bottom, float top, float near, float far, float scale_x, float scale_y);
   SDL_GLContext glcontext;
};
#else // Rendering: SDL2 surface.
// SDL2 Hardware Surface Video Rendering.
//
// Known Bugs:
// -	Software scanlines not implemented because we do hardware post-scaling using the SDL_RenderCopy() rects from the original bitmap,
//	so would not look good at all because they would be ruined by magnifying.
// Copyright Manuel Alfayate and Chris White.
// See License.txt for more details.

class Render: public RenderBase {
public:
   Render();
   ~Render();
   bool init(int src_width, int src_height, int scale, int video_mode, int scanlines);
   void disable();
   bool start_frame();
   bool finalize_frame();
   void draw_frame(Num2 *pixels);
private:
// SDL2 renderer
   SDL_Renderer *renderer;
// SDL2 texture
   SDL_Texture *texture;
// SDL2 blitting rects for hw scaling ratio correction using SDL_RenderCopy()
   SDL_Rect src_rect;
   SDL_Rect dst_rect;
};
#endif // Rendering: end.
