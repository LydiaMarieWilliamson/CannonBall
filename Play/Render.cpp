#include <iostream>
#include "Play/Render.hpp"
#include "Arena/Config.hpp"

#if defined WITH_OPENGL // Rendering: Open GL desktop.
// Open GL Video Rendering.
//
// Useful References:
//	http://www.sdltutorials.com/sdl-opengl-tutorial-basics
//	http://www.opengl.org/wiki/Common_Mistakes
//	http://open.gl/textures
//
// Copyright Chris White.
// See License.txt for more details.

const static Num4 SCANLINE_TEXTURE[] = { 0x00000000, 0xff000000 }; // BGRA 8-8-8-8-REV

Render::Render() {
}

bool Render::init(int src_width, int src_height, int scale, int video_mode, int scanlines) {
   this->src_width = src_width;
   this->src_height = src_height;
   this->video_mode = video_mode;
   this->scanlines = scanlines;
// Setup SDL Screen size
   if (!RenderBase::sdl_screen_size())
      return false;
   int flags = SDL_WINDOW_OPENGL;
// Full Screen Mode
   if (video_mode == video_settings_t::MODE_FULL) {
   // Calculate how much to scale screen from its original resolution
      Num4 w = (scn_width << 16)/src_width;
      Num4 h = (scn_height << 16)/src_height;
      dst_width = (src_width*std::min(w, h)) >> 16;
      dst_height = (src_height*std::min(w, h)) >> 16;
      flags |= SDL_WINDOW_FULLSCREEN_DESKTOP; // Set SDL flag
      SDL_ShowCursor(false); // Don't show mouse cursor in full-screen mode
   }
// Stretch screen. Lose original proportions
   else if (video_mode == video_settings_t::MODE_STRETCH) {
      dst_width = scn_width;
      dst_height = scn_height;
      flags |= SDL_WINDOW_FULLSCREEN_DESKTOP; // Set SDL flag
      SDL_ShowCursor(false); // Don't show mouse cursor in full-screen mode
   }
// Window Mode
   else {
      scn_width = dst_width = src_width*scale;
      scn_height = dst_height = src_height*scale;
      SDL_ShowCursor(true);
   }
// If we're not stretching the screen, centre the image
   if (video_mode != video_settings_t::MODE_STRETCH) {
      screen_xoff = scn_width - dst_width;
      if (screen_xoff)
         screen_xoff = (screen_xoff/2);
      screen_yoff = scn_height - dst_height;
      if (screen_yoff)
         screen_yoff = (screen_yoff/2);
   }
// Otherwise set to the top-left corner
   else {
      screen_xoff = 0;
      screen_yoff = 0;
   }
#if 0
   int bpp = info->vfmt->BitsPerPixel;
#else
   const int bpp = 32;
#endif
// Frees (Deletes) existing surface
   if (surface)
      SDL_FreeSurface(surface);
// Create the window and rendering context: no longer setting video mode on SDL2.
   surface = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0);
   if (!surface) {
      std::cerr << "Can't create rendering memory surface: " << SDL_GetError() << std::endl;
      return false;
   }
   SDL_ShowCursor(SDL_DISABLE);
