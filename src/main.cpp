#include <Sorted_button.h>
#include <Tile_selector.h>
#include <Deck_generator.h>
#include <Parser.h>
#include <Player.h>
#include <Leaderboard.h>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Output.H>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <stdexcept>
#include <sstream>


void tile_cb(Fl_Widget* o, void* data);
void start_cb(Fl_Widget* o, void* data);
void begin_cb(Fl_Widget* o, void* data);
void back_cb(Fl_Widget* o, void* data);
void slider_cb(Fl_Widget* o, void* data);
void set_game(Fl_Window* window, int level, const char* name);
void start_screen(Fl_Window* window);
void start_screen(Fl_Window* window);

void tile_cb(Fl_Widget* o, void* data)
/*
    Callback for game tiles
    Toggles position and calculates sum
*/
{
    Sorted_button* b = (Sorted_button*)o; // Cast tile button that callback was called from
    void** d = (void**)data;
    Tile_selector* lists = (Tile_selector*)d[0]; // get tile selector for button
    Fl_Multiline_Output* scorebox = (Fl_Multiline_Output*)d[1];

    b->hide(); // hide button
    lists->toggle_button(b); // toggle row button is on

    Parser parser; // make parser for expression
    std::string expression; // expression string
    double value = 0; // output value for expression

    for (auto but : lists->get_bottom()) { // for loop to build expression string
        expression += but->label(); 
    }
    //expression = expression + "="; // tack on output token

    try { // error checking
        value = parser.parse_expression(expression + "="); // parse expression
    } catch(std::logic_error &e) {
        value = 0; // otherwise 0
    }

    char outbuf[20];

    sprintf(outbuf, "%.2f", value);

    lists->set_total(outbuf); // set output to value of expression
    lists->redraw(); // redraw tiles

    if(lists->get_top().size() == 0) { // end of game
        for (auto but : lists->get_bottom()) // for loop to remove callback
            but->callback(b->default_callback);

            char label[20];

            std::sprintf(label, "Difficulty: %d", lists->get_size()); 
            try{
                std::string filename(label);
                std::stringstream buf;
                Leaderboard l(filename+".txt");
                Player p;

                buf << scorebox->value();

                buf << " " << outbuf << std::endl;

                while(buf >> p){
                    l.addPlayer(p);
                }

                l.writeFile();

                scorebox->value(buf.str().c_str());
            } catch(const std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }

        b->parent()->begin();
        Fl_Button* restart = new Fl_Button(400, 0, 100, 50, "Restart?");
        restart->callback(start_cb);
        b->parent()->end();
    }
}

void start_cb(Fl_Widget* o, void* data)
/*
    Callback for start button on splash
    Changes window layout and sets
    instruction screen
*/
{
    Fl_Window* w = (Fl_Window*)o->parent();
    w->begin();
    for(int i = w->children(); i >= 0; i--) {
        Fl_Widget* widg = w->child(i);
        w->remove(widg);
    }

    start_screen(w);
    w->end();
    w->redraw();
}

void begin_cb(Fl_Widget* o, void* data)
/*
    Callback for begin button on instruction
    Changes window layout and begins
    game
*/
{
    Fl_Window* w = (Fl_Window*)o->parent();
    void** d = (void**)data;
    Fl_Slider* s = (Fl_Slider*)d[0];
    Fl_Input* in = (Fl_Input*)d[1];
    //Fl_Slider* s = (Fl_Slider*)data;

    w->begin();
    for(int i = w->children(); i >= 0; i--) 
        w->remove(w->child(i));

    set_game(w, (int)s->value(), in->value());
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
    Fl_Multiline_Output* out = (Fl_Multiline_Output*)data;

    char label[20];

    std::sprintf(label, "Difficulty: %d", (int)s->value());

    try{
        std::string filename(label);
        std::stringstream buf;
        Leaderboard l(filename+".txt");
        l.loadFile();
        for(auto p : l.getPlayers()){
            buf << p << std::endl;
        }

        out->value(buf.str().c_str());
    } catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    s->copy_label(label);
}

void set_game(Fl_Window* window, int level, const char* name)
/*
    Setups game screen layout for game
*/
{
    int button_size = 50;
    int x_button_spacing = 20;
    int y_button_spacing = 50;
    int init_x = 175;
    int init_y = 50;

    Fl_Box* scorebox_label = new Fl_Box(0,30,80,20,"High Scores");
    Fl_Multiline_Output* scorebox = new Fl_Multiline_Output(0,50,150,200);

    char label[20];

    std::sprintf(label, "Difficulty: %d", level);

    try{
        std::string filename(label);
        std::stringstream buf;
        Leaderboard l(filename+".txt");
        l.loadFile();
        for(auto p : l.getPlayers()){
            buf << p << std::endl;
        }

        buf << name;

        scorebox->value(buf.str().c_str());
    } catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    Deck_Generator generator(level);

    generator.generate_deck();

    std::vector<std::string> name_list = generator.get_deck();

    Tile_selector* selector = new Tile_selector(init_x, init_y, x_button_spacing, y_button_spacing, button_size, button_size, tile_cb, (void*)scorebox);

    selector->add_buttons(name_list);
}

void start_screen(Fl_Window* window)
/*
    Setup start screen
*/
{
    const char* help_text = "The object of the game is to rearrange a certain number\nof tiles (each labelled with a digit or an operator) to yield\nthe highest arithmetic value. For example, the three tiles\n'3', '5', and '+' could be rearranged to 3+5 = 8,\n5+3 = 8, +35 = 35, or +53 = 53. Since +53 has the\nhighest value, that is the best move.  If 35+ or 53+ is chosen,\nthe score is zero since that is not a “well-formed\nformula” in arithmetic (in other words, it is an illegal move)";
    Fl_Box* help_box = new Fl_Box(250, 30, 100, 30, help_text);
    help_box->labelsize(10);
    Fl_Button* begin = new Fl_Button(275, 200, 150, 80, "Begin");
    Fl_Box* scorebox_label = new Fl_Box(0,30,80,20,"High Scores");
    Fl_Multiline_Output* scorebox = new Fl_Multiline_Output(0,50,150,300);
    Fl_Input* name = new Fl_Input(275, 110, 150, 30, "Name: ");
    Fl_Slider* difficulty = new Fl_Slider(FL_HORIZONTAL, 275, 150, 150, 30, "Difficulty: 3");
    difficulty->bounds(3, 7);
    difficulty->value(3);
    difficulty->step(1);

    void** data;
    data = new void* [2];

    data[0] = (void*)difficulty;
    data[1] = (void*)name;

    difficulty->callback(slider_cb, (void*)scorebox);

    //begin->callback(begin_cb, (void*)difficulty);
    begin->callback(begin_cb, (void*)data);
}

void splash_screen(Fl_Window* window)
/*
    Setup splash screen
*/
{
    const char* title_text = "Numerophile!";
    const char* member_text = "Matthew Skolaut\nRyan Terry\nSharon";
    Fl_Box* title_box = new Fl_Box(300, 10, 100, 50, title_text);
    Fl_Box* member_box = new Fl_Box(300, 60, 100, 80, member_text);
    Fl_Button* start = new Fl_Button(275, 200, 150, 80, "Start!");

    title_box->labelsize(60);
    member_box->labelsize(20);
    start->labelsize(60);

    start->callback(start_cb);
}

int main(int argc, char** argv)
/*
    Application main loop
*/
{
    Fl_Window* window = new Fl_Window(700, 300);

    splash_screen(window);

    window->end();
    window->show(argc, argv);

    return Fl::run();
}
