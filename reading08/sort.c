/* sort.c */

#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define MAX_NUMBERS (1<<10)

/* Functions */
/*
int compare(const void *a, const void *b)
{
    return (const int *)a - (const int *)b;
}
*/

int compare (const void *a, const void *b)  {
  return ( *(int*)a - *(int*)b);
}

void read_numbers(FILE *stream, int numbers[], size_t n) {
    size_t i = 0;

    while (i < n && scanf("%d", &numbers[i]) != EOF) {
        i++;
    }

    qsort(numbers, i, sizeof(int), compare);
    for(size_t x = 0; x < i; x++)
      printf("%d\n", numbers[x]);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    int numbers[MAX_NUMBERS];
    
    read_numbers(stdin, numbers, MAX_NUMBERS);

    return EXIT_SUCCESS;
}
