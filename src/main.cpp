#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "renderer.h"
#include "vertex_buffer.h"
#include "element_buffer.h"

struct ShaderProgramSource {
    std::string vertexSourceProgram;
    std::string fragmentSourceProgram;
};

static ShaderProgramSource parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    enum class ShaderType { NONE=-1, VERTEX=0, FRAGMENT=1 };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while ( getline(stream, line) ) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

static SDL_Window* window = nullptr;
static SDL_GLContext glContext;
static GLuint VAO, vertexShader, fragmentShader, shaderProgram;
static unsigned int fps = 0;
static unsigned int lastDeltaTime = 0;
static VertexBuffer* vb = nullptr;
static ElementBuffer* eb = nullptr;

void CheckShaderCompile(GLuint shader, const char* name) {
    GLint success;
    GLchar infoLog[512];
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
        std::cerr << "Error compiling " << name << ":\n" << infoLog << std::endl;
    }
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("ArcadeGameProject", "0.1", "ArcadeGameProject");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("Hello OpenGL Triangle", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        SDL_Log("Failed to create GL context: %s", SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_Log("Failed initialize GLAD");
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    SDL_GL_SetSwapInterval(1);  // VSync = 1, uncapped = 0, adaprive VSync = -1 (if supported)

    GLCall(glViewport(0, 0, 800, 600));

    /* Data for VBO */
    float vertices[] = {
         0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    /* Data for EBO */
    unsigned int elements[] = {
        0, 1, 2,
        1, 0, 3
    };

    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    // VBO
    vb = new VertexBuffer(vertices, sizeof(vertices));

    // EBO
    eb = new ElementBuffer(elements, 6);

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    ShaderProgramSource source = parseShader("shaders/basic.glsl");
    const char* vertexShaderSource = source.vertexSourceProgram.c_str();
    const char* fragmentShaderSource = source.fragmentSourceProgram.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr));
    GLCall(glCompileShader(vertexShader));
    CheckShaderCompile(vertexShader, "vertex shader");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr));
    GLCall(glCompileShader(fragmentShader));
    CheckShaderCompile(fragmentShader, "fragment shader");

    shaderProgram = glCreateProgram();
    GLCall(glAttachShader(shaderProgram, vertexShader));
    GLCall(glAttachShader(shaderProgram, fragmentShader));
    GLCall(glLinkProgram(shaderProgram));

    GLint success;
    GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
    if (!success) {
        GLchar infoLog[512];
        GLCall(glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog));
        std::cerr << "Error linking shader program:\n" << infoLog << std::endl;
    }

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

    // Background color
    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    case SDL_EVENT_WINDOW_RESIZED:
        GLCall(glViewport(0, 0, event->window.data1, event->window.data2));
        break;
    }
    // For now I don't see a reason to handle the default.
    // I only want to handle specific events. Not all of them.
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    unsigned int tickStartTime = SDL_GetTicks();
    GLCall(glClear(GL_COLOR_BUFFER_BIT));


    GLCall(glUseProgram(shaderProgram));
    GLCall(glBindVertexArray(VAO));
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    SDL_GL_SwapWindow(window);

    fps++;
    unsigned int deltaTime = SDL_GetTicks() - tickStartTime;
    if (tickStartTime > lastDeltaTime + 1000) {
        lastDeltaTime = tickStartTime;
        std::string title = "FPS: " + std::to_string(fps);
        SDL_SetWindowTitle(window, title.c_str());
        fps = 0;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    // glDeleteBuffers(1, &VBO);
    delete eb;
    delete vb;
    GLCall(glDeleteVertexArrays(1, &VAO));
    GLCall(glDeleteProgram(shaderProgram));
    SDL_GL_DestroyContext(glContext);
}
