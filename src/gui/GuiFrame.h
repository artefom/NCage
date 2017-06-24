//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_GUIFRAME_H
#define PLAYIN_GUIFRAME_H

#include <vector>
#include <glutUtils.h>
#include <memory.h>
#include <mathUtils.h>
#include <unordered_map>
#include <utils/FBTexture.h>

#include "resources/constants.h"
#include "GuiBase.h"
#include "ProjectionManager.h"


class GuiFrame : public GuiBase {
protected:

    // Sub-elements of frame
    // Order of elements in this vector is responsible
    // for drawing order and click processing
    // To move Gui Element on top, put it on top of this vector.
    std::vector< std::shared_ptr<GuiBase> > children;

    // Gui that lies under mouse.
    std::shared_ptr<GuiBase> MouseGui;

    std::unordered_map< int,std::shared_ptr<GuiBase> > ClickedGuis;

    constants::FRAME_CULL_MODE cull_mode;

    FBTexture cull_tex;

    Vec2i scissor_min;
    Vec2i scissor_size;

    bool resized;

public:

    //Vec2d texture_span;


    GuiFrame(const std::weak_ptr<GuiFrame>&& i_self,
             constants::FRAME_CULL_MODE i_cull_mode = constants::CULL_TEXTURE);

    void setRenderMode(constants::FRAME_CULL_MODE mode);

    // Update texture size when cull_mode is CULL_TEXTURE
    // Does not redraw children objects
    void updateTexture();

    // Update scissor position when cull_mode is CULL_SCISSOR
    // Sets scissor boundaries to match current frame in pixel coordinates
    // by projecting frame boundaries into pixels
    // (see gluProject(), ProjectManager::project_i )
    void updateScissor();

    constants::FRAME_CULL_MODE getRenderMode() const;

    // Mouse event in relative coordinates
    // Internal function (tight bounds)
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos);

    virtual void OnMouseEnter();

    virtual void OnMouseLeave();

    // Mouse event when cursor moves over current gui instance
    virtual void OnMouseMove(Vec2d mousePos);

    // Setups everything to be rendered into texture through FBO
    // Pushes new Viewport and binds frame buffer, resets scissor box
    // All this is done through FBTexture class with method FBTexture::bind()
    // this method estimates texture size (in pixels) through unprojecting current position
    // see (ProjectionManager::project_i)
    virtual void pushBuffer();

    // Draws frame and its children into screen or int texture (if pushBuffer was called before)
    virtual void draw();

    // Undrolls changes of pushBuffer() into Viewport/Scissor/FBO settings
    virtual void popBuffer();


    // Draw frame and its children into screen
    // (Texture can be drawn if no changes were made (see Update()) since last draw)
    virtual void drawBuffered();

    // Add new element to current window. This element should have self member to be set to refer itself's class
    // Like so
    // Class A { std::weak_ref<A> self{this}
    // sadly, this is hard to be accomplished in normal ways, so pointer to self is passed as parameter to
    // constructor of Any gui class by GuiFactory (which should be used to create any gui class)
    virtual void add(std::shared_ptr<GuiBase> gui);

    // Function, called after resize
    // Sets flags, so window knows it's been resized and update is needed
    // (texture resize in case cull_mode == CULL_TEXTURE)
    // Also, calles Update()
    virtual void afterResize();


    // Mouse Scroll occured!
    virtual void OnScroll(Vec2d scale);

};


#endif //PLAYIN_GUIFRAME_H
