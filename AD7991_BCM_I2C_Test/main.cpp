#include <QCoreApplication>
#include <bcm2835.h>
#include <qdebug.h>
#include <iostream>

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

    char slave = 0x29;

    bcm2835_i2c_setSlaveAddress(slave);
    bcm2835_i2c_set_baudrate(100000);
    char buf[2] = {0};

    ////////////////////////////////////////////////////////////////////////////////////////////////

    bcm2835_delay(20);

    int result = 99;

    //write to configuration register


    buf[0] = {0x20};

    result = bcm2835_i2c_write(buf, 1);
    if(0 == result)
    {
        //success
        qDebug() << "write to configuration register success";
    }
    else
    {
        //failed
        qDebug() << "write to configuration register failed";
        qDebug() << "result: " << result;
        //return false;
    }

    bcm2835_delay(20);


    //read 2 bytes from A/D

    char data[2] = {0, 0};
    result = bcm2835_i2c_read(data, 2);
    if(0 == result)
    {
        //success
        qDebug() << "i2c_read success";
        printf("data[0] : 0x%02X \r\n", data[0]);
        printf("data[1] : 0x%02X \r\n", data[1]);
    }
    else
    {
        //failed
        qDebug() << "i2c_read failed";
        qDebug() << "result: " << result;
        //return false;
    }

//    bcm2835_delay(20);


//    //read 2 bytes from A/D

//    data[0] = 0;
//    data[0] = 1;
//    result = bcm2835_i2c_read(data, 2);
//    if(0 == result)
//    {
//        //success
//        qDebug() << "i2c_read success";
//        printf("data[0] : 0x%02X \r\n", data[0]);
//        printf("data[1] : 0x%02X \r\n", data[1]);
//    }
//    else
//    {
//        //failed
//        qDebug() << "i2c_read failed";
//        qDebug() << "result: " << result;
//        //return false;
//    }



//    bcm2835_delay(20);

    ////////////////////////////////////////////////////////////////////////////////////////////


//    bcm2835_i2c_end();
//    bcm2835_close();
    qDebug() << "done";

    return a.exec();
}
