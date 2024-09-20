#include <stdio.h>

void frt(int *x, int y) {
    int i;
    for (i = 0; i < 5; i++)
        *(x + i) += 2;
    y += 2;
}

int main() {
    int a[5], i, b = 16;
    for (i = 0; i < 5; i++)
        a[i] = 2 * i;
    frt(a, b);
    for (i = 0; i < 5; i++)
        printf("\n%d", a[i]);
    printf("\n%d", b);
}


