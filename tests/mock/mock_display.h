#pragma once

#include <lib_coffee_machine/common.h>
#include <lib_coffee_machine/interfaces.h>

class MockDisplay : public BaseDisplay
{
  public:
    MockDisplay() = default;

    bool initialise() override
    {
        return true;
    }
    bool clear() override
    {
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const char *data) override
    {
        printed_data.push_back(std::string(data));
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const int &data) override
    {
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const float &data) override
    {
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const double &data) override
    {
        return true;
    }
    bool display() override
    {
        return true;
    }

    std::vector<std::string> printed_data;
};

class MockCustomDisplay : public BaseDisplay
{
  public:
    MockCustomDisplay() = default;

    bool use_custom_display() override
    {
        return true;
    }

    bool print_custom_display(const Machine::Status &status) override
    {
        printed_status = status;
        return true;
    };

    bool initialise() override
    {
        return true;
    }
    bool clear() override
    {
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const char *data) override
    {
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const int &data) override
    {
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const float &data) override
    {
        return true;
    }
    bool print(const unsigned &col, const unsigned &row, const double &data) override
    {
        return true;
    }
    bool display() override
    {
        return true;
    }

    std::optional<Machine::Status> printed_status;
};
