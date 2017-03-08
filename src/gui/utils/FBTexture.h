//
// Created by artef on 05.03.2017.
//

#ifndef PLAYIN_FBTEXTURE_H
#define PLAYIN_FBTEXTURE_H

#include <ProjectionManager.h>
#include <cassert>
#include "glutUtils.h"
#include "AttributeStack.h"

// This texture is supposed to be drawn into
class FBTexture {
private:

    bool initialized;

    GLuint texId;
    GLuint fbId;

    Vec2i size;

public:

    FBTexture() :
            texId(0),
            fbId(0),
            initialized(false)
    {

    }

    void Init(Vec2i i_size) {

        assert(!isInitialized());

        if (initialized)
            return;

        size = i_size;

        glGenFramebuffers(1, &fbId);
        glBindFramebuffer(GL_FRAMEBUFFER, fbId);

        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGenTextures(1, &texId);
        print("Texture created");
        glBindTexture(GL_TEXTURE_2D, texId);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        // Mipmaps [OPTIONAL]
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);

        //Create internal storage for image.
        //glTexStorage2D(GL_TEXTURE_2D,1,PIXEL_FORMAT,IMAGE_WIDTH,IMAGE_HEIGHT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        //glTexSubImage2D(GL_TEXTURE_2D,0,0,0,IMAGE_WIDTH,IMAGE_HEIGHT,GL_RGBA,GL_UNSIGNED_BYTE,0);


        // Configure frame buffer

        // Set "renderedTexture" as our colour attachement #0
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texId, 0);
        GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers


        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        initialized = true;
    }

    void resize(Vec2i i_size) {

        assert(isInitialized());
        assert(texId != 0);

        size = i_size;

        glBindTexture(GL_TEXTURE_2D, texId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }

    void Destroy() {
        if (!initialized) return;
        initialized = false;

        assert(texId != 0);
        assert(fbId != 0);

        glDeleteTextures(1, &texId);
        glDeleteFramebuffers(1, &fbId);

        texId = 0;
        fbId = 0;
    }

    ~FBTexture() {
        if (initialized) Destroy();
    }

    void bind() {

        assert(isInitialized());

        AttributeStack::pushFrameBuffer(fbId);

        ProjectionManager::pushViewportProjection();
        ProjectionManager::setViewportProjection( Vec2i(0,0), getSize() );

    }

    void unbind() {
        ProjectionManager::popViewportProjection();
        AttributeStack::popFrameBuffer();
    }

    bool isInitialized() const {
        return initialized;
    }

    GLuint getTexId() {
        return texId;
    }

    Vec2i getSize() {
        return size;
    }
};


#endif //PLAYIN_FBTEXTURE_H
