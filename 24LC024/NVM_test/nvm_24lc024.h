#ifndef NVM_24LC024_H
#define NVM_24LC024_H


class NVM_24LC024
{
public:
    NVM_24LC024();
    void writeByte(char address, char data);
    std::string getErrorFromCode(int code);
    char readByte(char address);

private:

    short m_deviceAddress = 0x51;
};

#endif // NVM_24LC024_H
