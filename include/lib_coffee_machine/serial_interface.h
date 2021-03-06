#pragma once

#include "common.h"
#include "interfaces.h"

template <class Adapter> class SerialInterface
{
  public:
    SerialInterface(BaseSerialInterface *serial) : serial(serial)
    {
    }

    void read_input()
    {
        // Read input data and enable or disable the debug mode
        // If debug mode is enabled, accept temperature input
        // to overwrite sensor readings
        if (serial->available())
        {
            char data[25];
            serial->read_string_until('\n', data);
            if (string_utils::start_with(data, "help"))
            {
                print_help();
            }
            else if (string_utils::start_with(data, "debug on"))
            {
                debug_mode = true;
                serial->println("Setting debug mode ON");
            }
            else if (string_utils::start_with(data, "debug off"))
            {
                debug_mode = false;
                serial->println("Setting debug mode OFF");
            }
            else if (string_utils::start_with(data, "output on"))
            {
                enable_output(true);
                serial->println("Setting output ON");
            }
            else if (string_utils::start_with(data, "output off"))
            {
                enable_output(false);
                serial->println("Setting output OFF");
            }
            else if (string_utils::start_with(data, "temp ") && is_debug_active())
            {
                mock_temperature = string_utils::to_number<double>(data, 5);
                // serial->println("Setting mock temperature to; " + data);
                serial->println("Setting mock temperature");
            }
        }
    }

    void print_status(const Machine::Status &status)
    {
        auto now = Adapter::millis();
        if (is_output_enabled() && now - time_last_print > PRINT_TIMEOUT)
        {
            unsigned limit(100);
            char output[limit];
            char curr_temp_buffer[6];
            char target_temp_buffer[6];

            time_last_print = now;

            Adapter::dtostrf(status.current_temperature, 4, 1, curr_temp_buffer);
            Adapter::dtostrf(status.target_temperature, 4, 1, target_temp_buffer);

            snprintf(output, limit - 1, "%d,%s,%s,%d,%s",
                     static_cast<int>(status.machine_mode), curr_temp_buffer,
                     target_temp_buffer, status.water_heater_on, status.status_message);
            serial->println(output);
        }
    }

    bool is_debug_active()
    {
        return debug_mode;
    }

    double get_mock_temperature()
    {
        return mock_temperature;
    }

    void enable_output(const bool &enable)
    {
        output_enabled = enable;
    }

  private:
    void print_help()
    {
        serial->println("**** Coffee Machine serial interface ****");
        serial->println("Commands:");
        serial->println("- help: show this message");
        serial->println("- debug [on/off]: enable/disable debug mode");
        serial->println("- output [on/off]: enable/disable serial output");
        serial->println(
            "- temp [value]: Set the mock temperature. Used only in debug mode");
        serial->println("**** END ****");
    }

    bool is_output_enabled()
    {
        return output_enabled;
    }

    static constexpr unsigned short PRINT_TIMEOUT = 200;
    unsigned long time_last_print;

    bool output_enabled = false;
    bool debug_mode = false;
    double mock_temperature = 0.0;

    BaseSerialInterface *serial;
};
