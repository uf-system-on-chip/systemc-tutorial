# Variables
SYSTEMC_HOME = /usr/local/systemc-2.3.3
CXX          = g++
CXXFLAGS     = -I$(SYSTEMC_HOME)/include -L$(SYSTEMC_HOME)/lib-linux64 \
               -lsystemc -lm -O3 -std=c++17

# Target executable name [cite: 75]
TARGET = soc_sim_rtl

# Source files for RTL version (Ensure these match your RTL filenames)
SRCS = sc_main_rtl.cpp producer_rtl.h consumer_rtl.h

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o rtl_output.ppm waveform.vcd

run: all
	./$(TARGET)
