
#include <iostream>
#include <ad7991.h>



int main()
{

    try
    {
        AD7991 adc;
        adc.setActiveChannels(1,1,1,1);
        adc.setVref(3.3);

        std::vector <float> vals;
        adc.readADC(vals);

        for(int i = 0; i < vals.size(); i++)
        {
            std::cout << "channel " << i << " : " << vals[i] << std::endl;
        }
    }
    catch (std::runtime_error &error)
    {
        std::cout << error.what();
    }
    catch (...)
    {
        std::cout << "unkown error" << std::endl;
    }
    std::cin.get();
}








/*


int main_Old(int argc, char *argv[])
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

    //select channels
    std::bitset<8> channels = {0};

    bool ch0 = 1;
    bool ch1 = 0;
    bool ch2 = 0;
    bool ch3 = 0;

    if(ch0) channels[4] = 1;
    if(ch1) channels[5] = 1;
    if(ch2) channels[6] = 1;
    if(ch3) channels[7] = 1;

    char config = channels.to_ulong();

    qDebug() << "channels: " << QString::number(config, 2);

    //write to configuration register
    buf[0] = {config};

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

////////////////    parse out the data response   ///////////////////////////////

    char channel;

    //get channel
    channel = ((data[0] & 0b00110000)>>4); //mask the 2 channel bits, shift them to the right
    qDebug() << "channel: " << static_cast<int>(channel);

    //do I need static cast??
//    int ch = ((buf[0] & 0b00110000)>>4);
//    qDebug() << "channel not static cast: " << ch;

    //get value
    int data0, data1;
    float datan;
    data0 = static_cast<int>(data[0] & 0b00001111); //mask out the channel bits on buf[0]
    //qDebug() << "data0 after mask: " << QString::number(data0, 2);

    data0 = (data0 << 8); // bit shift 8 bits to the left
    //qDebug() << "data0 after << 8 : " << QString::number(data0, 2);

    data1 = data[1] & 0xFF;//0xFF will over flow ??
    //qDebug() << "data1: "  << QString::number(data1, 2);

    datan = data0 + data1;

    qDebug() << "data0 + data1: " << QString::number(datan);

    float Vref = 3.294;
    float value = datan/4095;
    qDebug() << "data/4095: " << value;

    value = value * Vref;

    qDebug() << "value: " << value;




//    bcm2835_i2c_end();
//    bcm2835_close();
    qDebug() << "done";

    return a.exec();
}

*/
