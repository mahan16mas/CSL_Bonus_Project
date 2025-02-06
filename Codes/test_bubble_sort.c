#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

long sort(int n, int *array)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
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
    FILE *times = fopen("graph//bubble_sort_time.txt", "w");
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
        char destination[100] = "sorted_arrays//bubble_sort//";
        strcat(destination, num);
        strcat(destination, ".txt");
        FILE *arrays_des = fopen(destination, "w");
        print_array_in_file(n, array, arrays_des);
        fclose(arrays_des);
    }
    fclose(times);
}
