#include "dc.h"

double parser::prim(bool get)
{
    /* map<string,double>table;
    double error(const string&);
    token_value get_token();
    double expr(bool);*/
    if(get) get_token();

    switch(curr_tok) {
    case lexer::NUMBER:
    {
        double v = lexer::number_value;
        get_token();
        return v;
    }
    case lexer::NAME:
    {
        double& v = table[lexer::string_value];
        if(get_token() == lexer::ASSIGN) v = expr(true);
        return v;
    }
    case lexer::MINUS:
        return -prim(true);
    case lexer::LP:
    {
        double e = expr(true);
        if(curr_tok != lexer::RP) throw error::syntax_error("')' expected") ;
        get_token();
        return e;
    }
    case lexer::END:
        return 1;
    default:
        throw error::syntax_error("primary expected");
    }
}

double parser::term(bool get)
{
    // double error(const string&);
    //double prim(bool);
    double left = prim(get);
    for (;;)
        switch(curr_tok) {
        case lexer::MUL:
            left *= prim(true);
            break;
        case lexer::DIV:
            if (double d = prim(true)) {
                left /= d;
                break;
            }
            throw error::zero_divide();
        default:
            return left;
        }
}

double parser::expr(bool get)
{
    double term(bool);
    double left = term(get);
    for (;;)
        switch (curr_tok){
        case lexer::PLUS:
            left += term(true);
            break;
        case lexer::MINUS:
            left -= term(true);
            break;
        default:
            return left;
        }
}

