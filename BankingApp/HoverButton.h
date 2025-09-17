#pragma once
#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

//------------------------------------------------------------------------------------------------

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>

//------------------------------------------------------------------------------------------------

// Custom button with hover effect
class HoverButton : public Fl_Button {
    Fl_Color normal_color;
    Fl_Color hover_color;
    Fl_Color text_color;
    bool hovering = false;

public:
    HoverButton(int X, int Y, int W, int H, const char* L = 0)
        : Fl_Button(X, Y, W, H, L) {
        normal_color = fl_rgb_color(28, 43, 94);
        hover_color = fl_color_average(normal_color, FL_WHITE, 0.3f);
        text_color = FL_WHITE;

        box(FL_NO_BOX); // No default FLTK box
        labelfont(FL_HELVETICA_BOLD);
        labelsize(14);
    }

    int handle(int event) override {
        switch (event) {
        case FL_ENTER:
            hovering = true;
            redraw();
            return 1;
        case FL_LEAVE:
            hovering = false;
            redraw();
            return 1;
        default:
            return Fl_Button::handle(event);
        }
    }

    void draw() override {
        // Choose fill color based on hover state
        Fl_Color fill = hovering ? hover_color : normal_color;

        // Draw a rounded filled rectangle
        fl_draw_box(FL_ROUNDED_BOX, x(), y(), w(), h(), fill);

        // Draw the label on top
        fl_color(text_color);
        draw_label();
    }
};
#endif

//------------------------------------------------------------------------------------------------