#include <QCoreApplication>
#include <bcm2835.h>
#include <qdebug.h>
#include <iostream>

#define REGISTER 0x20
#define DATA 0xAB
#define PRINT_CHAR(ch) std::cout << std::hex << (0xFF & ch) << std::endl


//this code works!

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (!bcm2835_init())
    {
        qDebug() << "bcm2835_init() failed";
    }
    else qDebug() << "bcm2835_init() success";

    if (!bcm2835_i2c_begin())
    {
        qDebug() << "bcm2835_i2c_begin() failed";
    }
    else qDebug() << "bcm2835_i2c_begin() success";

    bcm2835_i2c_setSlaveAddress(0X51);

    char buf[] = {REGISTER}; //0X20

    //send the data address to be rad

    if(0 == bcm2835_i2c_write (buf,1))
    {
        //success
        qDebug() << "write success";
    }
    else
    {
        //failed
        qDebug() << "write failed";
    }

    //read the data at the address

    if(0 == bcm2835_i2c_read (buf,1))
    {
        //success
        qDebug() << "read success";
        printf("User Register = %X \r\n",buf[0]);
    }
    else
    {
        //failed
        qDebug() << "read failed";
    }

    //read the data at the next address

    if(0 == bcm2835_i2c_read (buf,1))
    {
        //success
        qDebug() << "read success";
        printf("User Register = %X \r\n",buf[0]);
    }
    else
    {
        //failed
        qDebug() << "read failed";
    }


    bcm2835_i2c_end();
    bcm2835_close();

    return a.exec();
}
