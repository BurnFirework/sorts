#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void ascending(int n, int *arr) {
    for(int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

void descending(int n, int *arr) {
    for(int i = n; i > 0; i--) {
        arr[n - i] = i;
    }
}

void random_array(int n, int *arr) {
    for(int i = 0; i < n; i++) {
        arr[i] = rand() * rand();
    }
}

void generator(int n, int *arr, int par) {
    if(par == 1) {
        ascending(n, arr);
    }
    else if(par == 2) {
        descending(n, arr);
    }
    else {
        random_array(n, arr);
    }
}

//Метод простого выбора
void simple_choice (int n, int *arr, int *count_comp, int *count_move) {
    int min, tmp;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            (*count_comp) += 1;
            if (arr[j] < arr[min]) {//ищем индекс минимального элемента
                min = j;
            }
        }

        tmp = arr[i]; //меняем значения местами
        arr[i] = arr[min];
        arr[min] = tmp;
        (*count_move) += 1;
    }
}

//быстрая сортировка
void quick_sort(int n, int *arr, int *count_comp, int *count_move) {
    int right = n - 1, left = 0, centr = arr[n / 2], tmp = 0;
    while(left <= right) {
        while(arr[left] < centr) { //двигаем левую границу
            left++;
            (*count_comp) += 1;
        }
        while(arr[right] > centr) { //двигаем правую границу
            right--;
            (*count_comp) += 1;
        }
        if(left <= right) { //меняем местами левый и правый элементы
            tmp = arr[right];
            arr[right] = arr[left];
            arr[left] = tmp;
            left++;
            right--;
            (*count_move) += 1;
        }
    }
    //выполняем сортировку правой и левой части
    if(right > 0) { 
        quick_sort(right + 1, arr, count_comp, count_move);
    }
    if (n - 1 > left) {
        quick_sort(n - left, arr + left, count_comp, count_move);
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0) {
            printf("Данная программа генерирует разные массивы чисел \
            и выполняет на них сравнение эффективности быстрой сортировки и метода простого выбора. \
            После выполнения программы в консоль выводится количество операций, выполненное указанными сортировками.");
            return 0;
        }
    }
    int count_comp = 0, count_move = 0;
    
    //перебираем размеры массивов: 10, 100, 1000, 10000
    for (int n = 10; n <= 10000; n *= 10) {
        int comp1 = 0, comp2 = 0, move1 = 0, move2 = 0;
        
        //перебираем тип генерации массива
        for (int type = 1; type <= 4; type++) {
            //создаём два копии сгенерированного массива для сортировки
            int *arr = malloc(n * sizeof(int));
            int *arr2 = malloc(n * sizeof(int));
            generator(n, arr, type);
            memcpy(arr2, arr, n * sizeof(int));
            count_move = 0, count_comp = 0;
            
            //выполняем сортировку методом простого выбора, считаем операции
            simple_choice(n, arr, &count_comp, &count_move);
            comp1 += count_comp;
            move1 += count_move;
            printf("Simple choice: size %d, type %d, count_comp %d, count_move %d\n", n, type, count_comp, count_move);
            count_move = 0, count_comp = 0;
            
            //выполняем быструю сортировку, считаем операции
            quick_sort(n, arr2, &count_comp, &count_move);
            comp2 += count_comp;
            move2 += count_move;
            printf("Quick sort: size %d, type %d, count_comp %d, count_move %d\n", n, type, count_comp, count_move);
            
            free(arr);
            free(arr2);
        }
        printf("\n");
        printf("Simple choice: size %d, aver_comp %d, aver_move %d\n", n, comp1 / 4, move1 / 4);
        printf("Quick sort: size %d, aver_comp %d, aver_move %d\n", n, comp2 / 4, move2 / 4);
        printf("\n");
    }
    return 0;
}
