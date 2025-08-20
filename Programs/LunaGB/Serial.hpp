#pragma once
#include <Luna/Runtime/RingDeque.hpp>
using namespace Luna;

struct Emulator;
struct Serial
{
    u8 sb;
    u8 sc;

    bool transferring;

    RingDeque<u8> output_buffer;

    // The current transfer out byte.
    u8 out_byte;
    // The transferring bit index (7 to 0).
    i8 transfer_bit;

    bool is_master() const { return bit_test(&sc, 0); }
    bool transfer_enable() const { return bit_test(&sc, 7); }

    void begin_transfer();
    void process_transfer(Emulator *emu);
    void end_transfer(Emulator *emu);

    void init()
    {
        sb = 0xFF;
        sc = 0x7C;
        transferring = false;
    }
    void tick(Emulator *emu);
    u8 bus_read(u16 addr);
    void bus_write(u16 addr, u8 data);
};