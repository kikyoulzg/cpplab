#include "dc.h"
#include <sstream>
#include <iostream>

int driver::no_of_errors = 0;
std::istream* driver::input=0;

void driver::skip()
{
    no_of_errors++;
    while (*input) {
        char ch;
        input ->get(ch);
        switch(ch){
        case '\n':
        case ';':
            return;
        }
    }
    }

int main(int argc, char* argv[])
{
    using namespace std;
    using namespace driver;


    map<string,double>table;
    switch (argc) {
    case 1: 
        input = &cin;
        break;
    case 2:
        input = new istringstream(argv[1]);
        break;
default:
    cerr<<"too many arguments\n";
    return 1;
        }
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    while (*input){
        try{
            lexer::get_token();
            if(lexer::curr_tok == lexer::END)break;
            if(lexer::curr_tok == lexer::PRINT)continue;
            cout << parser::expr(false) << '\n';
        }
        catch(error::zero_divide){
            cerr << "attempt to divide by zero\n";
            if (lexer::curr_tok != lexer::PRINT)skip();
            ++driver::no_of_errors;       
}
        catch(error::syntax_error e){
            cerr << "syntax error:" <<e.p <<"\n";
            if (lexer::curr_tok != lexer::PRINT)skip();
            ++driver::no_of_errors;
        }
    }
    if(driver::input != &std::cin)delete driver::input;
    return driver::no_of_errors;
    }

