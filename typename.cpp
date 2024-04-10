#include<iostream>
#include<typeinfo>

template<typename T>
struct A
{
    int num;
    A()
    {
        std::cout << "A Construct" << std::endl;
        std::cout << "template typename is: " << typeid (T).name() << std::endl;
    }
};
//此处的T可省略，X代表模板类型，T和X前的typename可替换成class
template<template<typename T> typename X>
struct B
{
    X<double> e;
    B() { std::cout << "B Construct" << std::endl; }
};

int main()
{
    A<B<A>> a;
    std::cout << "***************************" << std::endl;
    B<A> b;
    return 0;
}