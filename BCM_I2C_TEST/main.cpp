#include <QCoreApplication>
#include <bcm2835.h>
#include <qdebug.h>
#include <iostream>


void printByte(char address)//reads a byte at an address and print to console
{
    char buf[] = {address}; //0x20 0xAB
    int result;

    //send the data address to be read
    result = bcm2835_i2c_write (buf,1);

    if(0 == result)
    {
        //success
        qDebug() << "printByte : write success";
    }
    else
    {
        //failed
        qDebug() << "printByte : write failed"; //always NACKS but actually worked??
        qDebug() << "result: " << result;
    }

    //read the data at the address
    result = bcm2835_i2c_read (buf,1);
    if(0 == result)
    {
        //success
        qDebug() << "printByte : read success";
        printf("address:    0x%02X \r\n", address);
        printf("data:       0x%02X \r\n", buf[0]); //big X means print the value in capital HEX notation
    }                                               //02 means print 2 digits left padded by 0's
    else
    {
        //failed
        qDebug() << "printByte : read failed";
        qDebug() << "result: " << result;
    }
}

void writeByte(char address, char data)
{
    char buf[] = {address, data, 0};

    int result = bcm2835_i2c_write (buf, 3);

    if(0 == result)
    {
        //success
        qDebug() << "writeByte : write success";
    }
    else
    {
        //failed
        qDebug() << "writeByte : write failed"; //always NACKS but actually worked??
        qDebug() << "result: " << result;
    }
}


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
    char data2 = 0x63;


    //write data1 to address
    //qDebug() << "writing " << data1 << " to address " << address;
    writeByte(address, data1);

    bcm2835_delay(500);

    //read data 1 from address
    printByte(address);

    bcm2835_delay(500);

    //write data2 to address
    //qDebug() << "writing " << data2 << " to address " << address;
    writeByte(address, data2);

    bcm2835_delay(500);

    //read data2 from address
    printByte(address);

    bcm2835_delay(500);


    bcm2835_i2c_end();
    bcm2835_close();

    qDebug() << "done";

    return a.exec();
}
