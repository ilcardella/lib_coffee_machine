#include "common_test.h"

class TestCustomDisplay : public CommonTest
{
};

TEST_F(TestCustomDisplay, testDisplayWithoutCustomImplementation)
{
    auto status = machine->spin();

    ASSERT_EQ(display.printed_data.size(), 4);
    ASSERT_EQ(display.printed_data[0], "Water mode");
    ASSERT_EQ(display.printed_data[1], "10.0 C  ");
    ASSERT_EQ(display.printed_data[2], "95.0 C  ");
    ASSERT_EQ(display.printed_data[3], "Heating...");
}

TEST_F(TestCustomDisplay, testDisplayWithCustomImplementation)
{
    // Create a new Machine with a Custom Display
    MockCustomDisplay custom_display;
    auto custom_machine = new CoffeeMachine<Adapter, Configuration>(
        &controller, &serial, &mode_switch_pin, &custom_display, &heater_pin,
        &water_sensor, &steam_sensor);

    time_step();
    auto status = custom_machine->spin();

    ASSERT_TRUE(custom_display.printed_status.has_value());
    ASSERT_EQ(custom_display.printed_status.value().machine_mode,
              Machine::Mode::WATER_MODE);
    ASSERT_EQ(custom_display.printed_status.value().current_temperature, 10.0);
    ASSERT_EQ(custom_display.printed_status.value().target_temperature,
              Configuration::TARGET_WATER_TEMP);
    ASSERT_TRUE(custom_display.printed_status.value().water_heater_on);
    ASSERT_EQ(strcmp(custom_display.printed_status.value().status_message, "Heating..."),
              0);
    ASSERT_EQ(custom_display.printed_status.value().start_timestamp, 500.0);
    ASSERT_EQ(custom_display.printed_status.value().steam_mode_timestamp,
              Adapter::millis_ret);
}
