
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

long sort(int n, int *arr)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    asm volatile(
        "movl $1, %%ecx          \n\t"
        "start_loop:             \n\t"
        "cmpl %%edi, %%ecx       \n\t"
        "jge end_sort            \n\t"
        "movl (%%esi, %%ecx, 4), %%eax \n\t"
        "movl -4(%%esi, %%ecx, 4), %%ebx \n\t"
        "cmpl %%eax, %%ebx       \n\t"
        "jle no_swap             \n\t"

        "movl %%eax, -4(%%esi, %%ecx, 4) \n\t"
        "movl %%ebx, (%%esi, %%ecx, 4)   \n\t"
        "decl %%ecx              \n\t"
        "testl %%ecx, %%ecx      \n\t"
        "jz set_to_one           \n\t"
        "jmp start_loop          \n\t"
        "no_swap:                \n\t"
        "incl %%ecx              \n\t"
        "jmp start_loop          \n\t"
        "set_to_one:             \n\t"
        "movl $1, %%ecx          \n\t"
        "jmp start_loop          \n\t"
        "end_sort:               \n\t"
        :
        : "S"(arr), "D"(n)
        : "eax", "ebx", "ecx", "memory");
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
    FILE *times = fopen("graph//asm_gnome_sort_time.txt", "w");
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
        char destination[100] = "sorted_arrays//asm_gnome_sort//";
        strcat(destination, num);
        strcat(destination, ".txt");
        FILE *arrays_des = fopen(destination, "w");
        print_array_in_file(n, array, arrays_des);
        fclose(arrays_des);
    }
    fclose(times);
}
