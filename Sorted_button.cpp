#include "Sorted_button.h"

Sorted_button::Sorted_button(int X, int Y, int W, int H, const char* L, int id)
    : Fl_Button(X, Y, W, H, L)
    , id(id)
{
}

int Sorted_button::getid()
/*
    Return id of buttom
*/
{
    return id;
}

void Sorted_button::setid(int new_id)
{
    id = new_id;
}

bool Sorted_button::operator==(Sorted_button b)
{
    return id == b.getid();
}

bool Sorted_button::cmp(Sorted_button a, Sorted_button b)
/*
*/
{
    return a.getid() < b.getid();
}
