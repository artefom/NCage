//
// Created by artef on 01.03.2017.
//

#ifndef PLAYIN_PBOTEXTURE_H
#define PLAYIN_PBOTEXTURE_H

#include <glutUtils.h>

#include <iostream>
#include <stdlib.h>

template<GLuint IMAGE_WIDTH,
        GLuint IMAGE_HEIGHT,
        GLenum PIXEL_FORMAT,
        GLuint DATA_SIZE = IMAGE_WIDTH*IMAGE_HEIGHT*pixelSize<PIXEL_FORMAT>::size >
class PBOTexture {
public:

    // Define global parameters

    static const GLuint width = IMAGE_WIDTH;
    static const GLuint height = IMAGE_HEIGHT;
    static const GLuint data_size = DATA_SIZE;
    static const GLenum pixel_format = PIXEL_FORMAT;

    GLuint pboId;
    GLuint textureId;
    Color* mapped_mem;

    PBOTexture() {

  //      IMAGE_WIDTH = width;
   //     IMAGE_HEIGHT = height;
        mapped_mem = 0;

//        DATA_SIZE = IMAGE_WIDTH*IMAGE_HEIGHT*4;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);

        //Create internal storage for image.
        glTexStorage2D(GL_TEXTURE_2D,1,PIXEL_FORMAT,IMAGE_WIDTH,IMAGE_HEIGHT);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        //glTexSubImage2D(GL_TEXTURE_2D,0,0,0,IMAGE_WIDTH,IMAGE_HEIGHT,GL_RGBA,GL_UNSIGNED_BYTE,0);
        glBindTexture(GL_TEXTURE_2D, 0);

        //
        glGenBuffersARB(1, &pboId);

        //Bind buffer to upgrade pixels
        // This buffer is implicitly used as argument to glBufferDataARB()
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboId);

        // Copy pixel data to the buffer object with
        //If you specify a NULL pointer to the source array in glBufferDataARB(),
        // then PBO allocates only a memory space with the given data size. The last
        // parameter of glBufferDataARB() is another performance hint for PBO to provide how
        // the buffer object will be used
        glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, DATA_SIZE, 0, GL_STREAM_DRAW_ARB);

        mapped_mem = (Color*)glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY_ARB);

        //Unbind buffer
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboId);
    }

    void updatePixels() {

        // bind the texture and PBO
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboId);

        // Just fill texture with random pixels
        randomizeTexture(mapped_mem, IMAGE_WIDTH, IMAGE_HEIGHT, DATA_SIZE, false);

        // Initiate texture loading process
        // According to documentation, this function will wait until previous operation is finished
        // Though, it's not certain.
        // This function initiates DMA transfer to video card memory.
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,IMAGE_WIDTH,IMAGE_HEIGHT,PIXEL_FORMAT,GL_UNSIGNED_BYTE,0);

        //glGenerateMipmapEXT(GL_TEXTURE_2D);

        // Unbind buffer and texture
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
        glBindTexture(GL_TEXTURE_2D,0);
    }

    void updateSubPixels(int min_x, int min_y, int max_x, int max_y) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboId);

        randomizeTexture(mapped_mem, IMAGE_WIDTH, IMAGE_HEIGHT, DATA_SIZE, false);

        glTexSubImage2D(GL_TEXTURE_2D,0,min_x,min_y,max_x-min_x,max_y-min_y,PIXEL_FORMAT,GL_UNSIGNED_BYTE,0);
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
        glBindTexture(GL_TEXTURE_2D,0);
    }


    void randomizeTexture(void* dst, GLsizei width, GLsizei height, GLsizei size, bool full_update)
    {
        if(!dst)
            return;

//        int random_width = rand()%IMAGE_WIDTH;
//        int random_height = rand()%IMAGE_HEIGHT;
//
//        mapped_mem[random_height*IMAGE_HEIGHT+random_width] = Color::gray(rand()%255);

        Color* ptr = (Color*)dst;

        // copy 4 bytes at once
        for(int i = 0; i < IMAGE_HEIGHT; ++i)
        {
            for(int j = 0; j < IMAGE_WIDTH; ++j)
            {
                ptr->r = rand()%256;// = Color::gray(rand()%256);
                ptr->g = rand()%256;
                ptr->b = rand()%256;
                ++ptr;
            }
        }
    }

    ~PBOTexture(){

    }

};


#endif //PLAYIN_PBOTEXTURE_H
