#include <QCoreApplication>
#include <QTimer>
#include <iostream>
#include <mutex>
#include <ad7991.h>
#include <nvm_24lc024.h>

//cannot have two diferent objects that use BCM I2C. Apparently they act as one.



static QTimer adcTimer;
static QTimer nvmTimer;

static std::mutex busMutex;
static short i = 0;

inline void printValues(const std::vector <float> &values)
{
    for(int i = 0; i < values.size(); i++)
    {
        std::cout << "channel " << i << " : " << values[i] << std::endl;
    }
}

void readADC()
{
    try
    {
        busMutex.try_lock();
        AD7991 adc;
        adc.setVref(3.3);
        adc.setActiveChannels(1,1,1,1);
        std::vector <float> values;
        adc.readADC(values);
        printValues(values);
        i++;
        std::cout << "i: " << i << std::endl;
        busMutex.unlock();
    }
    catch (std::runtime_error &error)
    {
        std::cout << error.what() << std::endl;
        adcTimer.stop();
    }
}

void readNvm()
{
    std::cout << "readNvm()" << std::endl;
    try
    {
        busMutex.try_lock();
        NVM_24LC024 nvm;
        char byte = nvm.readByte(0x11);
        std::cout << "byte: " << std::to_string(static_cast<int>(byte)) << std::endl;
        i++;
        std::cout << "i: " << i << std::endl;
        busMutex.unlock();
    }
    catch (std::runtime_error &error)
    {
        std::cout << error.what() << std::endl;
        nvmTimer.stop();
    }

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    try
    {


        QObject::connect(&adcTimer, &QTimer::timeout, [=](){ readADC(); } ) ;
        QObject::connect(&nvmTimer, &QTimer::timeout, [=](){ readNvm(); } ) ;

//        readADC();
//        readNvm();

        nvmTimer.start(50);
        adcTimer.start(50);
    }


    catch(std::runtime_error &error)
    {
        std::cout << error.what() << std::endl;
    }


    return a.exec();
}
