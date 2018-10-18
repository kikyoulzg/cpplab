#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>

std::map<std::string,double>table;

namespace parser{         
double prim(bool get);
double term(bool get);
double expr(bool get);

using lexer::get_token;
using lexer::curr_tok;
}

namespace parser{
double expr(bool);
}

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


namespace lexer{
enum token_value {
    NAME, NUMBER, END,
    PLUS='+', MINUS='-', MUL='*', DIV='/',
    PRINT=';', ASSIGN='=', LP='(', RP=')'
}
 extern token_value curr_tok ;//= PRINT;
extern   double number_value;//为什么这里用了extern，parser那些名字空间的声明就不用呢
 extern   std::string string_value;
          char ch;
token_value get_token();
}

lexer::token_value lexer::curr_tok ;//= PRINT;
double lexer::number_value;
std::string lexer::string_value;

lexer::token_value lexer::get_token()
{
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


namespace error {
struct zero_divide(){ };
struct syntax_error
{
    const char* p;
    syntax_error(const char* q){p =q;}
};
}


namespace driver{
int driver::no_of_errors = 0;
std::istream* driver::input=0;
void skip();
}

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
    error ("too many arguments");
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
        catch(error::syntax_error){
            cerr << "syntax error:" <<e.p <<"\n";
            if (lexer::curr_tok != lexer::PRINT)skip();
            ++driver::no_of_errors;
        }
    }
    if(input != &cin)delete input;
    return no_of_errors;
    
}



