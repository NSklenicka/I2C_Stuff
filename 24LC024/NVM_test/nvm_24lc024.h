#ifndef NVM_24LC024_H
#define NVM_24LC024_H

//std
#include <string>


class NVM_24LC024
{
public:
    NVM_24LC024();
    void writeByte(char address, char data);
    std::string getErrorFromCode(int code);
    uint8_t readByte(char address);

private:

    uint8_t m_deviceAddress = 0x51;
};

#endif // NVM_24LC024_H
