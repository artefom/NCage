//
// Created by artef on 24.06.2017.
//

#ifndef PLAYIN_RENDERMANAGER_H
#define PLAYIN_RENDERMANAGER_H


#include <utils/FBTexture.h>
#include "glutUtils.h"

/**
 * All draw calls should be done through this class
 */
class RenderManager {
public:

    static void drawrect(Vec2d p1, Vec2d p2) {
        glBegin(GL_QUADS);
        glVertex2d(p1.x, p1.y);
        glVertex2d(p2.x, p1.y);
        glVertex2d(p2.x, p2.y);
        glVertex2d(p1.x, p2.y);
        glEnd();
    }

    static void drawhrect(Vec2d p1, Vec2d p2) {
        glBegin(GL_LINE_LOOP);
        glVertex2d(p1.x, p1.y);
        glVertex2d(p2.x, p1.y);
        glVertex2d(p2.x, p2.y);
        glVertex2d(p1.x, p2.y);
        glEnd();
    }

    static void drawtexrect(Vec2d p1, Vec2d p2) {
        glColor4f(1, 1, 1, 1);
        glBegin(GL_QUADS);

        //glNormal3f(0, 0, 1);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2d(p1.x, p1.y);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2d(p2.x, p1.y);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2d(p2.x, p2.y);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2d(p1.x, p2.y);

        glEnd();
    }

    static void drawline(Vec2d p1, Vec2d p2) {
        glBegin(GL_LINES);
        glVertex(p1);
        glVertex(p2);
        glEnd();
    }

    static void color(Color c) {
        glColor4ub(c.r, c.g, c.b, c.a);
    }

    static void bind_texture(GLuint tex_id) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_id);
    }

    static void unbind_texture() {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

    /**
     * Setups everything to be rendered into texture through FBO
     * Pushes new Viewport and binds frame buffer, resets scissor box
     * All this is done through FBTexture class with method FBTexture::bind()
     * this method estimates texture size (in pixels) through unprojecting current position
     * see (ProjectionManager::project_i)
     * Sets current drawing context to draw into texture.
     * @param tex
     */
    static void push_texture_context(const FBTexture &tex) {
        tex.bind();

        //print(cull_tex.getSize());

        glPushMatrix();

        glLoadIdentity();

        glClear(GL_COLOR_BUFFER_BIT);
    }

    /**
     * Unrolls changes of push_texture_context
     * @param tex
     */
    static void pop_texture_context() {
        glPopMatrix();
        FBTexture::unbind();
    }
};


#endif //PLAYIN_RENDERMANAGER_H
