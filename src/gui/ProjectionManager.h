//
// Created by artef on 04.03.2017.
//

#ifndef PLAYIN_PROJECTIONMANAGER_H
#define PLAYIN_PROJECTIONMANAGER_H

#include <Vec2d.h>

#include "glutUtils.h"

class ProjectionManager {

public:

    static int SCR_W;
    static int SCR_H;

    static double Local_W;
    static double Local_H;


    static void setupProjection( Vec2i screen_size, Vec2d local_size ) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        SCR_W = screen_size.x;
        SCR_H = screen_size.y;
        Local_W = local_size.x;
        Local_H = local_size.y;

        glViewport(0, 0, screen_size.x, screen_size.y);
        glOrtho(0.0, local_size.x, local_size.y, 0.0, -1.0, 10.0);

        glTranslated(0.325,0.325,0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glDisable(GL_CULL_FACE);
        glMatrixMode(GL_MODELVIEW);
    }

    static Vec2d screenToLocal(Vec2i screen_pos) {

        double lx = mutils::map(screen_pos.x, 0, SCR_W, 0.0, Local_W);
        double ly = mutils::map(screen_pos.y, 0, SCR_H, 0.0, Local_H);

        return Vec2d(lx,ly);
    }

};


#endif //PLAYIN_PROJECTIONMANAGER_H
