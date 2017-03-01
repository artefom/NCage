//
// Created by artef on 01.03.2017.
//

#ifndef PLAYIN_PBOTEXTURE_H
#define PLAYIN_PBOTEXTURE_H

#include <glutUtils.h>

#include <iostream>
#include <stdlib.h>

class PBOTexture {
public:

    GLuint pboId;
    GLuint textureId;
    GLubyte* old_ptr;

    PBOTexture(GLsizei width, GLsizei height) {

        IMAGE_WIDTH = width;
        IMAGE_HEIGHT = height;
        old_ptr = 0;

        DATA_SIZE = IMAGE_WIDTH*IMAGE_HEIGHT*4;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
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

        //Unbind buffer
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboId);
    }

    void updatePixels() {

        // bind the texture and PBO
        glBindTexture(GL_TEXTURE_2D, textureId);
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboId);

        // bind PBO to update pixel values
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pboId);

        // map the buffer object into client's memory
        // Note that glMapBufferARB() causes sync issue.
        // If GPU is working with this buffer, glMapBufferARB() will wait(stall)
        // for GPU to finish its job. To avoid waiting (stall), you can call
        // first glBufferDataARB() with NULL pointer before glMapBufferARB().
        // If you do that, the previous data in PBO will be discarded and
        // glMapBufferARB() returns a new allocated pointer immediately
        // even if GPU is still working with the previous data.
        //glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, DATA_SIZE, 0, GL_STREAM_DRAW_ARB);
        GLubyte* ptr = (GLubyte*)glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY_ARB);
        if(ptr)
        {
            // update data directly on the mapped buffer
            updatePixels(ptr, IMAGE_WIDTH, IMAGE_HEIGHT, DATA_SIZE, ptr != old_ptr);
            glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB); // release pointer to mapping buffer
        }

        // copy pixels from PBO to texture object
        // Use offset instead of ponter.
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT, GL_BGRA, GL_UNSIGNED_BYTE, 0);

        // it is good idea to release PBOs with ID 0 after use.
        // Once bound with 0, all pixel operations behave normal ways.
        glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);


    }

    void updatePixels(void* dst, GLsizei width, GLsizei height, GLsizei size, bool full_update)
    {
        if(!dst)
            return;

        int* ptr = (int*)dst;

        // copy 4 bytes at once
        for(int i = 0; i < IMAGE_HEIGHT; ++i)
        {
            for(int j = 0; j < IMAGE_WIDTH; ++j)
            {
                *ptr = (int)((float)rand()/RAND_MAX*4294967296-2147483648);
                ++ptr;
            }
        }
    }

    static void Init();

    inline static bool isPBOSupported() {
        return pboSupported;
    }

    ~PBOTexture(){
    }

private:

    GLsizei DATA_SIZE;

    GLsizei IMAGE_WIDTH;
    GLsizei IMAGE_HEIGHT;

    static bool pboSupported;

};


#endif //PLAYIN_PBOTEXTURE_H
