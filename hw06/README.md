1.	Where does Julia Cartwright work? National Instruments
2.	What is PREEMT_RT? A patch that converts Linux to a fully preemptible kernel
3.	What is mixed criticality? Processing that has a mix of critical, real-time tasks and unbounded, non-real-time tasks
4.	How can drivers misbehave? If real-time and non-real-time tasks are sharing the same driver stacks, the drivers can fail to perform real-time tasks with the level of critical timing necessary
5.	What is delta in Figure 1? The time at which an external event occurs (some interrupt trigger) until the relevant real-time task executes
6.	What is Cyclictest[2]? Takes a timestamp, sleeps for a specified time, and takes another timestamp. The difference, subtracting the sleep time, is the delta from Figure 1
7.	What is plotted in Figure 2? The ? of Figure 1 for preempt and preempt_rt
8.	What is dispatch latency?  Scheduling latency? The amount of time it takes between the hardware event occuring to the interrupt dispatcher having occured and the scheduler prompt. The scheuling latency is the amount of time between the scheduler being prompted and the processor having the interrupt scheduled 
9.	What is mainline? The main execution thread (?)
10.	What is keeping the External event in Figure 3 from starting? A non-critical interrupt requirement that blocks a critical interrupt from being handled
11.	Why can the External event in Figure 4 start sooner? Activate additional threads to accomodate non-critical and critical interrupts