// scn_* values will be ignored if we pass any of the FULLSCREEN flags, as expected.
// So these are here just for the windowed modes, and ignored otherwise.
   window = SDL_CreateWindow("Cannonball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scn_width, scn_height, flags);
// I don't know if there are platforms where ES is the default profile, so just in case
// I force a GL2 core profile here (deprecated functions disabled for good).
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
   glcontext = SDL_GL_CreateContext(window);
   if (!surface) {
      std::cerr << "Video mode set failed: " << SDL_GetError() << std::endl;
      return false;
   }
   if (screen_pixels)
      delete[]screen_pixels;
   screen_pixels = new Num4[src_width*src_height];
// SDL Pixel Format Information
   Rshift = surface->format->Rshift;
   Gshift = surface->format->Gshift;
   Bshift = surface->format->Bshift;
// This hack is necessary to fix an Apple OpenGL with SDL issue
#ifdef __APPLE__
#   if SDL_BYTEORDER == SDL_LIL_ENDIAN
   Rmask = 0x000000FF;
   Gmask = 0x0000FF00;
   Bmask = 0x00FF0000;
   Rshift += 8;
   Gshift -= 8;
   Bshift += 8;
#   else
   Rmask = 0xFF000000;
   Gmask = 0x00FF0000;
   Bmask = 0x0000FF00;
#   endif
#else
   Rmask = surface->format->Rmask;
   Gmask = surface->format->Gmask;
   Bmask = surface->format->Bmask;
#endif
// Initalize Open GL
// ─────────────────
// Disable dithering
   glDisable(GL_DITHER);
// Disable anti-aliasing
   glDisable(GL_LINE_SMOOTH);
   glDisable(GL_POINT_SMOOTH);
// Disable depth buffer
   glDisable(GL_DEPTH_TEST);
   glClearColor(0, 0, 0, 0); // Black background
   glShadeModel(GL_FLAT);
   glViewport(0, 0, scn_width, scn_height);
// Initalize Texture ID
   bool enable_scanlines = scanlines && (scale != 1 || video_mode != video_settings_t::MODE_WINDOW);
   glGenTextures(enable_scanlines? 2: 1, textures);
// Screen Texture Setup
   const GLint param = config.video.filtering? GL_LINEAR: GL_NEAREST;
   glBindTexture(GL_TEXTURE_2D, textures[SCREEN]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, src_width, src_height, 0, /* texture width, texture height */GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, /* Data format in pixel array */NULL);
// Scanline Texture Setup
   if (enable_scanlines) {
      glBindTexture(GL_TEXTURE_2D, textures[SCANLN]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 2, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, SCANLINE_TEXTURE);
   }
// Initalize D-List
   dlist = glGenLists(1);
   glNewList(dlist, GL_COMPILE);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, scn_width, scn_height, 0, 0, 1); // left, right, bottom, top, near, far
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen and depth buffer
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[SCREEN]); // Select Screen Texture
   glBegin(GL_QUADS);
   glTexCoord2i(0, 1);
   glVertex2i(screen_xoff, screen_yoff + dst_height); // lower left
   glTexCoord2i(0, 0);
   glVertex2i(screen_xoff, screen_yoff); // upper left
   glTexCoord2i(1, 0);
   glVertex2i(screen_xoff + dst_width, screen_yoff); // upper right
   glTexCoord2i(1, 1);
   glVertex2i(screen_xoff + dst_width, screen_yoff + dst_height); // lower right
   glEnd();
   if (enable_scanlines) {
      glEnable(GL_BLEND);
      glColor4ub(255, 255, 255, ((scanlines - 1) << 8)/100);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glBindTexture(GL_TEXTURE_2D, textures[SCANLN]);
      glBegin(GL_QUADS);
      glTexCoord2i(0, S16_HEIGHT);
      glVertex2i(screen_xoff, screen_yoff + dst_height); // lower left
      glTexCoord2i(0, 0);
      glVertex2i(screen_xoff, screen_yoff); // upper left
      glTexCoord2i(src_width, 0);
      glVertex2i(screen_xoff + dst_width, screen_yoff); // upper right
      glTexCoord2i(src_width, S16_HEIGHT);
      glVertex2i(screen_xoff + dst_width, screen_yoff + dst_height); // lower right
      glEnd();
      glDisable(GL_BLEND);
   }
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   glEndList();
   return true;
}

void Render::disable() {
   glDeleteLists(dlist, 1);
   glDeleteTextures(scanlines? 2: 1, textures);
// Deinit SDL2 GL context
   SDL_DestroyWindow(window);
   SDL_GL_DeleteContext(glcontext);
}

bool Render::start_frame() {
   return !(SDL_MUSTLOCK(surface) && SDL_LockSurface(surface) < 0);
}

bool Render::finalize_frame() {
   if (SDL_MUSTLOCK(surface))
      SDL_UnlockSurface(surface);
   return true;
}

void Render::draw_frame(Num2 *pixels) {
   Num4 *spix = screen_pixels;
// Lookup real RGB value from rgb array for backbuffer
   for (int i = 0; i < (src_width*src_height); i++)
      *(spix++) = rgb[*(pixels++)];
   glBindTexture(GL_TEXTURE_2D, textures[SCREEN]);
   glTexSubImage2D(
      GL_TEXTURE_2D, 0, 0, 0,		// target, LOD, xoff, yoff
      src_width, src_height,		// texture width, texture height
      GL_BGRA,				// format of pixel data
      GL_UNSIGNED_INT_8_8_8_8_REV,	// data type of pixel data
      screen_pixels			// pointer in image memory
   );
   glCallList(dlist);
#if 0
   glFinish();
#endif
   SDL_GL_SwapWindow(window);
}

