#include "Sorted_button.h"
#include "Tile_selector.h"
#include "Deck_Generator.h"
#include "Parser.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <stdexcept>

void tile_cb(Fl_Widget* o, void* data);
void start_cb(Fl_Widget* o, void* data);
void back_cb(Fl_Widget* o, void* data);
void slider_cb(Fl_Widget* o, void* data);
void set_game(Fl_Window* window, int level);
void start_screen(Fl_Window* window);

void tile_cb(Fl_Widget* o, void* data)
/*
    Callback for game tiles
    Toggles position and calculates sum
*/
{
    Sorted_button* b = (Sorted_button*)o; // Cast tile button that callback was called from
    Tile_selector* lists = (Tile_selector*)data; // get tile selector for button

    b->hide(); // hide button
    lists->toggle_button(b); // toggle row button is on

    Parser parser; // make parser for expression
    std::string expression; // expression string
    int value = 0; // output value for expression

    for (auto but : lists->get_bottom()) { // for loop to build expression string
        expression += but->label(); 
    }
    expression = expression + "="; // tack on output token

    std::cout << expression << std::endl;

    try { // error checking
        value = parser.parse_expression(expression); // parse expression
    } catch(std::logic_error &e) {
        std::cout << "Error: " << e.what() << std::endl;
        value = 0; // otherwise 0
    }

    lists->set_total(std::to_string(value).c_str()); // set output to value of expression
    lists->redraw(); // redraw tiles
}

void start_cb(Fl_Widget* o, void* data)
/*
    Callback for start button on splash
    Changes window layout and begins
    game
*/
{
    void** d = (void**)data;
    Fl_Window* w = (Fl_Window*)d[0];
    Fl_Slider* s = (Fl_Slider*)d[1];
    w->clear();
    w->begin();
    set_game(w, (int)s->value());
    w->end();
    w->redraw();
}

void back_cb(Fl_Widget* o, void* data)
{
    void** d = (void**)data;
    Fl_Window* w = (Fl_Window*)d[0];
    Tile_selector* lists = (Tile_selector*)d[1]; // get tile selector for button

    //delete lists;
    w->clear();
    w->begin();
    start_screen(w);
    w->end();
    w->redraw();
}

void slider_cb(Fl_Widget* o, void* data)
/*
    Callback for the difficulty slider
    sets the difficulty for the game
*/
{
    Fl_Slider* s = (Fl_Slider*)o;

    char label[20];

    std::sprintf(label, "Difficulty: %d", (int)s->value());

    s->copy_label(label);
}

void set_game(Fl_Window* window, int level)
/*
    Setups game screen layout for game
*/
{
    int button_size = 50;
    int x_button_spacing = 20;
    int y_button_spacing = 50;
    int init_x = 150;
    int init_y = 50;

    Deck_Generator generator(level);

    generator.generate_deck();

    std::vector<std::string> name_list = generator.get_deck();

    Tile_selector* selector = new Tile_selector(init_x, init_y, x_button_spacing, y_button_spacing, button_size, button_size, tile_cb);

    Fl_Button* back = new Fl_Button(300, 300, 50, 50, "Back");

    void* data[2];
    data[0] = (void*)window;
    data[1] = (void*)selector;
    back->callback(back_cb, (void*)data);

    selector->add_buttons(name_list);
}

void start_screen(Fl_Window* window)
/*
    Setup start splash screen
*/
{
    Fl_Button* start = new Fl_Button(300, 300, 50, 50, "Start");
    Fl_Slider* difficulty = new Fl_Slider(FL_HORIZONTAL, 200, 200, 100, 10, "Difficulty: 3");
    difficulty->bounds(3, 7);
    difficulty->value(3);
    difficulty->step(1);
    difficulty->callback(slider_cb);
    void* data[2];
    data[0] = (void*)window;
    data[1] = (void*)difficulty;
    start->callback(start_cb, (void*)data);
}

int main(int argc, char** argv)
/*
    Application main loop
*/
{
    Fl_Window* window = new Fl_Window(700, 400);

    char* help_text = "The object of the game is to rearrange a certain number \nof tiles (each labelled with a digit or an operator) to \nyield the highest arithmetic value.\nFor example, the three tiles '3', '5', and '+' could be rearranged to 3+5 = 8,\n5+3 = 8, +35 = 35, or +53 = 53. Since +53 has the\nhighest value, that is the best move.  If 35+ or 53+ is chosen,\nthe score is zero since that is not a “well-formed formula” \n in arithmetic (in other words, it is an illegal move)";
    Fl_Box* help_box = new Fl_Box(30, 30, 100, 30, help_text);
    help_box->labelsize(5);
    Fl_Button* start = new Fl_Button(300, 300, 50, 50, "Start");
    Fl_Slider* difficulty = new Fl_Slider(FL_HORIZONTAL, 200, 200, 100, 10, "Difficulty: 3");
    difficulty->bounds(3, 7);
    difficulty->value(3);
    difficulty->step(1);
    difficulty->callback(slider_cb);
    void* data[2];
    data[0] = (void*)window;
    data[1] = (void*)difficulty;
    start->callback(start_cb, (void*)data);

    window->end();
    window->show(argc, argv);

    return Fl::run();
}
