#include <iostream>
#include <cstring>  // 需要包含此头文件，提供 strlen 和 strcpy 的声明

using namespace std;

class Mystr {

private:
    char* str;


// 表达定义类，其中包含构造函数和析构函数，这个是基础内容
public:
    Mystr(const char* s) {
        str = new char[strlen(s)+1];
        strcpy(str, s);

        std::cout << "Mystr::Mystr()" << std::endl;

    }

    ~Mystr() {
        std::cout << "Mystr::~Mystr()" << std::endl;
        delete[] str;
    }

    void print() {
        std::cout << str << std::endl;
    }
};

int main(){
{
    Mystr s("Hello World");
    s.print();
    Mystr s2("Hello World22");
    s2.print();
    sleep(3);
}
return 0;
}