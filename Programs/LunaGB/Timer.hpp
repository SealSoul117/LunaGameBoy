#pragma once
#include <Luna/Runtime/MemoryUtils.hpp>
using namespace Luna;

struct Emulator;
struct Timer
{
    //! 0xFF04
    //! Only the high 8-bit is accessible via bus, thus behaves like incrementing at 16384Hz (once per 256 clock cycles).
    //! Writing any value to this resets the value to 0.
    u16 div;
    //! 0xFF05 Timer counter
    //! Triggers a INT_TIMER when overflows (exceeds 0xFF).
    u8 tima;
    //! 0xFF06 Timer modulo
    //! The value to reset TIMA to if overflows.
    u8 tma;
    //! 0xFF07 Timer control
    u8 tac;

    u8 read_div() const
    {
        return (u8)(div >> 8);
    }
    u8 clock_select() const
    {
        return (u8)(tac & 0x03);
    }
    bool tima_enabled() const
    {
        return bit_test(&tac, 2);
    }

    void init()
    {
        div = 0xAC00;
        tima = 0x00;
        tma = 0x00;
        tac = 0xF8;
    }
    void tick(Emulator *emu);
    u8 bus_read(u16 address);
    void bus_write(u16 address, u8 data);
};