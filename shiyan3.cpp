#include <iostream>
using namespace std;
class student
{
public:
    void cala()
        {
            cout<<"call student::cala()\n";
        }
};

class gstudent:public student
{
public:
    void cala()
        {
            cout<<"call gstudent::cala()"<<endl;
        }
    void cala(int i)
        {
            cout<<"call gstudent::cala(int)"<<endl;
        }
};
    
int main()
{
    student s;
    gstudent gs;

    gs.cala();
    gs.cala(5);
    gs.student::cala();
    return 0
}

    
