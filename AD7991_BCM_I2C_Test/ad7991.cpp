#include "ad7991.h"

// for qt
// LIBS += -l bcm2835
#include <bcm2835.h>//raspberry pi specific

//std
#include <bitset>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>


AD7991::AD7991()
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
     if(BCM2835_I2C_REASON_OK == result)
     {
         //success
         std::cout << "setActiveChannels(): write to configuration register success" << std::endl;
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

/************************* Read A/D *************************/

void AD7991::readADC(std::vector<float> &values)
{

    int numChannelsToRead = 0;
    if(m_chan_1_Active) ++numChannelsToRead;
    if(m_chan_2_Active) ++numChannelsToRead;
    if(m_chan_3_Active) ++numChannelsToRead;
    if(m_chan_4_Active) ++numChannelsToRead;

    std::cout << "num channels: " << numChannelsToRead << std::endl;

    if(0 == numChannelsToRead)
    {
        throw std::runtime_error("readADC() no channels are active!");
    }

    if(!isValidVref(m_Vref))
    {
        throw std::runtime_error("AD7991::readADC() voltage reference is not set, or is invalid");
    }

    //allow 2 bytes per channel
    uint32_t numBytesToRead = numChannelsToRead * 2;
    char buf[8] = {0};

    //read bytes from I2C device
    short result = bcm2835_i2c_read(buf, numBytesToRead);
    if(BCM2835_I2C_REASON_OK == result)
    {
        //success
        std::cout << "i2c_read success" << std::endl;
    }
    else
    {
        //failed
        std::string error = "readADC(): bcm2835_i2c_read() failed. error ";
        error += std::to_string(result);
        error += getErrorFromCode(result);
        throw std::runtime_error(error);
    }

    values = getValuesFromBuffer(buf, numChannelsToRead);
}

/************************* Convert raw binary to analog values *************************/

std::vector<float> AD7991::getValuesFromBuffer(const char buffer[], const int numChannels)
{
    std::vector<float> vals;
    vals.resize(numChannels);

    for(int i = 0; i < numChannels; i++) //for each active channel
    {
        //get the 2 relevant bytes of the buffer

    }




    return vals;
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

/************************* Vref Validation *************************/

bool AD7991::isValidVref(float Vref)
{
    if(Vref > 1.2 && 5.5 > Vref) //Vref must be between 1.2 and 5.5
        return true;
    else return false;
}

/************************* Setters *************************/

void AD7991::setVref(float Vref)
{
    if(isValidVref(Vref))
    {
        m_Vref = Vref;
    }
    else
    {
        std::string error = "AD7991::setVref() Reference voltage must be between 1.2 and 5.5. V= ";
        error += std::to_string(Vref);
        throw std::runtime_error(error);
    }
}
