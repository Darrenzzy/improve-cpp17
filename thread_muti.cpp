#include <iostream>
#include <any>
#include <condition_variable>
#include <thread>
#include <vector>
#include <tuple>
#include <string>
#include <shared_mutex>

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

void anyValue() {
    std::optional<int> maybeNumber;

    // 初始状态，没有值
    if (!maybeNumber) {
        std::cout << "maybeNumber is empty" << std::endl;
    }

    // 赋值
    maybeNumber = 42;

    // 检查并使用值
    if (maybeNumber) {
        std::cout << "maybeNumber contains: " << maybeNumber.value() << std::endl;
    }

    // 重置为无值状态
    maybeNumber.reset();

    if (!maybeNumber) {
        std::cout << "maybeNumber is now empty again" << std::endl;
    }


    std::variant<int, std::string> myVariant;

    myVariant = 10;
    std::cout << "Integer value: " << std::get<int>(myVariant) << std::endl;

    myVariant = "Hello, Variant!";
    std::cout << "String value: " << std::get<std::string>(myVariant) << std::endl;


    std::any anything;

    anything = 42;
    std::cout << "Integer value: " << std::any_cast<int>(anything) << std::endl;

    anything = std::string("Hello, Any!");
    std::cout << "String value: " << std::any_cast<std::string>(anything) << std::endl;

    // 尝试错误类型的转换将抛出异常
    try {
        std::cout << std::any_cast<float>(anything) << std::endl;
    } catch (const std::bad_any_cast &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

void mutex() {
    std::shared_mutex mtx;

    // 创建多个读线程
    for (int i = 0; i < 5; ++i) {
        std::thread t([&]() {
            // 获取读锁
            std::shared_lock<std::shared_mutex> lock(mtx);
            std::cout << "Reader thread " << i << " is reading." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
        t.detach();
    }

    // 创建一个写线程
    std::thread t_writer([&]() {
        // 获取写锁
        std::unique_lock<std::shared_mutex> lock(mtx);
        std::cout << "Writer thread is writing." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    });
    t_writer.join();

}

std::shared_mutex mtx;
int cnt = 0;

void Reader(int id) {
    for (int i = 0; i < 5; ++i) {
        std::shared_lock<std::shared_mutex> lock(mtx);
        std::cout << "Reader " << id << ": cnt = " << cnt << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Writer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        ++cnt;
        std::cout << "Writer " << id << ": cnt = " << cnt << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void threadMuti() {
    std::vector<std::thread> readers;
    for (int i = 0; i < 5; ++i) {
        readers.push_back(std::thread(Reader, i + 1));
    }

    std::vector<std::thread> writers;
    for (int i = 0; i < 2; ++i) {
        writers.push_back(std::thread(Writer, i + 1));
    }

    for (auto &t: readers) {
        t.join();
    }

    for (auto &t: writers) {
        t.join();
    }
}


int main() {
    threadMuti();
//    mutex();
    anyValue();
    MapObj();
    MapObj2();


    return 0;
}
