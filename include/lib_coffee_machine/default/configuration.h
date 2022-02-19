#pragma once

struct DefaultConfiguration
{
    /************************************************************************************
     * WATER TEMPERATURE SENSOR
     ************************************************************************************/
    inline static constexpr double TARGET_WATER_TEMP = 95.0;
    inline static constexpr float WATER_TEMP_OFFSET = -12.0f; // degree celsius
    inline static constexpr unsigned long WATER_TEMP_REFRESH_PERIOD = 300; // milliseconds
    /************************************************************************************
     * STEAM TEMPERATURE SENSOR
     ************************************************************************************/
    inline static constexpr double TARGET_STEAM_TEMP = 145.0;
    inline static constexpr float STEAM_TEMP_OFFSET = -12.0f; // degree celsius
    inline static constexpr unsigned long STEAM_TEMP_REFRESH_PERIOD = 300; // milliseconds

    /************************************************************************************
     * TEMPERATURE CONTROLLER
     ************************************************************************************/
    inline static constexpr unsigned long CONTROLLER_SAMPLE_PERIOD = 100; // milliseconds

    /************************************************************************************
     * DEFAULT PID CONTROLLER
     ************************************************************************************/
    inline static constexpr double P_GAIN = 125;
    inline static constexpr double I_GAIN = 0.8;
    inline static constexpr double D_GAIN = 0.75;

    /************************************************************************************
     * SERIAL INTERFACE
     ************************************************************************************/
    inline static constexpr unsigned long SERIAL_BAUDRATE = 9600;
    inline static constexpr bool ENABLE_OUTPUT = false;

    /************************************************************************************
     * SAFETY SETTINGS
     ************************************************************************************/
    // Safety timeouts in milliseconds to turn off the heater. (disabled if < 1)
    inline static constexpr long SAFETY_TIMEOUT = 2400000; // 40 minutes
    inline static constexpr long STEAM_TIMEOUT = 300000;   // 5 minutes
    // Maximum temperature where the heater is simply cut off
    inline static constexpr int SAFETY_MAX_TEMP = 160; // degree celsius
};
