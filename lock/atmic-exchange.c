int xchg(int volatile *ptr, int newval)
{
    int result;
    asm volatile(
        // 指令自带 memory barrier
        "lock xchgl %0, %1"
        : "+m"(*ptr), "=a"(result)
        : "1"(newval)
        // Compiler barrier
        : "memory");
    return result;
}