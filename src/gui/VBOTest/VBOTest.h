//
// Created by artef on 14.06.2017.
//

#ifndef PLAYIN_VBOTEST_H
#define PLAYIN_VBOTEST_H

#include <Logger.h>
#include <vector>
#include "glutUtils.h"
#include "VBOTest/VBOMesh.h"

class VBOTest {
public:

    static bool initialized;
    static unsigned int m_nVBOVertices;
    static GLuint vao;
    static VBOMesh mesh;

    VBOTest() {

    }

    static void Init() {
        static GLfloat vertices_position[24] = {
                0.0, 0.0,
                0.5, 0.0,
                0.5, 0.5,
                0.0, 0.0,
                0.0, 0.5,
                -0.5, 0.5,
                0.0, 0.0,
                -0.5, 0.0,
                -0.5, -0.5,
                0.0, 0.0,
                0.0, -0.5,
                0.5, -0.5,
        };

//        mesh.setMesh(vertices_position, 24);

        Logger::info("VBO Initialized!");

        initialized = true;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);

        Logger::info("Compiling shaders");
        GLuint shaderProgram = create_program("res/vertex_shader", "res/fragment_shader");

        Logger::info("Getting attribute location");
        // Get the location of the attributes that enters in the vertex shader
        GLint position_attribute = glGetAttribLocation(shaderProgram, "position");

        // Specify how the data for position can be accessed
        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
        // Enable the attribute
        glEnableVertexAttribArray(position_attribute);

        Logger::info("VBOTest successfully initialized!");
    }

    static void Drawrect(Vec2d p1, Vec2d p2) {
        if (!initialized) Init();

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 12);
    }

    static void read_shader_src(const char *fname, std::vector<char> &buffer) {
        std::ifstream is(fname);
        if (!is.is_open()) {
            throw std::runtime_error("Could not open file " + std::string(fname));
        }
        while (!is.eof()) {
            buffer.push_back((char) is.get());
        }
        is.close();
//        std::ifstream is(fname);
//        std::istream_iterator<char> start(is), end;
////        std::vector<char> numbers(start, end);
//        buffer.insert(buffer.begin(),start,end);
////        std::cout << "Read " << numbers.size() << " numbers" << std::endl;
    }

    static GLuint load_and_compile_shader(const char *fname, GLenum shaderType) {
        // Load a shader from an external file
        std::vector<char> buffer;
        read_shader_src(fname, buffer);
        const char *src = &buffer[0];

        // Compile the shader
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        // Check the result of the compilation
        GLint test;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
        if (!test) {
            std::cerr << "Shader compilation failed with this message:" << std::endl;
            std::vector<char> compilation_log(512);
            glGetShaderInfoLog(shader, compilation_log.size(), NULL, &compilation_log[0]);
            std::cerr << &compilation_log[0] << std::endl;
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
};


#endif //PLAYIN_VBOTEST_H
