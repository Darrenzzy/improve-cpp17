

#include <iostream>
#include <cstdint>

int main() {
    int a = 300;
    uint8_t *p = reinterpret_cast<uint8_t *>(&a);
    *p = 1; // 修改a在内存中的第一个字节

    // 打印修改后的a的值
    std::cout << "Modified a = " << a << std::endl;

    // 为了更清楚地看到发生了什么，我们也可以以十六进制形式打印出来
    std::cout << "Modified a (hex) = 0x" << std::hex << a << std::endl;
//  std::cout << "Modified a = " << std:: << a << std::endl;

    return 0;
}
