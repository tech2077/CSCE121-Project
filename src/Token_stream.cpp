#include "Token_stream.h"

Token_stream::Token_stream()
/*
    The constructor just sets full to
    indicate that the buffer is empty
    Constructor for cin
*/
:full(false), buffer(0)    // no Token in buffer
{
    stream = &std::cin;
}

Token_stream::Token_stream(std::string instring)
/*
    The constructor just sets full to
    indicate that the buffer is empty
    Constructor for string
*/
:full(false), buffer(0)    // no Token in buffer
{
    stream = new std::stringstream(instring);
}


void Token_stream::putback(Token t)
/*
    putback() member function puts its argument
    back into the Token_stream's buffer:
*/
{
    if (full) throw std::logic_error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
/*
    get() returns the next token
    from the Token_stream
*/
{
    if (full) { // do we already have a Token ready?
        full=false; // remove token from buffer
        return buffer;
    }
    char ch;
    *stream >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
    switch (ch) {
    case '=':    // for "print"
    case 'x':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/': case '!':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {    
            stream->putback(ch);         // put digit back into the input stream
            double val;
            *stream >> val;              // read a floating-point number
            return Token('8',val);   // let '8' represent "a number"
        }
    default: throw std::logic_error("Bad Token");
    }
}