bool Render::supports_vsync() {
   return SDL_GL_SetSwapInterval(1) == 0;
}
#elif defined WITH_OPENGLES // Rendering: Open GL mobile.
// Open GL_ES Video Rendering.
//
// Copyright Manuel Alfayate.
// See License.txt for more details.
#include <cstring>
#include <assert.h>

// Uncomment only for debugging purposes.
void gles_show_error();
#define	SHOW_ERROR // gles_show_error();

const unsigned kVertexCount = 4;
const unsigned kIndexCount = 6;

static const char *vertex_shader =
   "attribute vec2 TexCoord;\n"
   "attribute vec2 VertexCoord;\n"
   "attribute vec4 Color;\n"
   "uniform mat4 MVPMatrix;\n"
   "varying vec2 tex_coord;\n"
   "void main() {\n"
   "   gl_Position = MVPMatrix*vec4(VertexCoord, 0.0, 1.0);\n"
   "   tex_coord = TexCoord;\n"
   "}";

static const char *fragment_shader =
   "#ifdef GL_ES\n"
   "precision mediump float;\n"
   "#endif\n"
   "uniform sampler2D Texture;\n"
   "varying vec2 tex_coord;\n"
   "void main() {\n"
   "   gl_FragColor = vec4(texture2D(Texture, tex_coord).rgb, 1.0);\n"
   "}";

const char *vertex_shader_scanlines =
   "uniform mat4 MVPMatrix;"
   "uniform mediump vec2 OutputSize;"
   "uniform mediump vec2 TextureSize;"
   "uniform mediump vec2 InputSize;"
   "attribute vec4 VertexCoord;"
   "attribute vec4 TexCoord;"
   "varying vec4 TEX0;"
   "varying vec4 TEX2;"
   "varying vec2 _omega;"
   "struct sine_coord {"
   "   vec2 _omega;"
   "};"
   "vec4 _oPosition1;"
   "vec4 _r0006;"
   "void main() {"
   "   vec2 _oTex;"
   "   sine_coord _coords;"
   "   _r0006 = VertexCoord.x*MVPMatrix[0];"
   "   _r0006 = _r0006 + VertexCoord.y*MVPMatrix[1];"
   "   _r0006 = _r0006 + VertexCoord.z*MVPMatrix[2];"
   "   _r0006 = _r0006 + VertexCoord.w*MVPMatrix[3];"
   "   _oPosition1 = _r0006;"
   "   _oTex = TexCoord.xy;"
   "   _coords._omega = vec2((3.14150000E+00*OutputSize.x*TextureSize.x)/InputSize.x, 6.28299999E+00*TextureSize.y);"
   "   gl_Position = _r0006;"
   "   TEX0.xy = TexCoord.xy;"
   "   TEX2.xy = _coords._omega;"
   "}";

const char *fragment_shader_scanlines =
   "precision mediump float;"
   "uniform mediump vec2 OutputSize;"
   "uniform mediump vec2 TextureSize;"
   "uniform mediump vec2 InputSize;"
   "uniform sampler2D Texture;"
   "varying vec2 _omega;"
   "varying vec4 TEX2;"
   "varying vec4 TEX0;"
   "struct sine_coord {"
   "   vec2 _omega;"
   "};"
   "vec4 _ret_0;"
   "float _TMP2;"
   "vec2 _TMP1;"
   "float _TMP4;"
   "float _TMP3;"
   "vec4 _TMP0;"
   "vec2 _x0009;"
   "vec2 _a0015;"
   "void main() {"
   "   vec3 _scanline;"
   "   _TMP0 = texture2D(Texture, TEX0.xy);"
   "   _x0009 = TEX0.xy*TEX2.xy;"
   "   _TMP3 = sin(_x0009.x);"
   "   _TMP4 = sin(_x0009.y);"
   "   _TMP1 = vec2(_TMP3, _TMP4);"
   "   _a0015 = vec2(5.00000007E-02, 1.50000006E-01)*_TMP1;"
   "   _TMP2 = dot(_a0015, vec2(1.00000000E+00, 1.00000000E+00));"
   "   _scanline = _TMP0.xyz*(9.49999988E-01 + _TMP2);"
   "   _ret_0 = vec4(_scanline.x, _scanline.y, _scanline.z, 1.00000000E+00);"
   "   gl_FragColor = _ret_0;"
   "   return;"
   "}";

