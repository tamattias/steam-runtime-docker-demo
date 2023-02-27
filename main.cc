#include <SDL.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL2: %s", SDL_GetError());
    return 1;
  }

  auto window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
  if (!window) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create app window: %s", SDL_GetError());
    return 1;
  }

  // Create an OpenGL 3.2 Core Profile context and activate it.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  auto context = SDL_GL_CreateContext(window);
  if (!context) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create OpenGL context: %s", SDL_GetError());
    return 1;
  }
  SDL_GL_MakeCurrent(window, context);

  // Request VSync.
  SDL_GL_SetSwapInterval(1);

  // Create Vertex Buffer.
  const GLfloat vertices[] = {
    -0.5f, 0.5f,
    1.0f, 0.0f, 0.0f,

    0.5f, 0.5f,
    0.0f, 1.0f, 0.0f,

    0.0f, -0.5f,
    0.0f, 0.0f, 1.0f,
  };
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create Vertex Array Object.
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 20, nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 20, (char*)nullptr + 8);
  glEnableVertexAttribArray(1);

  // Compile Vertex Shader.
  const GLchar* vs_sources[] = { R"(
    #version 150
    in vec2 in_position;
    in vec3 in_color;
    out vec3 v_color;
    void main() {
      gl_Position = vec4(in_position, 0.0, 1.0);
      v_color = in_color;
    }
  )" };
  auto vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, vs_sources, nullptr);
  glCompileShader(vs);

  // Compile Fragment Shader.
  const GLchar* fs_sources[] = { R"(
    #version 150
    in vec3 v_color;
    out vec4 o_color;
    void main() {
      o_color = vec4(v_color, 1.0);
    }
  )" };
  auto fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, fs_sources, nullptr);
  glCompileShader(fs);

  // Link Shader Program and activate it.
  auto program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glBindAttribLocation(program, 0, "in_position");
  glBindAttribLocation(program, 1, "in_color");
  glLinkProgram(program);
  glUseProgram(program);

  bool quitting = false;

  while (!quitting) {
    // Event loop.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        quitting = true;
        break;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(context);

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
