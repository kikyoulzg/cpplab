#include "dc.h"
#include <iostream>
#include <cctype>

lexer::token_value lexer::curr_tok ;//= PRINT;
double lexer::number_value;
std::string lexer::string_value;

lexer::token_value lexer::get_token()
{
    char ch;
    using namespace std;

   
    do {
        if(!cin.get(ch)) return curr_tok = END;
    } while(ch != '\n' && isspace(ch));
    switch (ch){
    case ';':
    case '\n':
        return curr_tok = PRINT;
    case '*':
    case '/':
    case '-':
    case '+':
    case '(':
    case ')':
    case '=':
        return curr_tok = token_value(ch);
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        cin.putback(ch);
        cin >>  number_value;
        return curr_tok=NUMBER;
    default:
        if (isalpha(ch)) {
            string_value = ch;
            while (cin.get(ch) && isalnum(ch)) string_value.push_back(ch);
            cin.putback(ch);
            return curr_tok=NAME;
        }
        throw error::syntax_error("bad token");
    }
}
