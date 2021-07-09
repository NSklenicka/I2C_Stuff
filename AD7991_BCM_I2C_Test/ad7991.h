#ifndef AD7991_H
#define AD7991_H

#include<string>

#define DELAY_MS_BETWEEN_COMMANDS 10
#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms));

//make this class without using qt !!!!

class AD7991
{
public:

    AD7991();

    //set which a/d channels to use. send configuration byte to a/d
    void setActiveChannels(bool chan_1_Active, bool chan_2_Active, bool chan_3_Active, bool chan_4_Active);

private:

    std::string getErrorFromCode(int code);

    //active A/D channels
    bool m_chan_1_Active = false;
    bool m_chan_2_Active = false;
    bool m_chan_3_Active = false;
    bool m_chan_4_Active = false;


};

#endif // AD7991_H
