//
// Created by artef on 23.06.2017.
//

#ifndef PLAYIN_RENDERPRIMITIVE_H
#define PLAYIN_RENDERPRIMITIVE_H

#include "glutUtils.h"
#include "Vertex.h"
#include "ShaderLoader.h"

/**
 * A class that warps around VAO (Vertex Array Object)
 * And can be rendered easily
 */
class RenderPrimitive {
public:

    GLuint vao;
    GLuint vbo;

    RenderPrimitive() {
//        glGenVertexArrays(1, &vao);
//        glBindVertexArray(vao);
//        glGenBuffers(1, &vbo);
    }

    void init() {
    }

//    /**
//     * Set vertex data of current primitive
//     * @tparam V - iterable object with .size()
//     * @param vec
//     */
//    template<class V>
//    void set_data( V vec ) {
//        Vertex vertices[vec.size()];
//        int counter = 0;
//        for (auto &v : vec) {
//            vertices[counter] = v;
//            ++counter;
//        }
//        set_data(vertices, vec.size());
//    }

    /**
     * Set vertex data of current primitive
     * @param vertices
     * @param len
     */
    void set_data(void *vertices, int len) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, len * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        GLint position_attribute = glGetAttribLocation(ShaderLoader::primary_shader, "position");

        // Specify how the data for position can be accessed
        glVertexAttribPointer(position_attribute, 2, GL_DOUBLE, GL_FALSE, 0, nullptr);
        // Enable the attribute
        glEnableVertexAttribArray(position_attribute);
    }

    // bind current vertex array object
    void bind() {
        glBindVertexArray(vao);
    }

};


#endif //PLAYIN_RENDERPRIMITIVE_H
