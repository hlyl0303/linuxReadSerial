#ifndef __PORT_H
#define __PORT_H

namespace TTY_USB{

class ttyUSB0{

    int fd_;

public:
    ttyUSB0();
    ~ttyUSB0();
    int openPort(void);

};
}

#endif




