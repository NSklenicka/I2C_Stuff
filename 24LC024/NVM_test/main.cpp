#include <QCoreApplication>

#include <nvm_24lc024.h>

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try
    {
        NVM_24LC024 nvm;
        nvm.writeByte(0x22, 0xAA);

    }
    catch (std::runtime_error &error)
    {
        std::cout << error.what();
    }
    catch (...)
    {
        std::cout << "unkown error";
    }


    std::cin.get();

    return a.exec();
}
