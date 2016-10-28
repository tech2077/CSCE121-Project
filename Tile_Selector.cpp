#include "Tile_selector.h"
#include <iostream>

Tile_selector::Tile_selector(int x, int y, int x_spacing, int y_spacing, int x_tile_size, int y_tile_size, Fl_Callback* callback)
    : x(x)
    , top_y(y)
    , x_spacing(x_spacing)
    , y_spacing(y_spacing)
    , x_tile_size(x_tile_size)
    , y_tile_size(y_tile_size)
    , tile_callback(callback)
{
    bottom_y = y + y_tile_size + y_spacing;
}

void Tile_selector::add_buttons(std::vector<std::string> names)
{
    for (unsigned int i = 0; i < names.size(); i++) {
        std::string* num_label = new std::string(names[i]);
        Sorted_button* b = new Sorted_button(x + x_spacing * i, top_y, x_tile_size, y_tile_size, num_label->c_str(), i);
        b->callback(tile_callback, (void*)this);
        top.push_back(b);
    }
}

void Tile_selector::redraw()
{
    for (unsigned int i = 0; i < top.size(); i++) {
        top[i]->hide();
        top[i]->position(x + x_spacing * top[i]->getid(), top_y);
        top[i]->show();
    }

    for (unsigned int i = 0; i < bottom.size(); i++) {
        bottom[i]->hide();
        bottom[i]->position(x + x_spacing * i, bottom_y);
        bottom[i]->show();
    }
}

void Tile_selector::toggle_button(Sorted_button* b)
{

    std::vector<Sorted_button*>::iterator tpos = find(top.begin(), top.end(), b);

    if (tpos != top.end()) {
        top.erase(tpos, tpos + 1);
        bottom.push_back(b);
        std::cout << "Found\n";
    } else {
        std::vector<Sorted_button*>::iterator bpos = find(bottom.begin(), bottom.end(), b);
        bottom.erase(bpos, bpos + 1);
        top.push_back(b);
        std::cout << "Not Found\n";
    }
}