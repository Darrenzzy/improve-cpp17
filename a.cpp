#include <iostream>
#include <charconv>

#include <condition_variable>
#include <thread>
#include <unistd.h>
#include <vector>
#include <tuple>
#include <string>


struct Person {
    std::string name;
    int age;
    bool ok;
    double height;
};


template<typename T>
class Pair {
public:
    T first;
    T second;

    // 构造函数模板，使用参数推导
    template<typename U, typename V>
    Pair(U &&f, V &&s) : first(std::forward<U>(f)), second(std::forward<V>(s)) {}
};

void MapObj() {
    // 创建一个 Person 对象
    Person person{"Alice", 30, true, 1.75};

    // 使用结构化绑定访问 Person 对象的成员
    auto [name, age, okkm, height] = person;

    // 打印成员值
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "ok: " << okkm << std::endl;
    std::cout << "Height: " << height << std::endl;

}

void MapObj2() {
    // 使用构造函数模板参数推导
    Pair<int> pair1(5, 10); // 推导出类型为 Pair<int>
    std::cout << "Pair 1: " << pair1.first << ", " << pair1.second << std::endl;

    Pair<double> pair2(3.14, 2.71); // 推导出类型为 Pair<double>

    std::cout << "Pair 2: " << pair2.first << ", " << pair2.second << std::endl;

}

void anyValue(){
//    optional<T>——持有 T 或什么都不持有
//    variant<T,U>——持有 T 或 U
//    any——持有任意类型

}

int main() {

    anyValue();
    MapObj();
    MapObj2();


    return 0;
}