const GLfloat vertices[] = {
   -0.5f, -0.5f, 0.0f,
   +0.5f, -0.5f, 0.0f,
   +0.5f, +0.5f, 0.0f,
   -0.5f, +0.5f, 0.0f,
};

// Values defined in gles2_create()
GLfloat uvs[8];

const GLushort indices[] = {
   0, 1, 2,
   0, 2, 3,
};

Render::Render() {
}

Render::~Render() {
}

void Render::disable() {
   glDeleteProgram(shader.program);
   glDeleteBuffers(3, buffers);
   SHOW_ERROR
   glDeleteTextures(1, &texture);
   SHOW_ERROR
// Deinit SDL2 EGL context
   SDL_DestroyWindow(window);
   SDL_GL_DeleteContext(glcontext);
}

bool Render::init(int src_width, int src_height, int scale, int video_mode, int scanlines) {
   this->src_width = src_width;
   this->src_height = src_height;
   this->video_mode = video_mode;
   this->scanlines = scanlines;
// Setup SDL Screen size
   if (!RenderBase::sdl_screen_size())
      return false;
   int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
   const int bpp = 32;
// We init the SDL2 EGL context here
   SDL_ShowCursor(SDL_DISABLE);
   SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
   SDL_SetHint(SDL_HINT_VIDEO_WIN_D3DCOMPILER, "none");
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
   window = SDL_CreateWindow("Cannonball", 0, 0, 0, 0, flags);
   glcontext = SDL_GL_CreateContext(window);
// Frees (Deletes) existing surface
   if (surface)
      SDL_FreeSurface(surface);
   surface = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0);
   if (!surface) {
      std::cerr << "Can't create rendering memory surface: " << SDL_GetError() << std::endl;
      return false;
   }
// GL_ES only supports full screen mode
// Calculate how much to scale screen from its original resolution
// Full Screen Mode
   if (video_mode == video_settings_t::MODE_FULL) {
   // Calculate how much to scale screen from its original resolution
      Num4 w = (scn_width << 16)/src_width;
      Num4 h = (scn_height << 16)/src_height;
      dst_width = (src_width*std::min(w, h)) >> 16;
      dst_height = (src_height*std::min(w, h)) >> 16;
   }
// Stretch screen. Lose original proportions
   else {
      dst_width = scn_width;
      dst_height = scn_height;
   }
// If we're not stretching the screen, centre the image
   if (video_mode != video_settings_t::MODE_STRETCH) {
      screen_xoff = scn_width - dst_width;
      if (screen_xoff)
         screen_xoff = (screen_xoff/2);
      screen_yoff = scn_height - dst_height;
      if (screen_yoff)
         screen_yoff = (screen_yoff/2);
   }
// Otherwise set to the top-left corner
   else {
      screen_xoff = 0;
      screen_yoff = 0;
   }
// The src and scn dimensions are only needed for the scanlines shaders
   gles2_init_shaders(src_width, src_height, scn_width, scn_height, scanlines);
   if (screen_pixels)
      delete[]screen_pixels;
   screen_pixels = new Num4[src_width*src_height];
// SDL Pixel Format Information
   Rshift = surface->format->Rshift;
   Gshift = surface->format->Gshift;
   Bshift = surface->format->Bshift;
// Initalize Open GL
// ─────────────────
   glDisable(GL_DITHER); // Disable Dithering
   glDisable(GL_DEPTH_TEST); // Disable Depth Buffer
   glClearColor(0, 0, 0, 0); // Black background
   glViewport(screen_xoff, screen_yoff, dst_width, dst_height);
// Initalize Texture ID
   glGenTextures(1, &texture);
// ────────── Screen texture setup  ──────────────────
   const GLint param = config.video.filtering? GL_LINEAR: GL_NEAREST;
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA_EXT, src_width, src_height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, NULL);
   SHOW_ERROR
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen and depth buffer
   glActiveTexture(GL_TEXTURE0);
   SHOW_ERROR
// Leave screen texture binded so it's like that when we arrive to draw_frame so we save this call.
   glBindTexture(GL_TEXTURE_2D, texture);
   SHOW_ERROR
// ────────── GL geometry setup  ──────────────────
   GLfloat uvs[8];
   GLfloat proj[4][4];
