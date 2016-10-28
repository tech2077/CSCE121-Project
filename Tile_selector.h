#ifndef TILE_SELECTOR_H
#define TILE_SELECTOR_H

#include "Sorted_button.h"
#include <FL/Fl_Widget.H>
#include <algorithm>
#include <string>
#include <vector>

class Tile_selector {
public:
    Tile_selector(int x, int y, int x_spacing, int y_spacing, int x_tile_size, int y_tile_size, Fl_Callback* callback);
    void redraw();
    void add_buttons(std::vector<std::string> names);
    void move_to_bottom();
    void move_to_top();
    void toggle_button(Sorted_button* b);

private:
    std::vector<Sorted_button*> top;
    std::vector<Sorted_button*> bottom;
    int x;
    int top_y;
    int x_spacing;
    int y_spacing;
    int x_tile_size;
    int y_tile_size;
    Fl_Callback* tile_callback;
    int bottom_y;
};

#endif