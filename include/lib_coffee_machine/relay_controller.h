#pragma once

#include "interfaces.h"

template <class Adapter> class RelayController
{
  public:
    RelayController(Controller *ctrl, const unsigned long &period)
        : controller(ctrl), sample_period(period)
    {
        // the output signal is expressed as a time in ms, capped at WINDOW_SIZE
        controller->set_output_limits(0, WINDOW_SIZE);
    }

    bool compute(const double &input, const double &setpoint, bool *relay_on)
    {
        double output(0.0);

        // Limit the computation at the sample rate
        auto now = Adapter::millis();
        if (now - last_update_ts < sample_period)
        {
            // Use the previous output
            *relay_on = previous_output;
            return true;
        }

        last_update_ts = now;

        // How much time it has passed in the current window frame
        unsigned short window_progress = now % WINDOW_SIZE;

        // Process the pid output
        if (controller->compute(input, setpoint, output))
        {
            // Set the relay status based on the pid output
            *relay_on = (output >= window_progress);
            previous_output = *relay_on;
            return true;
        }
        return false;
    }

    // void set_kp(const double &kp)
    // {
    //     p_gain = kp;
    //     pid.SetTunings(p_gain, i_gain, d_gain);
    // }

    // void set_ki(const double &ki)
    // {
    //     i_gain = ki;
    //     pid.SetTunings(p_gain, i_gain, d_gain);
    // }

    // void set_kd(const double &kd)
    // {
    //     d_gain = kd;
    //     pid.SetTunings(p_gain, i_gain, d_gain);
    // }

  private:
    static constexpr unsigned short WINDOW_SIZE = 5000;

    unsigned long sample_period = 100;
    unsigned long last_update_ts = 0;

    Controller *controller = nullptr;

    bool previous_output = false;
};
