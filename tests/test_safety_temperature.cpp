#include "common_test.h"

class TestSafetyTemperature : public CommonTest
{
};

TEST_F(TestSafetyTemperature, testWaterModeSafetyTemperatureCutOffTheHeater)
{
    auto status = machine->spin();

    ASSERT_EQ(status.machine_mode, Machine::Mode::WATER_MODE);
    ASSERT_EQ(status.current_temperature, 10.0);
    ASSERT_EQ(status.target_temperature, Configuration::TARGET_WATER_TEMP);
    ASSERT_TRUE(status.water_heater_on);
    ASSERT_EQ(strcmp(status.status_message, "Heating..."), 0);
    ASSERT_EQ(status.start_timestamp, 0.0);
    ASSERT_EQ(status.steam_mode_timestamp, Adapter::millis_ret);

    // Simulate the temperature over the safety limits
    water_sensor.temp_c = Configuration::SAFETY_MAX_TEMP + 20.0;
    while (status.current_temperature < Configuration::SAFETY_MAX_TEMP)
    {
        time_step();
        status = machine->spin();
    }

    ASSERT_EQ(status.machine_mode, Machine::Mode::WATER_MODE);
    ASSERT_GT(status.current_temperature, Configuration::SAFETY_MAX_TEMP);
    ASSERT_EQ(status.target_temperature, Configuration::TARGET_WATER_TEMP);
    ASSERT_FALSE(status.water_heater_on);
    ASSERT_EQ(strcmp(status.status_message, "Safey temperature exceeded"), 0);
    ASSERT_EQ(status.start_timestamp, 0.0);
    ASSERT_EQ(status.steam_mode_timestamp, Adapter::millis_ret);
}

TEST_F(TestSafetyTemperature, testSteamModeSafetyTemperatureCutOffTheHeater)
{
    // Mock the mode button as pressed
    mode_switch_pin.set_steam_mode();

    auto status = machine->spin();

    ASSERT_EQ(status.machine_mode, Machine::Mode::STEAM_MODE);
    ASSERT_EQ(status.current_temperature, 10.0);
    ASSERT_EQ(status.target_temperature, Configuration::TARGET_STEAM_TEMP);
    ASSERT_TRUE(status.water_heater_on);
    ASSERT_EQ(strcmp(status.status_message, "Heating..."), 0);
    ASSERT_EQ(status.start_timestamp, 0.0);
    ASSERT_EQ(status.steam_mode_timestamp, 0.0);

    // Mock a high steam temperature
    steam_sensor.temp_c = Configuration::SAFETY_MAX_TEMP + 20.0;
    while (status.current_temperature < Configuration::SAFETY_MAX_TEMP)
    {
        time_step();
        status = machine->spin();
    }

    ASSERT_EQ(status.machine_mode, Machine::Mode::STEAM_MODE);
    ASSERT_GT(status.current_temperature, Configuration::SAFETY_MAX_TEMP);
    ASSERT_EQ(status.target_temperature, Configuration::TARGET_STEAM_TEMP);
    ASSERT_FALSE(status.water_heater_on);
    ASSERT_EQ(strcmp(status.status_message, "Safey temperature exceeded"), 0);
    ASSERT_EQ(status.start_timestamp, 0.0);
    ASSERT_EQ(status.steam_mode_timestamp, 0.0);
}