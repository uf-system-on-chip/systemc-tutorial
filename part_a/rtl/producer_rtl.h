#include <systemc.h>

SC_MODULE(Producer_RTL) {
    sc_in<bool> clk;
    sc_out<uint32_t> addr;
    sc_out<uint32_t> data;
    sc_out<bool> write_en;

    void process() {
        // Initial state
        write_en.write(false);
        wait();

        // Generate 780x610 pattern
        for (int y = 0; y < 610; y++) {
            for (int x = 0; x < 780; x++) {
                addr.write((y * 780 + x) * 4); // 32-bit byte addressing 
                data.write(x % 256);           // Synthetic gradient pattern 
                write_en.write(true);
                wait(); // Wait for one clock cycle
            }
        }
        write_en.write(false);
        wait();
        cout << "Producer finished at " << sc_time_stamp() << endl;
        sc_stop(); // This kills the simulation kernel
    }

    SC_CTOR(Producer_RTL) {
        SC_THREAD(process);
        sensitive << clk.pos();
    }
};
