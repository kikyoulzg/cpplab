#include <iostream>
#include "signal.hpp"

class Button {
public:
    Signal<> on_click;
};

class Message {
public:
    void print() {
        std::cout << "Hello wolrd!" << std::endl;
    }
};

int main(void)
{
    Button btn;
    Message msg;

    btn.on_click.connect(&msg, &Message::print);
    btn.on_click.emit();

    return 0;
}
