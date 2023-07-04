#include "../thread.h"
#include "../thread-sync.h"

int n, count = 0;
mutex_t lk = MUTEX_INIT();
cond_t cv = COND_INIT();

#define CAN_PRODUCE (count < n)
#define CAN_CONSUME (count > 0)

void Tproduce()
{
    while (1)
    {
        mutex_lock(&lk);
        if (!CAN_PRODUCE)
        {
            cond_wait(&cv, &lk);
        }
        printf("(");
        count++;
        // slingal the wrong threads。
        // maybe it is Tproduce. when there are more than 2 threads, it will be wrong
        cond_signal(&cv);
        mutex_unlock(&lk);
    }
}

void Tconsume()
{
    while (1)
    {
        mutex_lock(&lk);
        if (!CAN_CONSUME)
        {
            cond_wait(&cv, &lk);
        }
        printf(")");
        count--;
        // slingal the wrong threads。
        // maybe it is Tconsume. when there are more than 2 threads, it will be wrong
        cond_signal(&cv);
        mutex_unlock(&lk);
    }
}

int main(int argc, char *argv[])
{
    assert(argc == 3);
    n = atoi(argv[1]);
    int T = atoi(argv[2]);
    setbuf(stdout, NULL);
    for (int i = 0; i < T; i++)
    {
        spawn(Tproduce);
        spawn(Tconsume);
    }
}