// Setup texture coordinates
   float min_u = 0;
   float max_u = 1.0f;
   float min_v = 0;
   float max_v = 1.0f;
   uvs[0] = min_u;
   uvs[1] = min_v;
   uvs[2] = max_u;
   uvs[3] = min_v;
   uvs[4] = max_u;
   uvs[5] = max_v;
   uvs[6] = min_u;
   uvs[7] = max_v;
// Init buffer data
   glGenBuffers(3, buffers);
   SHOW_ERROR
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   SHOW_ERROR
   glBufferData(GL_ARRAY_BUFFER, kVertexCount*sizeof(GLfloat)*3, vertices, GL_STATIC_DRAW);
   SHOW_ERROR
   glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
   SHOW_ERROR
   glBufferData(GL_ARRAY_BUFFER, kVertexCount*sizeof(GLfloat)*2, uvs, GL_STATIC_DRAW);
   SHOW_ERROR
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   SHOW_ERROR
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
   SHOW_ERROR
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, kIndexCount*sizeof(GL_UNSIGNED_SHORT), indices, GL_STATIC_DRAW);
   SHOW_ERROR
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   SHOW_ERROR
// Activate the vertex position and texture coordinate attributes for the vertices
   glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
   SHOW_ERROR
   glVertexAttribPointer(shader.a_position, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), NULL);
   SHOW_ERROR
   glEnableVertexAttribArray(shader.a_position);
   SHOW_ERROR
   glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
   SHOW_ERROR
   glVertexAttribPointer(shader.a_texcoord, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), NULL);
   SHOW_ERROR
   glEnableVertexAttribArray(shader.a_texcoord);
   SHOW_ERROR
// Set the projection matrix
   SetOrtho(proj, -0.5f, +0.5f, +0.5f, -0.5f, -1.0f, 1.0f, 1, 1);
// Upload the projection matrix to the shader
   glUniformMatrix4fv(shader.u_vp_matrix, 1, GL_FALSE, &proj[0][0]);
   SHOW_ERROR
// We leave the element array buffer binded so it's binded when we arrive to gles2_draw() on each frame.
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
   SHOW_ERROR
   return true;
}

void gles_show_error() {
   GLenum error = GL_NO_ERROR;
   error = glGetError();
   if (GL_NO_ERROR != error) {
      SDL_Log("GL Error %x encountered!\n", error);
   }
}

void Render::gles2_init_shaders(unsigned texture_width, unsigned texture_height, unsigned output_width, unsigned output_height, int scanlines) {
   memset(&shader, 0, sizeof(__ShaderInfo));
// Load custom shaders
   float input_size[2], output_size[2], texture_size[2];
   if (scanlines)
      shader.program = CreateProgram(vertex_shader_scanlines, fragment_shader_scanlines);
   else
      shader.program = CreateProgram(vertex_shader, fragment_shader);
   if (shader.program) {
      shader.u_vp_matrix = glGetUniformLocation(shader.program, "MVPMatrix");
      shader.a_texcoord = glGetAttribLocation(shader.program, "TexCoord");
      shader.a_position = glGetAttribLocation(shader.program, "VertexCoord");
      if (scanlines) {
         shader.input_size = glGetUniformLocation(shader.program, "InputSize");
         shader.output_size = glGetUniformLocation(shader.program, "OutputSize");
         shader.texture_size = glGetUniformLocation(shader.program, "TextureSize");
         input_size[0] = (float)texture_width;
         input_size[1] = (float)texture_height;
         output_size[0] = (float)output_width;
         output_size[1] = (float)output_height;
         texture_size[0] = (float)texture_width;
         texture_size[1] = (float)texture_height;
      }
   } else
      exit(0);
   glUseProgram(shader.program);
   SHOW_ERROR
   if (scanlines) {
      glUniform2fv(shader.input_size, 1, input_size);
      glUniform2fv(shader.output_size, 1, output_size);
      glUniform2fv(shader.texture_size, 1, texture_size);
   }
}

GLuint Render::CreateShader(GLenum type, const char *shader_src) {
   GLuint shader = glCreateShader(type);
   if (!shader)
      return 0;
// Load and compile the shader source
   glShaderSource(shader, 1, &shader_src, NULL);
   glCompileShader(shader);
// Check the compile status
   GLint compiled = 0;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
   if (!compiled) {
      GLint info_len = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
      if (info_len > 1) {
         char *info_log = (char *)malloc(sizeof(char)*info_len);
         glGetShaderInfoLog(shader, info_len, NULL, info_log);
         SDL_Log("Error compiling shader:\n%s\n", info_log);
         free(info_log);
      }
      glDeleteShader(shader);
      return 0;
   }
   return shader;
}

