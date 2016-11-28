#ifndef TILE_SELECTOR_H
#define TILE_SELECTOR_H

#include "Sorted_button.h"
#include <FL/Fl_Widget.H>
#include <FL/Fl_Output.H>
#include <algorithm>
#include <string>
#include <vector>

class Tile_selector {
public:
    Tile_selector(int x, int y, int x_spacing, int y_spacing, int x_tile_size, int y_tile_size, Fl_Callback* callback);
    ~Tile_selector();
    void redraw();
    void add_buttons(std::vector<std::string> names);
    void move_to_bottom();
    void move_to_top();
    void toggle_button(Sorted_button* b);
    std::vector<Sorted_button*> get_top();
    std::vector<Sorted_button*> get_bottom();
    void set_total(const char* text);

private:
    std::vector<Sorted_button*> top; // top row
    std::vector<Sorted_button*> bottom; // bottom row
    int x; // right alignment coordinate
    int top_y; // top y coordinate
    int x_spacing; // vertical spacing between top and bottom row
    int y_spacing; // horizontal spacing between tiles
    int x_tile_size; // x size of tile
    int y_tile_size; // y size of tile
    Fl_Callback* tile_callback; // callback for all tile buttons
    int bottom_y; // bottom y coordinate
    Fl_Output* total; // output space for selector
};

#endif