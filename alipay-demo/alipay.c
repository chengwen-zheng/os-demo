#include "../c-demo/thread.h"

unsigned long balance = 100;

void Alipay_withdraw(int amt) {
  if (balance >= amt) {
    usleep(1);  // Unexpected delays
    balance -= amt;
  }
}

void Talipay(int id) {
  Alipay_withdraw(100);
}

int main() {
  spawn(Talipay);
//   spawn(Talipay);
  join();
  printf("balance = %lu\n", balance);
}