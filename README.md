# os-demo

This demo is written by jyy in Nanjing University. It simlutes the execution of the operating system.

1. you can execute `python3 os-modal.py ./threads.py`, obversve execution results.

2. mosaic.py implements a modeled operating system and state space explorer. It mainly contains the following parts.

   - Modeled operating system: Defines 9 system calls, maintains thread, heap, storage status, etc. Through sys_xxx() system calls, the application can interact with the operating system model. The operating system implements process scheduling, storage devices, etc.

   - State space explorer: Explores the state space of the operating system through random selection (run) or exhaustion (check), and generates execution paths and accessed states.

   - Source code analysis: Parses the source code of the application, replaces the sys_xxx() system calls in the source code with yield 'sys_xxx', args, so that the application can interact with the operating system model as a coroutine.

   - Serialization and visualization: Serializes the exploration results (execution paths, states) to JSON for easy follow-up processing (such as visualization).

3. python3 ./mosaic.py -c spinlock.py | grep stdout | sort | uniq
   spinlock.py：In the main function, two worker threads are created using sys_spawn(). One worker uses ( and ) as the enter and exit characters, while the other worker uses [ and ]. This exhaustively tests all possible combinations of enter and exit characters to ensure that the locking mechanism is working correctly.
   you can execute `python3 os-modal.py ./threads.py`, obversve execution results.
