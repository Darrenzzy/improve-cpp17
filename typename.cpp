#include<iostream>
#include<typeinfo>
#include <iostream>
#include <string>
#include <map>

template<typename T>
struct A {
    int num;

    A() {
        std::cout << "A Construct" << std::endl;
        std::cout << "template typename is: " << typeid(T).name() << std::endl;
//        std::cout << "template typename is: " << typeid (T).hash_code() << std::endl;
    }
};

//此处的T可省略，X代表模板类型，T和X前的typename可替换成class
template<template<typename T> typename X>
struct B {
    X<double> e;

    B() { std::cout << "B Construct" << std::endl; }
};

void templateDes() {
//    初始化一个 变量a 是A结构 其中参数是B模版，B模版夹带A模版作为参数
    A<B<A>> a;
    std::cout << "***************************" << std::endl;
//    初始化一个变量b 是B结构，其中参数是A模版
    B<A> b;
}


// 关键字表达在程序中可以被重复定义，而不被告警已定义
inline int num = 0;

inline void print() {
    std::cout << "hello world  " << num << std::endl;
}

inline void add(int arg) {
    num += arg;
    print();
}

int inlines() {
    num = 2;
    print();
    add(10);
    return 0;
}

// auto关键字能够通过初始化器推导出变量的类型
#include <vector>

void autoMain() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = v.begin(); // it 被推导为 std::vector<int>::iterator
    std::map<int, std::string> m = {{1, "one"},
                                    {2, "two"}};
    auto mit = m.begin(); // mit 被推导为 std::map<int, std::string>::iterator

    for (auto n: v) { // n 被推导为 int
        std::cout << n << " ";
    }
    std::cout << std::endl;

    for (auto &kv: m) { // kv 被推导为 std::pair<const int, std::string>&
        std::cout << kv.first << ": " << kv.second << " ";
    }
    std::cout << std::endl;

}

void addMap() {
    std::map<int, std::string> c = {{1, "a"}};
    // 使用 C++17 中的 if 语句带初始化器的语法
    if (auto res = c.insert(std::make_pair(2, "b")); !res.second) {
        std::cout << "key 2 exist" << std::endl;
    } else {
        std::cout << "insert success, value: " << res.first->second << std::endl;
    }
}

// 折叠表达式
template<typename ... T>
auto sum(T ... arg) {
    return (arg + ...);//右折叠
}

template<typename ... T>
double sum_strong(T ... arg) {
    return (arg + ... + 0);//右折叠
}

template<typename ... T>
double sub1(T ... arg) {
    return (arg - ...);//右折叠 从左边开始算
}

template<typename ... T>
double sub2(T ... arg) {
    return (... - arg);//左折叠  从右边开始算
}

void expressSum() {
    int s1 = sum(1, 2, 2, 4, 5);//解包：((((1+)2+)3+)4+)5 = 15
    double s2 = sum(1.1, 2.2, 3.3, 4.4, 5.5, 6.6);
    double s3 = sum(1, 2.2, 3, 4.4, 5);
    double s4 = sub1(5, 2, 1, 1);//解包：((((5-)2-)1-)1) = 1
    double s5 = sub2(5, 2, 1, 1);//解包：(5-(2-(1-(1)))) = 3
    double s6 = sum_strong();//s6 = 0

    std::string str1("he");
    std::string str2("ll");
    std::string str3("o ");
    std::string str4("world");
    std::string str5 = sum(str1, str2, str3, str4);//str5 = "hello world"
}

struct S {
    double nums;
    long num;
};

S foo(int arg1, double arg2) {
    double result1 = arg2 * arg1;
    long result22 = arg2 / arg1;
    return {result1, result22};
}

// 结构化绑定
void structs() {
    auto [n1, n2] = foo(10, 33);
    std::cout << n1 << n2 << std::endl;
}
// 嵌套使用命名空间
namespace Outer::Inner {
    inline namespace v1 { // 可选的命名空间版本
        void foo() {
            std::cout << "Outer::Inner::foo()" << std::endl;
        }
    }
}

// lambda 表达式 获取this 的结构值，注意要传递this
struct MyStruct {
    double ohseven = 100.7;
    auto f() {
        return [this] {
            return [*this] {
//                this->ohseven = 200.2;//错误，只读变量不可赋值
                return ohseven;//正确
            };
        }();
    }
};

void printMy() {
    MyStruct a;
    std::cout << a.f().operator()() << std::endl;
}
// 枚举初始化
void enmus(){
    enum MyEnum { value };
    enum byte : unsigned char { };
    byte b { 42 }; //正确
    byte d = byte{ 42 }; //正确，其值与b相等
    struct A { byte b; };
    A a2 = { byte{ 42 } }; //正确
    enum class Handle : unsigned int { value = 0 };
    Handle h { 42 }; //正确
}

int main() {
    enmus();
    printMy();
    Outer::Inner::foo(); // 无需重复 namespace
    structs();
    expressSum();
    addMap();
    autoMain();
    inlines();
    templateDes();
    return 0;
}
