# 🚀 SoC Tutorial: Image Processing with SystemC-TLM & RTL

> A dual-model implementation of a Test Pattern Generator (TPG) and Memory Consumer system demonstrating image frame transfer across an SoC interconnect using two levels of abstraction.

**Author:** Peter Mbua

---

## 📌 Project Overview

This repository implements a synthetic color gradient generator that transfers a **780×610 image frame** to a memory sink. The project is structured to compare and contrast two hardware modeling abstractions:

| Abstraction | Description |
|---|---|
| **TLM-2.0** | Transaction-Level Modeling using Generic Payload |
| **RTL** | Register-Transfer Level implementation |

### Key Specifications

- **Resolution:** 780 × 610 pixels
- **Data Width:** 32-bit (RGB pixel mapping)
- **Interface:** TLM-2.0 Base Protocol using Generic Payload
- **Verification:** Visual correctness validated by exporting memory buffer to a `.ppm` file

---

## 🛠️ Prerequisites & Setup

### Dependencies

- **SystemC 2.3.x** installed on a Linux environment
- **C++17** compatible compiler (GCC or Clang)

### Environment Configuration

Set the following environment variables before building:

```bash
export SYSTEMC_HOME=/your/path/to/systemc
export LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64:$LD_LIBRARY_PATH
```

---

## 📂 Design Architectures

### Part A: Basic Producer–Consumer

A point-to-point communication link between a **Traffic Generator (Initiator)** and a **Memory Sink (Target)**.

- **Mechanism:** Uses `b_transport` calls to send encapsulated pixel data.
- **Verification:** The Consumer allocates a `std::vector` buffer and exports the final frame to `output_frame.ppm`.

```
┌─────────────────────┐        b_transport        ┌─────────────────────┐
│  Traffic Generator  │ ────────────────────────► │    Memory Sink      │
│    (Initiator)      │                            │      (Target)       │
└─────────────────────┘                            └─────────────────────┘
```

---

### Part B: Router Architecture

Extends Part A by introducing an **interconnect** and **timing annotation** to observe bus contention.

- **Interconnect:** A TLM Router decodes addresses and directs traffic between memory targets.
- **Timing Constraints:**
  - `+10ns` delay per transaction at the Router
  - `+50ns` write latency at the Memory
- **Calculation Task:** Students must calculate and report the **total simulated time** for one full frame transfer.

```
┌──────────────┐     ┌─────────────┐     ┌──────────────┐
│   Initiator  │────►│  TLM Router │────►│  Memory [0]  │
└──────────────┘     └──────┬──────┘     └──────────────┘
                            │
                            └────────────►┌──────────────┐
                                          │  Memory [1]  │
                                          └──────────────┘
```

---

## 🚀 Running the Simulations

### Compilation

The provided `Makefile` links against SystemC and produces an executable named `soc_sim`.

```bash
make clean
make
```

### Execution

```bash
./soc_sim
```

After a successful run, the output image `output_frame.ppm` will be generated in the working directory.

---

## 📊 Submission Requirements

Submit a `.zip` archive containing the following:

1. **Source Code**
   - `producer.h` / `producer.cpp`
   - `consumer.h` / `consumer.cpp`
   - `router.h` / `router.cpp`
   - `sc_main.cpp`

2. **Build & Verification**
   - `Makefile`
   - Generated `output_frame.ppm`

3. **PPT Report** *(Max 7 Slides)*
   - System design understanding and architecture diagram
   - Terminal screenshot showing simulation start and end times
   - Analysis of address offset handling for the second consumer in Part B

---

## ⚠️ Troubleshooting

| Issue | Cause & Fix |
|---|---|
| **Infinite Loop** | Check your inner pixel loop — use `< width`, not `= width`. |
| **Simulation Hang** | Ensure `sc_stop()` is called in the Producer thread after the final pixel is sent, so `sc_main` can finalize the image export. |
| **Missing Header Error** | Include `<systemc.h>` in all files — do **not** use `<system.h>`. |

---

## 📁 Repository Structure

```
.
├── producer.h / producer.cpp    # Traffic Generator (TLM Initiator)
├── consumer.h / consumer.cpp    # Memory Sink (TLM Target)
├── router.h / router.cpp        # TLM Router (Part B)
├── sc_main.cpp                  # Simulation top-level
├── Makefile                     # Build configuration
└── output_frame.ppm             # Generated output (after simulation)
```

---

## 📄 License

This project is submitted as part of an academic SoC design tutorial. All rights reserved by the author.

---

*Authored by **Peter Mbua***
