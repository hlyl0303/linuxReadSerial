#include <cstdio>
#include <unistd.h>
#include "port.h"
#include "fcntl.h"
#include "termios.h"

using namespace TTY_USB;

int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
                    B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300, 38400,
                  19200,  9600, 4800, 2400, 1200,  300, };


ttyUSB0::ttyUSB0(uint16_t speed, uint8_t data_bits, uint8_t stop_bits, uint8_t parity) {
    t_speed = speed;
    t_dataBits = data_bits;
    t_stopBits = stop_bits;
    t_party = parity;

}

ttyUSB0::ttyUSB0(){

}

ttyUSB0::~ttyUSB0(){

}

int16_t ttyUSB0::openPort() {
    int fd;
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);

    if(-1 == fd){
        printf("can't open serial port\n");
    }
    this->t_fdValue = fd;
}

void ttyUSB0::closePort() {
    if(-1 != t_fdValue)
        close(t_fdValue);
}

ssize_t ttyUSB0::readData(char *buffer, uint16_t buffer_size) {
    return read(t_fdValue, buffer, buffer_size);
}
uint16_t ttyUSB0::configPort(int16_t fd, uint16_t speed, uint8_t data_bits, uint8_t stop_bits, uint8_t parity){
    setSpeed(fd, speed);
    setParty(fd, data_bits, stop_bits, parity);
}

uint16_t ttyUSB0::configPort(void){
    setSpeed(t_fdValue, t_speed);
    setParty(t_fdValue, t_dataBits, t_stopBits, t_party);
}

void ttyUSB0::setSpeed(int16_t fd, uint16_t speed) {
    int   i;
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) {
        if  (speed == name_arr[i]) {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if  (status != 0) {
                perror("tcsetattr fd1");
                return;
            }
            tcflush(fd,TCIOFLUSH);
        }
    }
}

uint8_t ttyUSB0::setParty(int16_t fd, uint16_t data_bits, uint16_t stop_bits, uint16_t parity) {
    struct termios options;
    if  ( tcgetattr( fd,&options)  !=  0) {
        perror("SetupSerial 1");
        return(FALSE);
    }
    options.c_cflag &= ~CSIZE;
    switch (data_bits) /*设置数据位数*/
    {
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
            fprintf(stderr,"Unsupported data size\n"); return (FALSE);
    }
    switch (parity)
    {
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;   /* Clear parity enable */
            options.c_iflag &= ~INPCK;     /* Enable parity checking */
            break;
        case 'o':
        case 'O':
            options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
            options.c_iflag |= INPCK;             /* Disnable parity checking */
            break;
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;     /* Enable parity */
            options.c_cflag &= ~PARODD;   /* 转换为偶效验*/
            options.c_iflag |= INPCK;       /* Disnable parity checking */
            break;
        case 'S':
        case 's':  /*as no parity*/
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;break;
        default:
            fprintf(stderr,"Unsupported parity\n");
            return (FALSE);
    }
/* 设置停止位*/
    switch (stop_bits)
    {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            options.c_cflag |= CSTOPB;
            break;
        default:
            fprintf(stderr,"Unsupported stop bits\n");
            return (FALSE);
    }
/* Set input parity option */
    if (parity != 'n')
        options.c_iflag |= INPCK;
    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("SetupSerial 3");
        return (FALSE);
    }
    return (TRUE);
}
