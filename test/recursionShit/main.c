#include <stdio.h>
#include <stdlib.h>

// recursion
void printReverseString(char str[], int k)
{
    if(k == 0)
    {
        return;
    }
    printf("%c", str[k-1]);
    printReverseString(str, k-1);
}

int main(void)
{
    char word[] = "cat";
    int k = 3;
    printReverseString(word, k);
}
