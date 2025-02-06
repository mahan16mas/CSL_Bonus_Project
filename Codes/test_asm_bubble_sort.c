
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

long sort(int n, int *arr)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    asm volatile(
        "start_loop: \n\t"
        "movl %1, %%ecx          \n\t"
        "decl %%ecx              \n\t"
        "jz end_sort             \n\t"
        "movl $0, %%edx          \n\t"
        "outer_loop: \n\t"
        "movl %%edx, %%ebx       \n\t"
        "inner_loop: \n\t"
        "movl (%%esi, %%ebx, 4), %%eax    \n\t"
        "movl 4(%%esi, %%ebx, 4), %%edi   \n\t"
        "cmpl %%edi, %%eax                \n\t"
        "jle no_swap                     \n\t"
        "movl %%edi, (%%esi, %%ebx, 4)    \n\t"
        "movl %%eax, 4(%%esi, %%ebx, 4)   \n\t"
        "no_swap: \n\t"
        "incl %%ebx                       \n\t"
        "cmpl %%ecx, %%ebx                \n\t"
        "jl inner_loop                    \n\t"
        "incl %%edx                       \n\t"
        "cmpl %%ecx, %%edx                \n\t"
        "jl outer_loop                    \n\t"

        "end_sort: \n\t"
        :
        : "S"(arr), "D"(n)
        : "eax", "ebx", "ecx", "edx", "memory");
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}
void print_array_in_file(int n, int *array, FILE *file)
{
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", array[i]);
    }
}

int main()
{
    FILE *times = fopen("graph//asm_bubble_sort_time.txt", "w");
    for (int j = 1; j <= 100000; j += 1000)
    {
        char name[] = "Samples//", num[7];
        sprintf(num, "%d", j);
        strcat(name, num);
        strcat(name, ".txt");
        FILE *file = fopen(name, "r");
        int n;
        fscanf(file, "%d", &n);
        printf("%d\n", j);
        int array[n];
        for (int i = 0; i < n; i++)
        {
            fscanf(file, "%d", &array[i]);
        }
        fprintf(times, "%ld\n", sort(n, array));
        fclose(file);
        char destination[100] = "sorted_arrays//asm_bubble_sort//";
        strcat(destination, num);
        strcat(destination, ".txt");
        FILE *arrays_des = fopen(destination, "w");
        print_array_in_file(n, array, arrays_des);
        fclose(arrays_des);
    }
    fclose(times);
}
