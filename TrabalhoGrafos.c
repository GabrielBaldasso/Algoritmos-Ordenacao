#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//1-Inseção direta
void insertionSort(int arr[], int n, double *timeTaken) {
    clock_t start = clock();
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

//2-BubbleSort:
void bubbleSort(int arr[], int n, double *timeTaken) {
    clock_t start = clock();
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

//3-Seleção direta:
void selectionSort(int arr[], int n, double *timeTaken) {
    clock_t start = clock();
    int i, j, min_idx;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

//4-ShellSort:
void shellSort(int arr[], int n, double *timeTaken) {
    clock_t start = clock();
    int gap, i, j, temp;
    for (gap = n/2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i += 1) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

//5-QuickSort:
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, double *timeTaken) {
    clock_t start = clock();
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1, timeTaken);
        quickSort(arr, pi + 1, high, timeTaken);
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}


//6-HeapSort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n, double *timeTaken) {
    clock_t start = clock();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

//7-MergeSort

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r, double *timeTaken) {
    clock_t start = clock();
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, timeTaken);
        mergeSort(arr, m + 1, r, timeTaken);
        merge(arr, l, m, r);
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}
//8-RadixSort
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n, double *timeTaken) {
    clock_t start = clock();
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
    *timeTaken = ((double) (clock() - start)) / CLOCKS_PER_SEC;
}

void printArray(int x[], int tamanho){
    printf("Array ordenado:\n");
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}


void main(){
    int choice = -1;
    double timeTaken;
    int numMaxElementos;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &numMaxElementos);
    int array[numMaxElementos];
    int i;

    srand(time(NULL)); // inicializa a semente aleatória com o tempo atual

    int escolha = 0;
    printf("Escolha a ordem do array:\n");
    printf("1 - Ordem crescente\n");
    printf("2 - Ordem decrescente\n");
    printf("3 - Ordem aleatória\n");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            // preenche o array em ordem crescente
            for (i = 0; i < numMaxElementos; i++) {
                array[i] = i + 1;
            }
            break;
        case 2:
            // preenche o array em ordem decrescente
            for (i = 0; i < numMaxElementos; i++) {
                array[i] = numMaxElementos - i;
            }
            break;
        case 3:
            // preenche o array de forma aleatória
            for (i = 0; i < numMaxElementos; i++) {
                array[i] = rand() % 100; // gera um número aleatório entre 0 e 99
            }
            break;
        default:
            printf("Opção inválida!\n");
    }

    // exibe o array preenchido
    printf("Array preenchido:\n");
    for (i = 0; i < numMaxElementos; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");


    while (choice != 0) {
        printf("Choose a sorting algorithm:\n");
        printf("1. Insertion Sort\n");
        printf("2. Bubble Sort\n");
        printf("3. Selection Sort\n");
        printf("4. Shell Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Heap Sort\n");
        printf("7. Merge Sort\n");
        printf("8. RadixSort\n");
        printf("0. Quit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Sorting using Insertion Sort...\n");
                insertionSort(array, numMaxElementos, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in Insertion Sort: %f seconds\n", timeTaken);
                break;
            case 2:
                printf("Sorting using Bubble Sort...\n");
                bubbleSort(array, numMaxElementos, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in Bubble Sort: %f seconds\n", timeTaken);
                break;
            case 3:
                printf("Sorting using Selection Sort...\n");
                selectionSort(array, numMaxElementos, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in Selection Sort: %f seconds\n", timeTaken);
                break;
            case 4:
                printf("Sorting using Shell Sort...\n");
                shellSort(array, numMaxElementos, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in Shell Sorte: %f seconds\n", timeTaken);
                break;
            case 5:
                printf("Sorting using Quick Sort...\n");
                quickSort(array, 0, numMaxElementos - 1, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in Quick Sorte: %f seconds\n", timeTaken);
                break;
            case 6:
                printf("Sorting using Heap Sort...\n");
                heapSort(array, numMaxElementos, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in Heap Sort: %f seconds\n", timeTaken);
                break;
            case 7:
                printf("Sorting using Merge Sort...\n");
                mergeSort(array, 0, numMaxElementos - 1, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in Merge Sort: %f seconds\n", timeTaken);
                break;
            case 8:
                printf("Sorting using Radix Sort...\n");
                radixSort(array, numMaxElementos, &timeTaken);
                printArray(array, numMaxElementos);
                printf("Time taken in radix Sort: %f seconds\n", timeTaken);
                break;
            case 0:
                printf("Quit...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

    printf("\n");
    }
}