#include "Tile_selector.h"
#include <iostream>

Tile_selector::Tile_selector(int x, int y, int x_spacing, int y_spacing, int x_tile_size, int y_tile_size, Fl_Callback* callback, void* data)
/*
    Constructor for Tile_selector
*/
    : x(x)
    , top_y(y)
    , x_spacing(x_spacing + x_tile_size)
    , y_spacing(y_spacing + y_tile_size)
    , x_tile_size(x_tile_size)
    , y_tile_size(y_tile_size)
    , tile_callback(callback)
    , data(data)
{
    // calculate spacing
    bottom_y = y + y_tile_size + y_spacing;
    // scorebox
    total = new Fl_Output(200,5,175,40,"Current Score");
    // font settings
    total->textsize(20);
    total->labelsize(17);
}

Tile_selector::~Tile_selector()
/*
    Class destructor
*/
{
    delete total;

    for(Sorted_button* b : top)
        delete b;

    for(Sorted_button* b : bottom)
        delete b;
}

void Tile_selector::add_buttons(std::vector<std::string> names)
/*
    Take a vector of names and turn into buttons
*/
{
    // Set size of selector
    size = names.size();

    void** packed_data;
    packed_data = new void* [2];

    packed_data[0] = (void*)this;
    packed_data[1] = (void*)data;

    // Go through vector of names and line buttons up on top row onto 
    // top vector
    for (unsigned int i = 0; i < names.size(); i++) {
        std::string* num_label = new std::string(names[i]);
        Sorted_button* b = new Sorted_button(x + x_spacing * i, top_y, x_tile_size, y_tile_size, num_label->c_str(), i);
        b->callback(tile_callback, (void*)packed_data);
        top.push_back(b);
    }
}

void Tile_selector::redraw()
/*
    Redraw each tile im bottom and top row
*/
{
    // Draw top row tile buttons
    for (unsigned int i = 0; i < top.size(); i++) {
        top[i]->hide();
        top[i]->position(x + x_spacing * top[i]->getid(), top_y);
        top[i]->show();
    }

    // Drawing bottom row tile buttons
    for (unsigned int i = 0; i < bottom.size(); i++) {
        bottom[i]->hide();
        bottom[i]->position(x + x_spacing * i, bottom_y);
        bottom[i]->show();
    }
}

void Tile_selector::toggle_button(Sorted_button* b)
/*
    Move button from one row to other
*/
{
    // Find position of button if in top
    std::vector<Sorted_button*>::iterator tpos = find(top.begin(), top.end(), b);

    // if in top move to bottom
    if (tpos != top.end()) {
        top.erase(tpos, tpos + 1);
        bottom.push_back(b);
    } else {
        // else in bottom move to top
        std::vector<Sorted_button*>::iterator bpos = find(bottom.begin(), bottom.end(), b);
        bottom.erase(bpos, bpos + 1);
        top.push_back(b);
    }
}

std::vector<Sorted_button*> Tile_selector::get_top()
/*
    Return vector of top button pointers
*/
{
    return top;
}

std::vector<Sorted_button*> Tile_selector::get_bottom()
/*
    Return vector of bottom button pointers
*/
{
    return bottom;
}

void Tile_selector::set_total(const char *text)
/*
    Set text of total output
*/
{
    total->value(text);
}