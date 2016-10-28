#ifndef SORTED_BUTTON_H
#define SORTED_BUTTON_H

#include <FL/Fl_Button.H>

class Sorted_button : public Fl_Button {
public:
    Sorted_button(int X, int Y, int W, int H, const char* L = 0, int id = 0);
    int getid();
    void setid(int new_id);
    bool operator==(Sorted_button b);
    static bool cmp(Sorted_button a, Sorted_button b);

private:
    int id;
};

#endif