// Function to load both vertex and fragment shaders, and create the program
GLuint Render::CreateProgram(const char *vertex_shader_src, const char *fragment_shader_src) {
   GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_src);
   if (!vertex_shader)
      return 0;
   GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_src);
   if (!fragment_shader) {
      glDeleteShader(vertex_shader);
      return 0;
   }
   GLuint program_object = glCreateProgram();
   if (!program_object)
      return 0;
   glAttachShader(program_object, vertex_shader);
   glAttachShader(program_object, fragment_shader);
// Link the program
   glLinkProgram(program_object);
// Check the link status
   GLint linked = 0;
   glGetProgramiv(program_object, GL_LINK_STATUS, &linked);
   if (!linked) {
      GLint info_len = 0;
      glGetProgramiv(program_object, GL_INFO_LOG_LENGTH, &info_len);
      if (info_len > 1) {
         char *info_log = (char *)malloc(info_len);
         glGetProgramInfoLog(program_object, info_len, NULL, info_log);
         printf("Error linking program:\n%s\n", info_log);
         free(info_log);
      }
      glDeleteProgram(program_object);
      return 0;
   }
// Delete these here because they are attached to the program object.
   glDeleteShader(vertex_shader);
   glDeleteShader(fragment_shader);
   return program_object;
}

// Builds an orthographic projection matrix and stores it in the matrix on the first parameter.
void Render::SetOrtho(float m[4][4], float left, float right, float bottom, float top, float near, float far, float scale_x, float scale_y) {
   memset(m, 0, 4*4*sizeof(float));
   m[0][0] = 2.0f/(right - left)*scale_x;
   m[1][1] = 2.0f/(top - bottom)*scale_y;
   m[2][2] = -2.0f/(far - near);
   m[3][0] = -(right + left)/(right - left);
   m[3][1] = -(top + bottom)/(top - bottom);
   m[3][2] = -(far + near)/(far - near);
   m[3][3] = 1;
}

bool Render::start_frame() {
   return true;
}

bool Render::finalize_frame() {
   return true;
}

void Render::draw_frame(Num2 *pixels) {
   Num4 *spix = screen_pixels;
// Lookup real RGB value from rgb array for backbuffer
   for (int i = 0; i < (src_width*src_height); i++)
      *(spix++) = rgb[*(pixels++)];
   glTexSubImage2D(
      GL_TEXTURE_2D, 0, 0, 0,	// target, LOD, xoff, yoff
      src_width, src_height,	// texture width, texture height
      GL_BGRA_EXT,		// format of pixel data
      GL_UNSIGNED_BYTE,		// data type of pixel data
      screen_pixels		// pointer in image memory
   );
   glDrawElements(GL_TRIANGLES, kIndexCount, GL_UNSIGNED_SHORT, 0);
   SHOW_ERROR
// We pageflip the SDL2 EGL context here
   SDL_GL_SwapWindow(window);
}

bool Render::supports_vsync() {
   return SDL_GL_SetSwapInterval(1) == 0;
}
#else // Rendering: SDL2 surface.
// SDL2 Hardware Surface Video Rendering.
//
// Known Bugs:
// -	Missing Scanlines
//
// Copyright Manuel Alfayate, Chris White.
// See License.txt for more details.

Render::Render(void) {
}

Render::~Render(void) {
}

