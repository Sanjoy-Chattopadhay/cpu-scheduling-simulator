# 🧠 CPU Scheduling Simulator (C Language)

A terminal-based simulator for classic **CPU scheduling algorithms** implemented in **C**, built as part of my M.Tech coursework to demonstrate core Operating Systems concepts such as **process scheduling**, **preemption**, **turnaround time**, and **waiting time** calculation.

> 💻 Built with: C (Dev C++ compatible)  
> 📘 Topics: FCFS, SJF, Round Robin, SRTF  
> 🛠️ Extras: Real-time simulation, CSV export, Gantt Chart output  

---

## 🎯 Features

✅ Supports the following **CPU Scheduling Algorithms**:
- **First Come First Serve (FCFS)**
- **Shortest Job First (SJF - Non-Preemptive)**
- **Round Robin (RR)**
- **Shortest Remaining Time First (SRTF - Preemptive)**

✅ **Gantt Chart** display for visual representation of CPU execution  
✅ Calculates and prints:
- Completion Time (CT)
- Turnaround Time (TAT)
- Waiting Time (WT)
- Average TAT and WT

✅ **Cross-platform support** (Tested on Windows with Dev C++, and Linux with GCC)  
✅ **CSV Export** for importing results into Excel  
✅ Easily extendable to include **Priority Scheduling**, **Aging**, and **Multicore Simulation**

---

## 🚀 How to Run

### 🖥️ For Windows (Dev C++)
1. Open `cpu_scheduler.c` in Dev C++
2. Compile & Run (F11)

### 🧪 For Linux
```bash
gcc cpu_scheduler.c -o scheduler
./scheduler
