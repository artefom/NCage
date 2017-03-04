//
// Created by artef on 28.02.2017.
//

#ifndef PLAYIN_GUIVIEW_H
#define PLAYIN_GUIVIEW_H


#include <glutUtils.h>
#include <cmath>
#include <utils/PBOTexture.h>
#include <stdlib.h>
#include "GuiBase.h"

class GuiView : public GuiBase {
public:


    Color background_color;
    Color grid_primary_color;
    Color grid_secondary_color;
    Color grid_third_color;

    Color grid_pivot_color;


    int highlight_step = 8;

    bool dragging;

    //PBOTexture<512,512,GL_RGBA> tex;

    GuiView();


    // INLINE FUNCTIONS

    inline Vec2d getScale() const {
        return scale;
    }

    inline Vec2d getScaleMin() const {
        return scale_min;
    }

    inline Vec2d getScaleMax() const {
        return scale_max;
    }

    inline Vec2d getCellSize() const {
        return cell_size;
    }

    inline Vec2d getPosition() const {
        return position;
    }

    // OTHER FUNCTIONS

    void setScale(Vec2d i_scale);

    void setScaleMin(Vec2d i_scale_min);

    void setScaleMax(Vec2d i_scale_max);

    void setCellSize(Vec2d i_cell_size);

    void rescale(double value, Vec2d pivot);

    virtual void OnMouseEvent(int button, int state, Vec2d mousePos);

    void setPosition(Vec2d pos);

    virtual void OnMouseMove(Vec2d mousePos);

    virtual void draw();

    // Draws scene in local (displayed scene) coordinates
    virtual void localDraw();

    virtual void localMouseEvent(int button, int state, Vec2d pos);

    virtual void localMouseMove(Vec2d pos);

    Vec2d screenToLocal(Vec2d pos) const;

    Vec2d localToScreen(Vec2d pos) const;

protected:

    void draw_background();

    void draw_grids();

private:

    Vec2d position;

    Vec2d scale;
    Vec2d scale_inv;
    Vec2d scale_min;
    Vec2d scale_max;

    Vec2d cell_size;

    // Minimum size of displayed cell;
    double min_displayed_cell_size_x;

    Vec2d pressed_local_position;

    void draw_grid(Vec2d cell_size, double min_displayed_cell_size_x, bool dynamic, Color c1, Color c2, int max_level);
};


#endif //PLAYIN_GUIVIEW_H
