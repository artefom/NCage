//
// Created by artef on 14.06.2017.
//

#ifndef PLAYIN_VBOMESH_H
#define PLAYIN_VBOMESH_H

#include <Logger.h>
#include "glutUtils.h"

class VBOMesh {
public:

    VBOMesh() {

    }

    VBOMesh(GLfloat *verticies, int size) {

    }

    void setMesh(GLfloat *verticies, int size) {
// Create a Vector Buffer Object that will store the vertices on video memory
        GLuint vbo;
        glGenBuffers(1, &vbo);

        // Allocate space and upload the data from CPU to GPU
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);

        Logger::info("Mesh initialized!");
    }
};


#endif //PLAYIN_VBOMESH_H
