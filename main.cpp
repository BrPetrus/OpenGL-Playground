
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

int main() {
    log::restartLog();
    
    std::string tmp = glfwGetVersionString();
    log::logError("Starting GLFW; version: " + tmp + "\n");
    // Register error callback
    glfwSetErrorCallback(log::glfwErrorCallback);
    // Start GL context and OS window using the GLFW helper library
    if(!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    // Create window
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", nullptr, nullptr);
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
    
    // Define triangle
    GLfloat pointsT1[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    
    GLfloat pointsT2[] = {
        0.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    
    /*// Copy to VBO
    GLuint vbo1 = 0;
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1); // Set as current buffer in OpenGL state machine
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointsT1), pointsT1, GL_STATIC_DRAW);
    
    // Set up the triangle's VAO
    GLuint vao1 = 0;
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1); // We bind it again ... we don't really have to
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Defines memory layout
    
    GLuint vbo2 = 0;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointsT2), pointsT2, GL_STATIC_DRAW);
    
    GLuint vao2 = 0;
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    // Shaders
    std::string tempStr = loadShaderFromFile("Shaders/vertexShader.vert");
    const char* vertex_shader = tempStr.c_str();
    GLuint vs = compileShader(vertex_shader, GL_VERTEX_SHADER);
    tempStr = loadShaderFromFile("Shaders/fragmentShader.frag");
    const char* fragment_shader = tempStr.c_str();
    GLuint fs = compileShader(fragment_shader, GL_FRAGMENT_SHADER);
    
    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&isLinked);
    if(isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);
        std::cout << "Error while linking the program: ";
        for(auto i = infoLog.begin(); i != infoLog.end(); i++)
            std::cout << *i;
    }
    
    // Shader 2
    tempStr = loadShaderFromFile("Shaders/vertexShader2.vert");
    const char* vertex_shader2 = tempStr.c_str();
    GLuint vs2 = compileShader(vertex_shader2, GL_VERTEX_SHADER);
    tempStr = loadShaderFromFile("Shaders/fragmentShader2.frag");
    const char* fragment_shader2 = tempStr.c_str();
    GLuint fs2 = compileShader(fragment_shader2, GL_FRAGMENT_SHADER);
    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vs2);
    glAttachShader(shaderProgram2, fs2);
    glLinkProgram(shaderProgram2);
    */
    
    const GLfloat points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    Shape obj1(loadShaderFromFile("Shaders/vertexShader.vert"), loadShaderFromFile("Shaders/fragmentShader.frag"), points, 9);
    
    // Draw in a loop
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    while(!glfwWindowShouldClose(window)) {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*glUseProgram(shaderProgram);
        glBindVertexArray(vao1);
        // draw points 0-3 from the currently bound vao with current shader-program
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgram2);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);*/
        obj1.draw();
        
        // update other events lke input handling
        glfwPollEvents();
        // display the drawed stuff
        glfwSwapBuffers(window);
    }

    // Shutdown
    //glDeleteProgram(shaderProgram);
    //glDeleteShader(vs);
    //glDeleteShader(fs);
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