#include "ad7991.h"

//raspberry pi specific
#include <bcm2835.h>

//Qt
#include <QDebug>

//STL
#include <bitset>
#include <string>
#include <thread>
#include <chrono>


AD7991::AD7991(QObject *parent) : QObject(parent)
{

}

/************************* Initialize *************************/

void AD7991::initialize()
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

    bcm2835_i2c_setSlaveAddress(0x29);
}

/************************* Set Active Channel *************************/

void AD7991::setActiveChannels(bool chan_1_Active, bool chan_2_Active, bool chan_3_Active, bool chan_4_Active)
{
    m_chan_1_Active = chan_1_Active;
    m_chan_2_Active = chan_2_Active;
    m_chan_3_Active = chan_3_Active;
    m_chan_4_Active = chan_4_Active;

    //create the configuration byte

    std::bitset<8> channels = {0};

    if(chan_1_Active) channels[4] = 1;
    if(chan_2_Active) channels[5] = 1;
    if(chan_3_Active) channels[6] = 1;
    if(chan_4_Active) channels[7] = 1;

    char configByte = channels.to_ulong();

    //write to configuration register

     char buf[1] = {configByte};

     int result = -1;

     result = bcm2835_i2c_write(buf, 1); //write 1 byte
     if(0 == result)
     {
         //success
         qDebug() << "setActiveChannels(): write to configuration register success";
     }
     else
     {
         //failed
         std::string error;
         error += "setActiveChannels(): write to configuration register failed. ";
         error +=  "error code: ";
         error += std::to_string(result);
         error += getErrorFromCode(result);
         throw std::runtime_error(error);
     }

     SLEEP(DELAY_MS_BETWEEN_COMMANDS); //allow time between I2C read/writes
}

/************************* Get Error Code *************************/

std::string AD7991::getErrorFromCode(int code)
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
