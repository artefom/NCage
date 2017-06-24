//
// Created by artef on 23.06.2017.
//

#ifndef PLAYIN_SHADERLOADER_H
#define PLAYIN_SHADERLOADER_H


#include <glew.h>
#include <vector>
#include <utils/FileIO.h>
#include <Logger.h>

class ShaderLoader {
public:
    static GLuint load_and_compile_shader(const char *fname, GLenum shaderType) {
        // Load a shader from an external file
        std::vector<char> buffer;

        try {
            FileIO::read_file(fname, buffer);
        } catch (...) {
            Logger::error("Could not open shader file: ", fname);
            glfwTerminate();
            exit(-1);
        }

        const char *src = &buffer[0];

        // Compile the shader
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        // Check the result of the compilation
        GLint test;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
        if (!test) {
            std::vector<char> compilation_log(512);
            glGetShaderInfoLog(shader, compilation_log.size(), NULL, &compilation_log[0]);
            Logger::error("Shader compilation failed with this message: ", &compilation_log[0]);
            glfwTerminate();
            exit(-1);
        }
        return shader;
    }

    // Create a program from two shaders
    static GLuint create_program(const char *path_vert_shader, const char *path_frag_shader) {
        // Load and compile the vertex and fragment shaders
        GLuint vertexShader = load_and_compile_shader(path_vert_shader, GL_VERTEX_SHADER);
        GLuint fragmentShader = load_and_compile_shader(path_frag_shader, GL_FRAGMENT_SHADER);

        // Attach the above shader to a program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        // Flag the shaders for deletion
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Link and use the program
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        return shaderProgram;
    }

    static GLuint primary_shader;

    static void Init() {
        primary_shader = create_program("res/vertex_shader", "res/fragment_shader");
    }
};


#endif //PLAYIN_SHADERLOADER_H
