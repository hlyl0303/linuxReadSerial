#include "port.h"
#include "fcntl.h"

using namespace TTY_USB;

ttyUSB0::ttyUSB0() {

}

ttyUSB0::~ttyUSB0() {

}

int ttyUSB0::openPort() {
    int fd;
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);

    if(-1 == fd){
        perror("can't open serial port");
    }
    this->fd_ = fd;
    return fd;
}