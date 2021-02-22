#pragma once

#include <string>
#include <unistd.h>

class TestAdapter
{
  public:
    inline static void delay(unsigned long ms)
    {
        sleep(ms / 1000);
    }

    inline static unsigned long millis()
    {
        // using namespace std::chrono;
        // return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        //     .count();
        return millis_ret;
    }

    inline static char *dtostrf(double val, signed char width, unsigned char prec,
                                char *sout)
    {
        char fmt[20];
        sprintf(fmt, "%%%d.%df", width, prec);
        sprintf(sout, fmt, val);
        return sout;
    }

    inline static unsigned long millis_ret = 0;
    inline static char message_sent[100];
};
