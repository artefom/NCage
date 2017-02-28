//
// Created by artef on 28.02.2017.
//

#ifndef PLAYIN_GUIVIEW_H
#define PLAYIN_GUIVIEW_H


#include <glutUtils.h>
#include <cmath>
#include "GuiBase.h"

class GuiView : public GuiBase {
public:

    Vec2d position;
    Vec2d scale;

    Vec2d cell_size;

    // Minimum size of displayed cell;
    double min_displayed_cell_size_x;

    Color background_color;
    Color grid_primary_color;
    Color grid_secondary_color;
    Color grid_third_color;

    Color grid_pivot_color;

    Vec2d pressed_local_position;

    int highlight_step = 8;

    bool dragging;

    GuiView() {
        position = Vec2d::ZERO;
        scale = Vec2d::ONE;

        cell_size = Vec2d(20,20);

        min_displayed_cell_size_x = 5;

        background_color = Color(30,30,30);
        grid_primary_color = Color(60,60,60);
        grid_pivot_color = Color(200,100,100);
        grid_secondary_color = Color(100,100,100);
        grid_third_color = Color(100,100,250);
    }

    virtual void OnMouseEvent(int button, int state, Vec2d mousePos) {
        if (state == 1) {
            if (button == 0) {
                dragging = false;
            }
            return;
        }

        if (button == 3 || button == 4) {

            Vec2d old_position = screenToLocal(mousePos);

            if (button == 3) scale *= 1.1;
            else scale /= 1.1;

            Vec2d newPos = screenToLocal(mousePos);
            position += (newPos-old_position)/scale;
        }


        if (button == 0) {
            std::cout << "Dragging!" << std::endl;
            dragging = true;
            pressed_local_position = screenToLocal(mousePos);
        }
    }

    virtual void OnMouseMove(Vec2d mousePos) {

        if (dragging) {
            Vec2d newPos = screenToLocal(mousePos);
            position += (newPos-pressed_local_position)/scale;
        }

    }

    virtual void draw() {

        // Draw background
        glColor(background_color);

        drawRect(Vec2d::ZERO,getSize());

        draw_grid(cell_size,min_displayed_cell_size_x, true, grid_primary_color, background_color,5);

        draw_grid(cell_size*highlight_step,min_displayed_cell_size_x*highlight_step, true, grid_secondary_color, grid_primary_color,4);

        draw_grid(cell_size*highlight_step*highlight_step,min_displayed_cell_size_x*highlight_step*highlight_step,
                  true, grid_third_color, grid_secondary_color,3);

        Vec2d pivot = localToScreen(Vec2d::ZERO);

        glColor(grid_pivot_color);
        if (pivot.x > 0 && pivot.x < getSize().x) {
            glBegin(GL_LINES);
            glVertex2d(pivot.x,0);
            glVertex2d(pivot.x,getSize().y);
            glEnd();
        }

        if (pivot.y > 0 && pivot.y < getSize().y) {
            glBegin(GL_LINES);
            glVertex2d(0,pivot.y);
            glVertex2d(getSize().x,pivot.y);
            glEnd();
        }

    }


    Vec2d screenToLocal(Vec2d pos) {
        return (pos-position)*scale;
    }

    Vec2d localToScreen(Vec2d pos) {
        return (pos/scale)+position;
    }

private:


    void draw_grid(Vec2d cell_size, double min_displayed_cell_size_x, bool dynamic, Color c1, Color c2, int max_level) {

        Vec2d pivot = localToScreen(Vec2d::ZERO);
        Vec2d displayed_cell_size = localToScreen(cell_size)-pivot;

        if (dynamic) {
            // Level of grid to be displayed

            int level = 0;

            while (displayed_cell_size.x < min_displayed_cell_size_x) {

                level += 1;
                if (level > max_level) return;

                displayed_cell_size *= highlight_step;
            }

            while (displayed_cell_size.x > min_displayed_cell_size_x*highlight_step) {

                level -= 1;
                if (level < -5) break;

                displayed_cell_size /= highlight_step;
            }

        }

        Color mixed_color = c1;
        if (displayed_cell_size.x < min_displayed_cell_size_x*4) {
            double alpha = (displayed_cell_size.x-min_displayed_cell_size_x)/(min_displayed_cell_size_x*3);
            mixed_color = Color::mix(c2,c1,alpha);
        }

        glColor(mixed_color);

        // Draw vertical lines
        {
            //int index = -(int)( pivot.x / displayed_cell_size.x );
            double begin = (double) std::fmod(pivot.x, displayed_cell_size.x);
            if (begin < 0) begin += displayed_cell_size.x;
            double end = getSize().x;
            double step = displayed_cell_size.x;

            double y1 = 0;
            double y2 = getSize().y;

            glBegin(GL_LINES);
            for (double x = begin; x < end; x+=step ) {
//                if (index == 0) {
//                    glColor(grid_pivot_color);
//                } else {
//                    glColor(grid_primary_color);
//                }
//                index += 1;
                glVertex2d(x,y1);
                glVertex2d(x,y2);
            }
            glEnd();
        }

        {
            // Draw horisontal lines
//            int index = -(int)( pivot.y / displayed_cell_size.y );
            double begin = (double) std::fmod(pivot.y, displayed_cell_size.y);
            if (begin < 0) begin += displayed_cell_size.y;
            double end = getSize().y;
            double step = displayed_cell_size.y;

            double x1 = 0;
            double x2 = getSize().x;

            glBegin(GL_LINES);
            for (double y = begin; y < end; y+=step ) {
//                if (index == 0) {
//                    glColor(grid_pivot_color);
//                } else {
//                    glColor(grid_primary_color);
//                }
//                index += 1;
                glVertex2d(x1,y);
                glVertex2d(x2,y);
            }
            glEnd();
        }
        // Draw horizontal lines
    }


};


#endif //PLAYIN_GUIVIEW_H
