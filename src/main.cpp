#include <iostream>
#include "port.h"

using namespace TTY_USB;

int main() {

    ttyUSB0 port;
    port.openPort();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

