#include "Sorted_button.h"

Sorted_button::Sorted_button(int X, int Y, int W, int H, const char* L, int id)
    : Fl_Button(X, Y, W, H, L)
    , id(id)
/*
    Constructor for sorted button
    An extension of button in order to easily be sorted in tile selector
*/
{}

int Sorted_button::getid()
/*
    Return id of buttom
*/
{
    return id;
}

void Sorted_button::setid(int new_id)
/*
    Set id of button
*/
{
    id = new_id;
}

bool Sorted_button::operator==(Sorted_button b)
/*
    Compare buttons via id
*/
{
    return id == b.getid();
}

bool Sorted_button::cmp(Sorted_button a, Sorted_button b)
/*
    Use to sort buttons via custom comparison function
*/
{
    return a.getid() < b.getid();
}
