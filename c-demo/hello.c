#include "../thread.h"

int x = 0;
void Thello(int id) {
    x++;
    printf("%d\n" , x );

    //   while (1) {
    //     // printf("%c", "_ABCDEFGHIJKLMNOPQRSTUVWXYZ"[id]);
    //   }
}

int main() {
  for (int i = 0; i < 10; i++) {
    spawn(Thello);
  }
}