#ifndef AD7991_H
#define AD7991_H

#include<string>
#include<vector>

#define DELAY_MS_BETWEEN_COMMANDS 10
#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))


class AD7991
{
public:

    AD7991();

    //set which a/d channels to use. send configuration byte to a/d
    void setActiveChannels(bool chan_0_Active, bool chan_1_Active, bool chan_2_Active, bool chan_3_Active);


    //get conversions from from adc for all active channels. enumerate the adc values into a vector.
    void readADC(std::vector <float> & values);

    std::vector <float> getValuesFromBuffer(const char buffer[], const int numChannels);

    void setVref(float Vref);

private:

    std::string getErrorFromCode(int result);

    float m_Vref = -1;
    bool isValidVref(float Vref);

    //active A/D channels
    bool m_chan_0_Active = false;
    bool m_chan_1_Active = false;
    bool m_chan_2_Active = false;
    bool m_chan_3_Active = false;


};

#endif // AD7991_H
