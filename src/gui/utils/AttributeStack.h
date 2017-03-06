//
// Created by artef on 05.03.2017.
//

#ifndef PLAYIN_ATTRIBUTESTACK_H
#define PLAYIN_ATTRIBUTESTACK_H

#include <stack>
#include "glutUtils.h"

class AttributeStack {
public:

    static std::stack<GLuint> fb_stack;
    static std::stack<GLuint> tex_stack;

    static void pushFrameBuffer(GLuint fb){
        glBindFramebuffer(GL_FRAMEBUFFER,fb);
        fb_stack.push(fb);
    }


    static void popFrameBuffer() {

        if (fb_stack.empty())
            glBindFramebuffer(GL_FRAMEBUFFER,0);

        fb_stack.pop();

        if (fb_stack.empty())
            glBindFramebuffer(GL_FRAMEBUFFER,0);
        else
            glBindFramebuffer(GL_FRAMEBUFFER,fb_stack.top());
    }

    static void pushTexture(GLuint tex){
        glBindTexture(GL_TEXTURE_2D, tex);
        tex_stack.push(tex);
    }

    static void popTexture() {
        if (tex_stack.empty())
            glBindTexture(GL_TEXTURE_2D, 0);;

        tex_stack.pop();

        if (tex_stack.empty())
            glBindTexture(GL_TEXTURE_2D, 0);
        else
            glBindTexture(GL_TEXTURE_2D,tex_stack.top());
    }


};


#endif //PLAYIN_ATTRIBUTESTACK_H
