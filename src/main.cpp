#include <iostream>
#include <termio.h>
#include "port.h"


using namespace TTY_USB;
char buffer[512];
ssize_t nread = 0;


int main() {

    ttyUSB0 port;
    port.openPort();
    printf("fd is %d\n", port.t_fdValue);
    port.configPort();

    while(1){
        nread = port.readData(buffer, 512);

        if(nread > 0){
//            printf("lenth is %d\n", nread);
            buffer[nread+1] = '\0';
            printf("%s", buffer);
        }
    }


    return 0;
}

