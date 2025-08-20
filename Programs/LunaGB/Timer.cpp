#include "Emulator.hpp"
#include "Timer.hpp"

void Timer::tick(Emulator* emu)
{
    u16 pre_div = div;
    div++;
    if (tima_enabled())
    {
        bool tima_update = false;
        switch(clock_select())
        {
            case 0: // 4096Hz
                tima_update = (pre_div & (1 << 9)) && (!(div & (1 << 9)));
                break;
            case 1: // 262144Hz
                tima_update = (pre_div & (1 << 3)) && (!(div & (1 << 3)));
                break;
            case 2: // 65536Hz
                tima_update = (pre_div & (1 << 5)) && (!(div & (1 << 5)));
                break;
            case 3: // 16384Hz
                tima_update = (pre_div & (1 << 7)) && (!(div & (1 << 7)));
                break;
        }
        if (tima_update)
        {
            if (tima == 0xFF)
            {
                emu->int_flags |= INT_TIMER;
                tima = tma;
            }
            else
            {
                tima++;
            }
        }
    }
}
u8 Timer::bus_read(u16 address)
{
    luassert(address <= 0xFF07 && address >= 0xFF04);
    switch (address)
    {
        case 0xFF04: 
            return read_div();
        case 0xFF05:
            return tima;
        case 0xFF06:
            return tma;     
        case 0xFF07:
            return tac;
    }
}
void Timer::bus_write(u16 address, u8 data)
{
    luassert(address <= 0xFF07 && address >= 0xFF04);
    switch (address)
    {        
        case 0xFF04: 
            div = 0; // Reset DIV to 0.
            break;      
        case 0xFF05:
            tima = data;
            break;
        case 0xFF06:
            tma = data;
            break;
        case 0xFF07:
            tac = 0xF8 | (data & 0x07);
            break;
    }
    return;
}