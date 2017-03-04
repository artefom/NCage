//
// Created by artef on 28.02.2017.
//

#include "GuiView.h"

GuiView::GuiView() {
    position = Vec2d::ZERO;

    setScaleMin(Vec2d(0.000001,0.000001));
    setScaleMax(Vec2d(100000,100000));
    setScale(Vec2d::ONE);

    setCellSize(Vec2d(20,20));

    min_displayed_cell_size_x = 5;

    background_color = Color(30,30,30);
    grid_primary_color = Color(60,60,60);
    grid_pivot_color = Color(200,100,100);
    grid_secondary_color = Color(100,100,100);
    grid_third_color = Color(100,100,250);
}

void GuiView::setScale(Vec2d i_scale) {

    // fool proof
    if (mutils::isinf_any(i_scale) || mutils::isnan_any(i_scale)) return;

    scale.x = mutils::clamp(scale.x,scale_min.x,scale_max.x);
    scale.y = mutils::clamp(scale.y,scale_min.y,scale_max.y);

    scale = i_scale;
    scale_inv = 1.0/scale;
}

void GuiView::setScaleMin(Vec2d i_scale_min) {

    // fool proof
    if (mutils::isinf_any(i_scale_min) || mutils::isnan_any(i_scale_min)) return;

    scale_min = i_scale_min;

    scale.x = mutils::clamp(scale.x,scale_min.x,scale_max.x);
    scale.y = mutils::clamp(scale.y,scale_min.y,scale_max.y);
}

void GuiView::setScaleMax(Vec2d i_scale_max) {

    // fool proof
    if (mutils::isinf_any(i_scale_max) || mutils::isnan_any(i_scale_max)) return;

    scale_max = i_scale_max;

    scale.x = mutils::clamp(scale.x,scale_min.x,scale_max.x);
    scale.y = mutils::clamp(scale.y,scale_min.y,scale_max.y);
}

void GuiView::setCellSize(Vec2d i_cell_size) {
    cell_size = i_cell_size;
}

void GuiView::rescale(double value, Vec2d pivot) {

    Vec2d old_position = screenToLocal(pivot);

    setScale(getScale()*value);

    Vec2d newPos = screenToLocal(pivot);

    setPosition(getPosition() + ((newPos-old_position)/scale) );

}

void GuiView::OnMouseEvent(int button, int state, Vec2d mousePos) {

    if (state == 1) {
        if (button == 0) {
            dragging = false;
        }
        return;
    }

    if (button == 3) rescale(1.1,mousePos);
    if (button == 4) rescale(1.0/1.1,mousePos);

    if (button == 0) {
        dragging = true;
        pressed_local_position = screenToLocal(mousePos);
    }

}

void GuiView::setPosition(Vec2d pos) {
    if (mutils::isinf_any(pos) || mutils::isnan_any(pos)) return;

    position = pos;
}

void GuiView::OnMouseMove(Vec2d mousePos) {

    if (dragging) {
        Vec2d newPos = screenToLocal(mousePos);
        setPosition(getPosition() + (newPos-pressed_local_position)/scale);
    }

}

void GuiView::draw() {
    draw_background();

    {safePushMatrix mat;
        glTranslate( position );
        glScale( scale_inv );
        drawRaw();
    }
    draw_grids();
}

void GuiView::drawRaw() {

    glColor(Color(255,0,0));
    drawRect( Vec2d::ZERO,Vec2d(20,20) );

    glColor(Color(0,255,0));
    drawRect( Vec2d(100,100),Vec2d(120,120) );

    // Draw background

//        Vec2d pivot = localToScreen(Vec2d::ZERO);
//        {
//            Vec2d tex_p1 = pivot;
//            Vec2d tex_size = localToScreen(cell_size * 512) - pivot;
//            Vec2d tex_p2 = tex_p1 + tex_size;
//
//            // Update sub pixels;
////            tex.updatePixels();
//////            tex.updateSubPixels(min_x,min_y,max_x,max_y);
////
////            glEnable(GL_TEXTURE_2D);
////            glBindTexture(GL_TEXTURE_2D, tex.textureId);
////
////            glColor4f(1, 1, 1, 1);
////            glBegin(GL_QUADS);
////
////            //glNormal3f(0, 0, 1);
////            glTexCoord2f(0.0f, 0.0f);
////            glVertex2d(tex_p1.x, tex_p1.y);
////            glTexCoord2f(1.0f, 0.0f);
////            glVertex2d(tex_p2.x, tex_p1.y);
////            glTexCoord2f(1.0f, 1.0f);
////            glVertex2d(tex_p2.x, tex_p2.y);
////            glTexCoord2f(0.0f, 1.0f);
////            glVertex2d(tex_p1.x, tex_p2.y);
////            glEnd();
////            // unbind texture
////            glBindTexture(GL_TEXTURE_2D, 0);
////            glDisable(GL_TEXTURE_2D);
//        }



}

Vec2d GuiView::screenToLocal(Vec2d pos) const {
    return (pos-position)*scale;
}

Vec2d GuiView::localToScreen(Vec2d pos) const {
    return (pos/scale)+position;
}

void GuiView::draw_background() {
    glColor(background_color);

    drawRect(Vec2d::ZERO,getSize());
}

void GuiView::draw_grids() {

    Vec2d pivot = localToScreen(Vec2d::ZERO);

    draw_grid(cell_size,min_displayed_cell_size_x, true, grid_primary_color, background_color,5);

    draw_grid(cell_size*highlight_step,min_displayed_cell_size_x*highlight_step, true, grid_secondary_color, grid_primary_color,4);

    draw_grid(cell_size*highlight_step*highlight_step,min_displayed_cell_size_x*highlight_step*highlight_step,
              true, grid_third_color, grid_secondary_color,3);


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

void
GuiView::draw_grid(Vec2d cell_size, double min_displayed_cell_size_x, bool dynamic, Color c1, Color c2, int max_level) {

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
            if (level < 0) break;

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
        double begin = (double) std::fmod(pivot.x, displayed_cell_size.x);
        if (begin < 0) begin += displayed_cell_size.x;
        double end = getSize().x;
        double step = displayed_cell_size.x;

        double y1 = 0;
        double y2 = getSize().y;

        glBegin(GL_LINES);
        for (double x = begin; x < end; x+=step ) {
            glVertex2d(x,y1);
            glVertex2d(x,y2);
        }
        glEnd();
    }

    {
        // Draw horisontal lines
        double begin = (double) std::fmod(pivot.y, displayed_cell_size.y);
        if (begin < 0) begin += displayed_cell_size.y;
        double end = getSize().y;
        double step = displayed_cell_size.y;

        double x1 = 0;
        double x2 = getSize().x;

        glBegin(GL_LINES);
        for (double y = begin; y < end; y+=step ) {
            glVertex2d(x1,y);
            glVertex2d(x2,y);
        }
        glEnd();
    }
}