bool Render::init(int src_width, int src_height, int scale, int video_mode, int scanlines) {
   this->src_width = src_width;
   this->src_height = src_height;
   this->scale = scale;
   this->video_mode = video_mode;
   this->scanlines = scanlines;
// Setup SDL Screen size
   if (!RenderBase::sdl_screen_size())
      return false;
   int flags = SDL_WINDOW_SHOWN;
// In SDL2, we calculate the output dimensions, but then in draw_frame() we won't do any scaling:
// SDL2 will do that for us, using the rects passed to SDL_RenderCopy().
// scn_* →	physical screen dimensions OR window dimensions.
//		On FULLSCREEN MODE it has the physical screen dimensions and in windowed mode it has the window dimensions.
// src_* →	real, internal, frame dimensions.
//		Will ALWAYS be 320 or 398 × 224.
//		NEVER CHANGES.
// corrected_scn_width_* →	output screen size for scaling.
//				In windowed mode it's the size of the window.
// Full Screen Mode
// ────────────────
   if (video_mode == video_settings_t::MODE_FULL || video_mode == video_settings_t::MODE_STRETCH) {
      flags |= (SDL_WINDOW_FULLSCREEN); // Set SDL flag
   // Fullscreen window size:
   // SDL2 ignores w and h in SDL_CreateWindow() if FULLSCREEN flag is enabled,
   // which is fine, so the window will be fullscreen of the physical videomode size,
   // but then, if we want to preserve ratio, we need dst_width bigger than src_width.
      scn_width = orig_width;
      scn_height = orig_height;
      src_rect.w = src_width;
      src_rect.h = src_height;
      src_rect.x = 0;
      src_rect.y = 0;
      if (video_mode == video_settings_t::MODE_FULL) {
         Num4 w = (scn_width << 16)/src_width;
         Num4 h = (scn_height << 16)/src_height;
         dst_rect.w = (src_width*std::min(w, h)) >> 16;
         dst_rect.h = (src_height*std::min(w, h)) >> 16;
         screen_xoff = scn_width - dst_rect.w;
         if (screen_xoff)
            screen_xoff = (screen_xoff/2);
         screen_yoff = scn_height - dst_rect.h;
         if (screen_yoff)
            screen_yoff = (screen_yoff/2)*scn_width;
         dst_rect.x = screen_xoff;
         dst_rect.y = screen_yoff;
      } else {
         dst_rect.x = 0;
         dst_rect.y = 0;
         dst_rect.w = scn_width;
         dst_rect.h = scn_height;
      }
      SDL_ShowCursor(false);
   }
// Windowed Mode
// ─────────────
   else {
      this->video_mode = video_settings_t::MODE_WINDOW;
      scn_width = src_width*scale;
      scn_height = src_height*scale;
      src_rect.w = src_width;
      src_rect.h = src_height;
      src_rect.x = 0;
      src_rect.y = 0;
      dst_rect.w = scn_width;
      dst_rect.h = scn_height;
      dst_rect.x = 0;
      dst_rect.y = 0;
      SDL_ShowCursor(true);
   }
#if 0
   int bpp = info->vfmt->BitsPerPixel;
#else
   const int bpp = 32;
#endif
// Frees (Deletes) existing surface
   if (surface)
      SDL_FreeSurface(surface);
   surface = SDL_CreateRGBSurface(0, src_width, src_height, bpp, 0, 0, 0, 0);
   if (!surface) {
      std::cerr << "Surface creation failed: " << SDL_GetError() << std::endl;
      return false;
   }
   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, config.video.filtering? "linear": "nearest");
   window = SDL_CreateWindow("Cannonball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scn_width, scn_height, flags);
   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, src_width, src_height);
// Convert the SDL pixel surface to 32 bit.
// This is potentially a larger surface area than the internal pixel array.
   screen_pixels = (Num4 *)surface->pixels;
// SDL Pixel Format Information
   Rshift = surface->format->Rshift;
   Gshift = surface->format->Gshift;
   Bshift = surface->format->Bshift;
   Rmask = surface->format->Rmask;
   Gmask = surface->format->Gmask;
   Bmask = surface->format->Bmask;
   return true;
}

void Render::disable() {
   SDL_DestroyTexture(texture);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
}

bool Render::start_frame() {
   return true;
}

bool Render::finalize_frame() {
   SDL_UpdateTexture(texture, NULL, screen_pixels, src_width*sizeof(Uint32));
   SDL_RenderClear(renderer);
   SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
// Very basic scanlines
   if (scanlines && scale != 1) {
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, ((scanlines - 1) << 8)/100);
      SDL_Rect r;
      r.x = dst_rect.x;
      r.w = dst_rect.w;
      r.h = scale >> 1;
      r.y = scale >> 1;
      for (; r.y < dst_rect.h; r.y += scale)
         SDL_RenderDrawRect(renderer, &r);
   }
   SDL_RenderPresent(renderer);
   return true;
}

void Render::draw_frame(Num2 *pixels) {
   Num4 *spix = screen_pixels;
// Lookup real RGB value from rgb array for backbuffer
   for (int i = 0; i < (src_width*src_height); i++)
      *(spix++) = rgb[*(pixels++)];
}
#endif // Rendering: end.
