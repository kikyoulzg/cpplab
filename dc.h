namespace error {
struct zero_divide{ };
struct syntax_error
{
    const char* p;
    syntax_error(const char* q){p = q;}
};
}

#include <string>

namespace lexer{
enum token_value {
    NAME, NUMBER, END,
    PLUS='+', MINUS='-', MUL='*', DIV='/',
    PRINT=';', ASSIGN='=', LP='(', RP=')'
};
 extern token_value curr_tok ;//= PRINT;
extern   double number_value;//为什么这里用了extern，parser那些名字空间的声明就不用呢
 extern   std::string string_value;
 //char ch;
token_value get_token();
}

namespace parser{         
double prim(bool get);
double term(bool get);
double expr(bool get);

using lexer::get_token;
using lexer::curr_tok;
//using error::error;
}

#include <map>

extern std::map<std::string,double>table;

namespace driver{
extern int no_of_errors;
extern std::istream* input;
void skip();
}
