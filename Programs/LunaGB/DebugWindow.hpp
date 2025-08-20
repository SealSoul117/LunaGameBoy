#pragma once
#include <Luna/Runtime/Vector.hpp>
#include <Luna/Runtime/String.hpp>
using namespace Luna;

struct DebugWindow
{
    bool show = false;

    void gui();
    void cpu_gui();

    String cpu_log;
    bool cpu_logging = false;

    Vector<u8> serial_data;
    void serial_gui();
};