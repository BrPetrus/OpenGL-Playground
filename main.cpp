#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/GLFW/glfw3.h>

#include "log.h"
#include "shape.h"

std::string loadShaderFromFile(const std::string);
GLuint compileShader(const char*, const GLenum);
void updateFPSCounter(GLFWwindow*);

int main() {
    log::restartLog();
    
    std::string tmp = glfwGetVersionString();
    log::logErrorPrint("Starting GLFW; version: " + tmp);
    // Register error callback
    glfwSetErrorCallback(log::glfwErrorCallback);
    // Start GL context and OS window using the GLFW helper library
    if(!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // 4x antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4); 

    int winWidth = 640;
    int winHeight = 480;
    
    // Framebuffer
    int fWinWidth = 640;
    int fWinHeight = 480;
    

    // Create window
    GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* vmode = glfwGetVideoMode(mon);
    GLFWwindow* window = glfwCreateWindow(vmode->width, vmode->height, "Hello Triangle", nullptr, nullptr);
    if(!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported: %s\n", version);

    // Tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as closer

    /*OTHER STUFF GOES HERE NEXT*/
    const GLfloat points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    Shape obj1(loadShaderFromFile("Shaders/vertexShader.vert"), loadShaderFromFile("Shaders/fragmentShader.frag"), points, 9);
    
    // Draw in a loop
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        updateFPSCounter(window);
        
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        obj1.draw();
        // update other events lke input handling
        glfwPollEvents();
        // display the drawed stuff
        glfwSwapBuffers(window);
        
        // Exit if ESC is pressed.
        if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    // Shutdown
    glfwTerminate();
    return 0;
}

std::string loadShaderFromFile(const std::string path) {
    std::ifstream file(path);
    if(file.fail()) {
        std::cerr << "Error opening file " << path << std::endl;
        return 0;
    }
    
    std::cout << "Loaded file \"" << path << "\"\n";
    
    std::string text;
    std::string line;
    while(file.good()) {
        getline(file, line);
        text += line + '\n';
    }
    file.close();
    return text;
}

GLuint compileShader(const char* shaderText, const GLenum shaderType) {
    // Create shader object
    GLuint shader = glCreateShader(shaderType);
    
    // Put the shader inside shader object
    glShaderSource(shader, 1, &shaderText, nullptr);
    
    // Compile the shader
    glCompileShader(shader);
    
    // Error handling
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    // Successful
    if (success == GL_TRUE) {
        std::cout << "Successfuly compiled shader.\nShader text\"" << shaderText << "\"\n";
        return shader;
    }
    
    std::cout << "Unsuccessfuly compiled shader.\nShader text\"" << shaderText << "\"\n";
    
    // Unsuccessful
    GLint logSize = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    GLchar log[logSize]; // Create log variable
    glGetShaderInfoLog(shader, logSize, nullptr, &log[0]);
    
    // Print log
    std::cerr << log << std::endl;
    
    return 0;
} 

void updateFPSCounter(GLFWwindow* window) {
    double currentSec;
    double elapsedSec;
    static double previousSec;
    static int frameCount;
    
    // Get current time
    currentSec = glfwGetTime();
    elapsedSec = currentSec - previousSec;
    
    // For optimization we are going to limit text updates to 4 per second
    if (elapsedSec > 0.25) {
        previousSec = currentSec;
        double fps = (double)frameCount / elapsedSec;
        char tmp[128];
        sprintf(tmp, "OpenGL @ fps: %.2f", fps);
        glfwSetWindowTitle(window, tmp);
        frameCount = 0;
    }
    frameCount++;
}

/*void glfwWindowSizeCallbak(GLFWwindow* window, int w, int h) {
    
}
void glfwFramebufferResizeCallback(GLFWwindow*, int, int);*/