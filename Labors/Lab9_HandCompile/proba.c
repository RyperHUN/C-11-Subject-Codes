#include <stdio.h>
 
static void hello(int i) {
    printf("Hello %d!\n", i);
}
 
int main(void) {
    for (int i = 1; i <= 5; ++i)
        hello(i);
}
