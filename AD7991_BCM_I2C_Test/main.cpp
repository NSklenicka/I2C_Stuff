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

    return a.exec();
}
