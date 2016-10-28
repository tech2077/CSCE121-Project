#include "Sorted_button.h"
#include "Tile_selector.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <string>
#include <vector>

void tile_cb(Fl_Widget* o, void* data);
void start_cb(Fl_Widget* o, void* data);
void set_game();

void tile_cb(Fl_Widget* o, void* data)
/*
    Callback for game tiles
    Toggles position and calculates sum
*/
{
    Sorted_button* b = (Sorted_button*)o;
    Tile_selector* lists = (Tile_selector*)data;

    b->hide();

    std::cout << "ID: " << b->getid() << std::endl;

    lists->toggle_button(b);

    lists->redraw();

    b->show();
    b->redraw();
}

void start_cb(Fl_Widget* o, void* data)
/*
    Callback for start button on splash
    Changes window layout and 
*/
{
    Fl_Button* b = (Fl_Button*)o;
    Fl_Window* w = (Fl_Window*)data;
    b->hide();
    w->begin();
    set_game();
    w->end();
}

void set_game()
/*
    Setups game screen layout for game
*/
{
    int button_size = 50;
    int x_button_spacing = 20 + button_size;
    int y_button_spacing = 50 + button_size;
    int init_x = 50;
    int init_y = 50;

    std::vector<std::string> name_list = { "One", "Two", "Three", "Four", "Five" };

    Tile_selector* selector = new Tile_selector(init_x, init_y, x_button_spacing, y_button_spacing, button_size, button_size, tile_cb);

    selector->add_buttons(name_list);
}

int main(int argc, char** argv)
/*
    Application main loop
*/
{
    Fl_Window* window = new Fl_Window(700, 400);

    Fl_Button* start = new Fl_Button(300, 300, 50, 50, "Start");
    start->callback(start_cb, (void*)window);

    window->end();
    window->show(argc, argv);

    return Fl::run();
}
