// Porownanie czasu sortowania tablicy w zaleznosci od implementacji Quick Sorta:
// Normal QS
// Random Pivot QS
// Median Pivot QS
// Built-in qsort

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef void (*gen)(int*, int);
void generate_random(int*, int);
void generate_sorted(int*, int);
void generate_sorted_reverse(int*, int);
void generate_almost_sorted(int*, int);
void generate_almost_sorted_reverse(int*, int);
void insertionSort(int*, int);
void printArray(int*, int);
double timetest (int*, int, gen);

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *arr, int left, int right){
    int pivot = arr[right];
    int i = left;
    for(int j = left; j < right; j++){
        if(arr[j] < pivot){
            swap(&arr[j], &arr[i]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

int medianPartition(int *arr, int left, int right){
    int mid = (left + right)/2;
    if(arr[right] < arr[left]) {
        swap(&arr[left], &arr[right]);
    }
    if(arr[mid] < arr[left])
    {
        swap(&arr[mid], &arr[left]);
    }
    if(arr[right] < arr[mid]) {
        swap(&arr[right], &arr[mid]);
    }
    // zeby mid byl na koncu
    swap(&arr[mid], &arr[right]);
    return partition(arr, left, right);
}

int randPartition(int *arr, int left, int right){
    int r = rand() % (right - left) + left;
    swap(&arr[r], &arr[right]);
    return partition(arr, left, right);
}

void quicksort_common(int *arr, int left, int right){
    if(right > left){
        int pi = partition(arr, left, right);
        quicksort_common(arr, left, pi - 1);
        quicksort_common(arr, pi + 1, right);
    }
}

void quicksort_rand(int *arr, int left, int right){
    if(right > left){
        int pi = randPartition(arr, left, right);
        quicksort_rand(arr, left, pi - 1);
        quicksort_rand(arr, pi + 1, right);
    }
}

void quicksort_median(int *arr, int left, int right){
    if(right > left){
        int pi = medianPartition(arr, left, right);
        quicksort_median(arr, left, pi - 1);
        quicksort_median(arr, pi + 1, right);
    }
}

void generate_random(int* arr, int n) {
    //	You can experiment with the modulo value.
    //	The bigger number the less duplicates in the array.
    for(int i = 0; i < n; ++i) arr[i] = rand() % 1000000;
}

void generate_almost_sorted(int* arr, int n) {
    //	initialize sorted array
    for(int i = 0; i < n; ++i) arr[i] = i;
    //	Make some swaps to disturb the order
    //	Experiment with different # of swaps
    for(int i = 0; i < 100; ++i) {
        int j = rand() % n;
        int k = rand() % n;
        while(j == k) k = rand() % n;
        swap(&arr[j], &arr[k]);
    }
}

void generate_sorted(int* arr, int n) {
    for(int i = 0; i < n; ++i) arr[i] = i;
}

void generate_almost_sorted_reverse(int* arr, int n) {
    //	initialize array sorted in reverse order
    for(int i = 0; i < n; ++i) arr[i] = n - i;
    //	Make some swaps to disturb the order
    //	Experiment with different # of swaps
    for(int i = 0; i < 100; ++i) {
        int j = rand() % n;
        int k = rand() % n;
        while(j == k) k = rand() % n;
        swap(&arr[j], &arr[k]);
    }
}

void generate_sorted_reverse(int* arr, int n) {
    for(int i = 0; i < n; ++i) arr[i] = n - i;
}

double timetestQuickSortCommon (int* arr, int n, gen fgen) {

    clock_t t0, t1;
    fgen(arr, n);

    //	Wait for clock() roll over before starting
    t0 = clock();
    while (t0 == (t1 = clock()));

    t0 = t1;
    quicksort_common(arr, 0, n - 1);
    t1 = clock();

    return (t1 - t0) * (1.0 / CLOCKS_PER_SEC);
}

double timetestQuickSortRand (int* arr, int n, gen fgen) {

    clock_t t0, t1;
    fgen(arr, n);

    //	Wait for clock() roll over before starting
    t0 = clock();
    while (t0 == (t1 = clock()));

    t0 = t1;
    quicksort_rand(arr, 0, n - 1);
    t1 = clock();

    return (t1 - t0) * (1.0 / CLOCKS_PER_SEC);
}

double timetestQuickSortMedian (int* arr, int n, gen fgen) {

    clock_t t0, t1;
    fgen(arr, n);

    //	Wait for clock() roll over before starting
    t0 = clock();
    while (t0 == (t1 = clock()));

    t0 = t1;
    quicksort_median(arr, 0, n - 1);
    t1 = clock();

    return (t1 - t0) * (1.0 / CLOCKS_PER_SEC);
}

int comparetor (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

double timetestQsort (int* arr, int n, gen fgen) {

    clock_t t0, t1;
    fgen(arr, n);

    //	Wait for clock() roll over before starting
    t0 = clock();
    while (t0 == (t1 = clock()));

    t0 = t1;
    qsort(arr, n, sizeof(int), comparetor);
    t1 = clock();

    return (t1 - t0) * (1.0 / CLOCKS_PER_SEC);
}

int main() {
    srand(time(NULL));
    int Z = 1;

    while(Z--){

        int n = 600000;
        int *arr = malloc(n * sizeof(int));

        double d1 = timetestQuickSortCommon(arr, n, generate_random);
        double d2 = timetestQuickSortRand(arr, n, generate_random);
        double d3 = timetestQuickSortMedian(arr, n, generate_random);
        double d4 = timetestQsort(arr, n, generate_random);

        printf("Pomiar dla n = %d (random)\n", n);
        printf("%30s: %12.2e [s]\n", "Common Quick Sort", d1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", d2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", d3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", d4);


        n = 30000;
        d1 = timetestQuickSortCommon(arr, n, generate_random);
        d2 = timetestQuickSortRand(arr, n, generate_random);
        d3 = timetestQuickSortMedian(arr, n, generate_random);
        d4 = timetestQsort(arr, n, generate_random);

        printf("Pomiar2 dla n = %d (random)\n", n);
        printf("%30s: %12.2e [s]\n", "Common Quick Sort", d1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", d2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", d3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", d4);


        int k = 600000;
        int *arr2 = malloc(k * sizeof(int));

        //double a1 = timetestQuickSortCommon(arr2, k, generate_almost_sorted);
        double a2 = timetestQuickSortRand(arr2, k, generate_almost_sorted);
        double a3 = timetestQuickSortMedian(arr2, k, generate_almost_sorted);
        double a4 = timetestQsort(arr2, k, generate_almost_sorted);

        printf("Pomiar dla k = %d (almost sorted)\n", k);
        // commonSort nie daje rady przy wiekszym k
        //printf("%30s: %12.2e [s]\n", "Common Quick Sort", a1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", a2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", a3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", a4);

        k = 30000;
        int *arr22 = malloc(k * sizeof(int));
        // dla k = 10000 common jeszcze daje rade
        double a1 = timetestQuickSortCommon(arr22, k, generate_almost_sorted);
        a2 = timetestQuickSortRand(arr22, k, generate_almost_sorted);
        a3 = timetestQuickSortMedian(arr22, k, generate_almost_sorted);
        a4 = timetestQsort(arr22, k, generate_almost_sorted);

        printf("Pomiar2 dla k = %d (almost sorted)\n", k);
        // commonSort nie daje rady przy wiekszym k
        printf("%30s: %12.2e [s]\n", "Common Quick Sort", a1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", a2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", a3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", a4);

        int m = 600000;
        // 10000000 ciekawa
        int *arr3 = malloc(m * sizeof(int));

        // double m1 = timetestQuickSortCommon(arr3, m, generate_sorted);
        double m2 = timetestQuickSortRand(arr3, m, generate_sorted);
        double m3 = timetestQuickSortMedian(arr3, m, generate_sorted);
        double m4 = timetestQsort(arr3, m, generate_sorted);

        printf("Pomiar dla m = %d (sorted)\n", m);
        // printf("%30s: %12.2e [s]\n", "Common Quick Sort", m1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", m2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", m3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", m4);

        m = 30000;
        // 10000000 ciekawa

        double m1 = timetestQuickSortCommon(arr3, m, generate_sorted);
        m2 = timetestQuickSortRand(arr3, m, generate_sorted);
        m3 = timetestQuickSortMedian(arr3, m, generate_sorted);
        m4 = timetestQsort(arr3, m, generate_sorted);

        printf("Pomiar2 dla m = %d (sorted)\n", m);
        printf("%30s: %12.2e [s]\n", "Common Quick Sort", m1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", m2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", m3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", m4);


        int h = 600000;
        // int h = 10000000 ciekawe
        int *arr4 = malloc(h * sizeof(int));

        // double h1 = timetestQuickSortCommon(arr4, h, generate_almost_sorted_reverse);
        double h2 = timetestQuickSortRand(arr4, h, generate_almost_sorted_reverse);
        double h3 = timetestQuickSortMedian(arr4, h, generate_almost_sorted_reverse);
        double h4 = timetestQsort(arr4, h, generate_almost_sorted_reverse);

        printf("Pomiar dla h = %d (almost reverse sorted)\n", h);
        // przy wiekszym h nie dziala
        // printf("%30s: %12.2e [s]\n", "Common Quick Sort", h1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", h2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", h3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", h4);

        h = 30000;
        // int h = 10000000 ciekawe

        double h1 = timetestQuickSortCommon(arr4, h, generate_almost_sorted_reverse);
        h2 = timetestQuickSortRand(arr4, h, generate_almost_sorted_reverse);
        h3 = timetestQuickSortMedian(arr4, h, generate_almost_sorted_reverse);
        h4 = timetestQsort(arr4, h, generate_almost_sorted_reverse);

        printf("Pomiar2 dla h = %d (almost reverse sorted)\n", h);
        // przy wiekszym h nie dziala
        printf("%30s: %12.2e [s]\n", "Common Quick Sort", h1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", h2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", h3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", h4);


        int s = 600000;
        // cieakwe dla s = 10000000
        int *arr5 = malloc(s * sizeof(int));

        // double s1 = timetestQuickSortCommon(arr5, s, generate_sorted_reverse);
        double s2 = timetestQuickSortRand(arr5, s, generate_sorted_reverse);
        double s3 = timetestQuickSortMedian(arr5, s, generate_sorted_reverse);
        double s4 = timetestQsort(arr5, s, generate_sorted_reverse);

        printf("Pomiar dla s = %d (sorted reverse)\n", s);
        // printf("%30s: %12.2e [s]\n", "Common Quick Sort", s1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", s2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", s3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", s4);

        s = 30000;
        // cieakwe dla s = 1000000

        double s1 = timetestQuickSortCommon(arr5, s, generate_sorted_reverse);
        s2 = timetestQuickSortRand(arr5, s, generate_sorted_reverse);
        s3 = timetestQuickSortMedian(arr5, s, generate_sorted_reverse);
        s4 = timetestQsort(arr5, s, generate_sorted_reverse);

        printf("Pomiar2 dla s = %d (sorted reverse)\n", s);
        printf("%30s: %12.2e [s]\n", "Common Quick Sort", s1);
        printf("%30s: %12.2e [s]\n", "Random Quick Sort", s2);
        printf("%30s: %12.2e [s]\n", "Median Quick Sort", s3);
        printf("%30s: %12.2e [s]\n", "Built-in qsort", s4);

        free(arr5);
        free(arr4);
        free(arr3);
        free(arr2);
        free(arr22);
        free(arr);
    }
    return 0;
}
