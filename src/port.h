#ifndef __PORT_H
#define __PORT_H

#include <cstdint>
#define FALSE  -1
#define TRUE   0


namespace TTY_USB{

    class ttyUSB0{



public:
    int32_t t_fdValue = -1;
    uint16_t t_speed = 9600;
    uint8_t  t_dataBits = 8;
    uint8_t  t_stopBits = 1;
    uint8_t t_party = 'N';

    ttyUSB0(uint16_t speed, uint8_t data_bits, uint8_t stop_bits, uint8_t parity);
    ttyUSB0();
    ~ttyUSB0();
    int16_t openPort(void);
    void closePort(void);
    ssize_t readData(char* buffer, uint16_t buffer_size);
    uint16_t configPort(int16_t fd, uint16_t speed, uint8_t data_bits, uint8_t stop_bits, uint8_t parity);
    uint16_t configPort(void);

private:
    void setSpeed(int16_t fd, uint16_t speed);
    uint8_t setParty(int16_t fd, uint16_t data_bits, uint16_t stop_bits, uint16_t parity);

};
}

#endif




