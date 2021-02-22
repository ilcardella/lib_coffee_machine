# Coffee Machine Library

The purpose of this library is to model a generic Coffee Machine creating a level of abstraction on the platform or hardware used for deployment.
The original application that led to its development was a PID controller for a Gaggia manual coffee machine, deployed on an Arduino Nano and then on a Raspberry PI Pico. The change of platform does not affect the functionalities of the library and speeded up the development for the new hardware.

Furthermore, being hardware independent, the library allows automated testing in the CI pipeline.

The library uses C++17 features.

## Getting started

The are different ways you can use this library in your project, depending on your setup
you might prefer to clone it, add as a git submodule or include it with CMake.

### CMake

In this configuration the first step is to install the library in your development
environment. The `Makefile` provide a target to do exactly that.

```
make install
```

Then in your top-level `CMakelists.txt` you can find the library and then link your
targets against with, as in the example below:

```CMake
project(my_project)
...
find_package(lib_coffee_machine CONFIG REQUIRED)
...
add_executable(${PROJECT_NAME} ...)
target_link_libraries(${PROJECT_NAME}
                        lib_coffee_machine::lib_coffee_machine
                        ...
)
...
```

### Clone

Clone this repository into your project workspace and make sure the source code is
accessible to your codebase.
For example if you are using `CMake`, you might need a `add_subdirectory(path/to/library)`
instruction.
If your project is Arduino based, then you need to clone this repository inside the
`libraries` subfolder

```bash
git clone https://github.com/ilcardella/lib_coffee_machine.git libraries/lib_coffee_machine
```

### As submodule

Create a submodule in your project with

```bash
git submodule add https://github.com/ilcardella/lib_coffee_machine.git lib_coffee_machine
```

Then, as in the previous option, just integrate the library with your project.

### Arduino library

TBD

## How to use

The library consists of 4 main components:
- The `interfaces`
- The `configuration`
- The `adapter`
- The `CoffeeMachine` class

### Interfaces

The `interfaces.h` provides a list of base abstract classes that need to be implemented to support the deployment platform. They provide an interface and the level of abstraction required to make this library generic for any hardware.

#### Example

The following example shows how you can implement a TSIC306 digital temperature sensor for your Arduino project

custom_temperture_sensor.h
```c++
#pragma once

#include "lib_coffee_machine/interfaces.h"
// Arduino library for TSIC sensor
#include <TSIC.h>

class CustomTemperatureSensor : public BaseSensor
{
  public:
    CustomTemperatureSensor(const unsigned char &pin) : sensor(pin, NO_VCC_PIN, TSIC_30x)
    {
        pinMode(pin, INPUT);
    }

    bool read_sensor(float *value) override
    {
        unsigned short raw;
        if (not sensor.getTemperature(&raw))
        {
            return false;
        }

        auto temp = sensor.calc_Celsius(&raw);

        *value = temp;
        return true;
    }

  private:
    TSIC sensor;
};

```

### Configuration

The library accept a template argument which should provide static constants of configurable parameters.
The `default_configuration.h` contains a sample `struct` with configuration parameters required by the `CoffeeMachine` class. You can use that straight away or create a new derived instance replacing the parameters you want.

#### Example

The following example shows how you can override the default configuration replacing some of the parameteres

my_configuration.h
```c++
#pragma once

#include <lib_coffee_machine/default_configuration.h>

struct MyConfiguration : public DefaultConfiguration
{
    // Replace the target water temperature
    inline static constexpr double TARGET_WATER_TEMP = 92.0;
    // Replace the target steam temperature
    inline static constexpr double TARGET_STEAM_TEMP = 155.0;
};
```

### Adapter

The second template parameter required by the library is the `Adapter`. A simple class with static methods that abstract functions that are platform specific. e.g. the Arduino `delay()`.

#### Example

This example shows an adapter class for the Arduino MCU to abstract platform specific methods. You can find another example in the `test` folder of this repository.

```c++
#pragma once

#include <Arduino.h>

class ArduinoAdapter
{
  public:
    inline static void delay(unsigned long ms)
    {
        ::delay(ms);
    }

    inline static unsigned long millis()
    {
        return ::millis();
    }

    inline static char *dtostrf(double val, signed char width, unsigned char prec,
                                char *s)
    {
        return ::dtostrf(val, width, prec, s);
    }
};

```

### CoffeeMachine

The `coffee_machine.h` provides the main library class and interface that needs to be instantiatd and spinned in your main function.

#### Example

```c++

#include <lib_coffee_machine/coffee_machine.h>

// Implementation of the interfaces for your platform
#include <my_interfaces.h>
// Implementation of the Adapter
#include <my_adapter.h>
// Implementation of the Configuration
#include <my_configuration.h>

using Adapter = MyAdapter;
using Configuration = MyConfiguration;

void main()
{
    // Create the custom interfaces
    CustomTemperatureSensor* temp_sensor = new CustomTemperatureSensor();
    ...

    // Create the coffee machine instance
    CoffeeMachine<Adapter, Configuration> machine(temp_sensor, ...);

    while (true)
    {
        machine.spin();
    }
}

```
