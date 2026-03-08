#include <systemc.h>
#include <vector>
#include <fstream>
#include <iostream>

SC_MODULE(Consumer_RTL) {
    sc_in<bool> clk;
    sc_in<uint32_t> addr;
    sc_in<uint32_t> data;
    sc_in<bool> write_en;

    std::vector<uint32_t> mem; // Memory buffer [cite: 17]

    void listen() {
        if (write_en.read()) {
            uint32_t idx = addr.read() / 4;
            if (idx < mem.size()) {
                mem[idx] = data.read();
            }
        }
    }

    // Function to export data to .ppm format
    void save_image(const char* filename) {
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "P6\n780 610\n255\n"; // PPM Header
        for (size_t i = 0; i < mem.size(); ++i) {
            unsigned char r = (mem[i] >> 16) & 0xFF;
            unsigned char g = (mem[i] >> 8) & 0xFF;
            unsigned char b = mem[i] & 0xFF;
            ofs << r << g << b;
        }
        ofs.close();
        std::cout << "Image saved to " << filename << std::endl;
    }

    SC_CTOR(Consumer_RTL) {
        mem.resize(780 * 610, 0); // Allocate for resolution [cite: 13, 17]
        SC_METHOD(listen);
        sensitive << clk.pos();
    }
};
