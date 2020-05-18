#include <iostream>
#include "meep.h"
int main()
{
    Meep<char,int> v(10);
    v.insert('a',3);
    v.insert('b',2);
    v.insert('c',10);
    v.display();
    v.change('c',0);
    v.display();
    
    return 0;
}