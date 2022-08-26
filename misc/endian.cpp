#include <iostream>

using namespace std;

void checkEnd()
{
    union 
    {
        long a;
        char b;
    } u;

    u.a = 1;
    if (u.b == 1)
    //低地址放低字节，小端模式
        cout<<"Little-Endian";
    else
    //低地址放高字节，大端模式
        cout<<"Big-Endian";
}

int main()
{
    checkEnd();
    cin.get();
    return 0;
}