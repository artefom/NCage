//
// Created by artef on 14.06.2017.
//

#ifndef PLAYIN_VBOTEST_H
#define PLAYIN_VBOTEST_H

#include <Logger.h>
#include <vector>
#include <render/ShaderLoader.h>
#include <render/RenderPrimitive.h>
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

    static RenderPrimitive render_piece;

    static void Init() {

        static GLdouble vertices_position[24] = {
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

        render_piece.init();
        render_piece.set_data(vertices_position, 24);

//        mesh.setMesh(vertices_position, 24);

//        Logger::info("VBO Initialized!");
//
//        initialized = true;
//
//        glGenVertexArrays(1, &vao);
//        glBindVertexArray(vao);
//
//        GLuint vbo;
//        glGenBuffers(1, &vbo);
//
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);
//
//        Logger::info("Compiling shaders");
//        //GLuint shaderProgram = create_program("res/vertex_shader", "res/fragment_shader");
//
//        Logger::info("Getting attribute location");
//        // Get the location of the attributes that enters in the vertex shader
//        GLuint position_attribute = glGetAttribLocation(ShaderLoader::primary_shader, "position");
//
//        // Specify how the data for position can be accessed
//        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
//        // Enable the attribute
//        glEnableVertexAttribArray(position_attribute);
//
//        Logger::info("VBOTest successfully initialized!");
    }

    static void Drawrect(Vec2d p1, Vec2d p2) {
        if (!initialized) Init();

        render_piece.bind();
//        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 12);
    }

};


#endif //PLAYIN_VBOTEST_H
