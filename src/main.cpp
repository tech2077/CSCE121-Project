#include <Deck_generator.h>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Window.H>
#include <Leaderboard.h>
#include <Parser.h>
#include <Player.h>
#include <Sorted_button.h>
#include <Tile_selector.h>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


// Text constants
const char* title_text = "Numerophile!";
const char* member_text = "Matthew Skolaut\nRyan Terry\nSharon Sims";
const char* help_text = "The object of the game is to rearrange a certain number\nof tiles (each labelled with a digit or an operator) to yield\nthe highest arithmetic value. For example, the three tiles\n'3', '5', and '+' could be rearranged to 3+5 = 8,\n5+3 = 8, +35 = 35, or +53 = 53. Since +53 has the\nhighest value, that is the best move.  If 35+ or 53+ is chosen,\nthe score is zero since that is not a “well-formed\nformula” in arithmetic (in other words, it is an illegal move).\nEnter initials and press start to begin!";

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
    <Over 24 lines due to additional complexity
    and memory management requirements would
    be introduced by diving function further>

    Callback for game tiles
    Toggles position and calculates sum
    Determines game end
    writes scores out
    asks for replay
*/
{
    Sorted_button* b = (Sorted_button*)o; // Cast tile button that callback was called from
    void** d = (void**)data;
    Tile_selector* lists = (Tile_selector*)d[0]; // get tile selector for button
    Fl_Multiline_Output* scorebox = (Fl_Multiline_Output*)d[1]; // get scorebox

    b->hide(); // hide button
    lists->toggle_button(b); // toggle row button is on

    Parser parser; // make parser for expression
    std::string expression; // expression string
    double value = 0; // output value for expression

    for (auto but : lists->get_bottom()) // for loop to build expression string
        expression += but->label();

    try { // error checking
        value = parser.parse_expression(expression + "="); // parse expression
    } catch (std::logic_error& e) {
        value = 0; // otherwise 0
    }

    char outbuf[20];
    sprintf(outbuf, "%.2f", value); // format score value

    lists->set_total(outbuf); // set output to value of expression
    lists->redraw(); // redraw tiles

    if (lists->get_top().size() == 0) { // end of game
        for (auto but : lists->get_bottom()) // for loop to remove callback
            but->callback(b->default_callback);

        std::string scores(std::string(scorebox->value()) + " " + outbuf); // String of players and scores

        Leaderboard l(std::string("Difficulty: ")+ std::to_string(lists->get_size()) + ".txt"); // Leaderboard object

        l.loadString(scores); // load scores from string
        l.writeFile(); // write scores to file

        scorebox->value(l.writeString().c_str()); // write scores to leaderboard

        b->parent()->begin(); // open window additions
        Fl_Button* restart = new Fl_Button(400, 0, 100, 50, "Restart?"); // ask to replay
        restart->callback(start_cb); // attach callback
        b->parent()->end(); // end window additions
    }
}

void start_cb(Fl_Widget* o, void* data)
/*
    Callback for start button on splash
    Changes window layout and sets
    instruction screen
*/
{
    // window from parent method
    Fl_Window* w = (Fl_Window*)o->parent();

    // window editable
    w->begin();

    // delete widgets
    for (int i = w->children(); i >= 0; i--) {
        Fl_Widget* widg = w->child(i);
        w->remove(widg);
    }

    // start scren and close window editting 
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
    for (int i = w->children(); i >= 0; i--)
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
    Fl_Slider* s = (Fl_Slider*)o; // slider object 
    Fl_Multiline_Output* out = (Fl_Multiline_Output*)data; // cast scorelist from provided data

    std::string filename("Difficulty: "); // filename base
    Leaderboard l(filename + std::to_string((int)s->value()) + ".txt"); // leaderboard object

    l.loadFile(); // load scores
    out->value(l.writeString().c_str()); // write scores to score list

    s->copy_label((filename + std::to_string((int)s->value())).c_str()); // set label for difficulty
}

void set_game(Fl_Window* window, int level, const char* name)
/*
    Setups game screen layout for game
*/
{
    int button_size = 50; // size constants
    int x_button_spacing = 20, y_button_spacing = 50;
    int init_x = 175, init_y = 50;

    // GUI widgets
    Fl_Box* scorebox_label = new Fl_Box(0, 30, 80, 20, "High Scores");
    Fl_Multiline_Output* scorebox = new Fl_Multiline_Output(0, 50, 150, 200);

    Leaderboard l(std::string("Difficulty: ")+ std::to_string(level) + ".txt"); // Leaderboard object

    // loadfile and write out scores to scorelist
    l.loadFile();
    scorebox->value((l.writeString() + name).c_str());

    // generate tiles 
    Deck_Generator generator(level);
    generator.generate_deck();
    std::vector<std::string> name_list = generator.get_deck();

    // create tile row and selector
    Tile_selector* selector = new Tile_selector(init_x, init_y, x_button_spacing, y_button_spacing, button_size, button_size, tile_cb, (void*)scorebox);
    selector->add_buttons(name_list);
}

void start_screen(Fl_Window* window)
/*
    Setup start screen
*/
{
    Fl_Box* help_box = new Fl_Box(250, 40, 100, 30, help_text); // Widgets
    Fl_Button* begin = new Fl_Button(275, 200, 150, 80, "Begin");
    Fl_Box* scorebox_label = new Fl_Box(0, 30, 80, 20, "High Scores");
    Fl_Multiline_Output* scorebox = new Fl_Multiline_Output(0, 50, 150, 300);
    Fl_Input* name = new Fl_Input(275, 110, 150, 30, "Initials: ");
    Fl_Slider* difficulty = new Fl_Slider(FL_HORIZONTAL, 275, 150, 150, 30, "Difficulty: 3");

    help_box->labelsize(10); // Font details
    difficulty->bounds(3, 7);
    difficulty->value(3);
    difficulty->step(1);

    Leaderboard l(std::string("Difficulty: ") + std::to_string((int)difficulty->value()) + ".txt");
    l.loadFile(); // load file to leaderboard
    scorebox->value(l.writeString().c_str());

    void** data = new void*[2]; // void array to pass extra data to callback

    data[0] = (void*)difficulty; // assign data to array
    data[1] = (void*)name;

    difficulty->callback(slider_cb, (void*)scorebox); // set callbacks
    begin->callback(begin_cb, (void*)data);
}

void splash_screen(Fl_Window* window)
/*
    Setup splash screen
*/
{
    // setup splash text
    Fl_Box* title_box = new Fl_Box(300, 10, 100, 50, title_text);
    Fl_Box* member_box = new Fl_Box(300, 60, 100, 80, member_text);
    Fl_Button* start = new Fl_Button(275, 200, 150, 80, "Start!");

    // adjust fonts
    title_box->labelsize(60);
    member_box->labelsize(20);
    start->labelsize(60);

    // attach callback
    start->callback(start_cb);
}

int main(int argc, char** argv)
/*
    Application main loop
*/
{
    // new window for program
    Fl_Window* window = new Fl_Window(700, 300);

    // start splash screen
    splash_screen(window);

    // close window
    window->end();
    //show window
    window->show(argc, argv);

    // GUI loop
    return Fl::run();
}
