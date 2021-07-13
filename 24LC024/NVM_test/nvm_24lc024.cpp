#include "nvm_24lc024.h"

// LIBS += -l bcm2835
#include <bcm2835.h>

//std
#include <iostream>
#include <thread>

/******************** Constructor ************************/

NVM_24LC024::NVM_24LC024()
{
    if (!bcm2835_init())
    {
        throw std::runtime_error("bcm2835_init() failed");
    }

    if (!bcm2835_i2c_begin())
    {
        throw std::runtime_error("bcm2835_i2c_begin() failed");
    }

    bcm2835_i2c_set_baudrate(100000);

    bcm2835_i2c_setSlaveAddress(m_deviceAddress); //0x51
}

/********************** Write Byte ******************************/

void NVM_24LC024::writeByte(char address, char data)
{
    char buf[] = {address, data, 0}; //I dont remember why I am sending an extra byte.

    int result = bcm2835_i2c_write(buf, 3);

    if(BCM2835_I2C_REASON_OK == result)
    {
        //success
        std::cout << "NVM_24LC024::writeByte() success" << std::endl;
    }
    else
    {
        //failed
        std::string error = "NVM_24LC024::writeByte() failed. Error code ";
        error += result;
        error += getErrorFromCode(result);
        throw std::runtime_error(error);
    }

    //delay between I2C commands
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

/********************** Read Byte ******************************/

char NVM_24LC024::readByte(char address)
{
    char buf[] = {address};
    int result;

    //send the data address to be read
    result = bcm2835_i2c_write (buf,1);

    if(BCM2835_I2C_REASON_OK != result)
    {
        //failed
        std::string error = "NVM_24LC024::readByte() failed to send register byte. Error code ";
        error += result;
        error += getErrorFromCode(result);
        throw std::runtime_error(error);
    }

    //read the data at the address
    result = bcm2835_i2c_read (buf,1);

    if(BCM2835_I2C_REASON_OK == result)
    {
        //success
        std::cout << "NVM_24LC024::readByte() success" << std::endl;
    }
    else
    {
        //failed
        std::string error = "NVM_24LC024::readByte() failed. Error code ";
        error += result;
        error += getErrorFromCode(result);
        throw std::runtime_error(error);
    }

    //delay between I2C commands
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    return buf[0];
}

/********************** Get Error ******************************/

std::string NVM_24LC024::getErrorFromCode(int code)
{

    switch(code)
    {
        case BCM2835_I2C_REASON_OK          : return " OK";
        case BCM2835_I2C_REASON_ERROR_NACK  : return " Received a NACK";
        case BCM2835_I2C_REASON_ERROR_CLKT  : return " Received Clock Streth Timeout";
        case BCM2835_I2C_REASON_ERROR_DATA  : return " Not all data is sent / received";
        default: return "Unknown error";
    }
}


