#include <QCoreApplication>
#include <bcm2835.h>
#include <qdebug.h>
#include <iostream>

//#define REGISTER 0x20
//#define DATA 0xAB
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

    char slave = 0x51;

    bcm2835_i2c_setSlaveAddress(slave);

    char address = 0x01;
    char data1 = 0x52;

    char buf[] = {address}; //0x20 0xAB

    int result;

    //write data
    //send the address followed by the data




    //read data
    //send the data address to be read

    //buf[0] = {REGISTER}; //0X20

    result = bcm2835_i2c_write (buf,1);

    if(0 == result)
    {
        //success
        qDebug() << "write success";
    }
    else
    {
        //failed
        qDebug() << "write failed"; //always NACKS but actually worked??
        qDebug() << "result: " << result;
    }

    //clear the buffer (for debugging)
    buf[0] = 0;
    //read the data at the address
    result = bcm2835_i2c_read (buf,1);

    if(0 == result)
    {
        //success
        qDebug() << "read success";
        printf("User Register = 0x%02X \r\n",buf[0]); //big X means print the value in capital HEX notation
    }                                               //02 means print 2 digits left padded by 0's
    else
    {
        //failed
        qDebug() << "read failed";
        qDebug() << "result: " << result;
    }

    //read the data at the next address

    if(0 == bcm2835_i2c_read (buf,1))
    {
        //success
        qDebug() << "read success";
        printf("User Register = 0x%02X \r\n",buf[0]);
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
