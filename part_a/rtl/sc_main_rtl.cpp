#include <systemc.h>
#include "producer_rtl.h"
#include "consumer_rtl.h"

int sc_main(int argc, char* argv[]) {
    // Clock and Signals
    sc_clock clk("clk", 10, SC_NS); // 100MHz clock
    sc_signal<uint32_t> addr_sig;
    sc_signal<uint32_t> data_sig;
    sc_signal<bool> write_en_sig;

    // Instantiate Modules 
    Producer_RTL producer("producer");
    Consumer_RTL consumer("consumer");

    // Port Mapping (Binding)
    producer.clk(clk);
    producer.addr(addr_sig);
    producer.data(data_sig);
    producer.write_en(write_en_sig);

    consumer.clk(clk);
    consumer.addr(addr_sig);
    consumer.data(data_sig);
    consumer.write_en(write_en_sig);

    // Simulation
    sc_start(); // Runs until producer thread finishes 

    // Deliverable: Export image
    consumer.save_image("rtl_output.ppm");

    return 0;
 }
