#include <iostream>
using namespace std;

int main() {
    const int SIZE = 10;

    //Упражнение 3.1: 4 способа заполнения массива квадратами индексов

    // Способ 1: статический массив + индексная адресация
    int arr1[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr1[i] = i * i;
    }
    for (int i = 0; i < SIZE; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    // Способ 2: статический массив + косвенная адресация
    int arr2[SIZE];
    int* p2 = arr2;
    for (int i = 0; i < SIZE; i++) {
        *(p2 + i) = i * i;
    }
    for (int i = 0; i < SIZE; i++) {
        cout << *(p2 + i) << " ";
    }
    cout << endl;

    // Способ 3: динамический массив + индексная адресация
    int* arr3 = new int[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr3[i] = i * i;
    }
    for (int i = 0; i < SIZE; i++) {
        cout << arr3[i] << " ";
    }
    cout << endl;
    delete[] arr3;

    // Способ 4: динамический массив + косвенная адресация
    int* arr4 = new int[SIZE];
    int* p4 = arr4;
    for (int i = 0; i < SIZE; i++) {
        *(p4 + i) = i * i;
    }
    for (int i = 0; i < SIZE; i++) {
        cout << *(p4 + i) << " ";
    }
    cout << endl;
    delete[] arr4;

    // 3.2
    int size1 = 5, size2 = 7;
    int* a = new int[size1] {1, 3, 5, 7, 9};
    int* b = new int[size2] {2, 4, 6, 8, 10, 12, 14};
    int* result = new int[size1 + size2];

    int i = 0, j = 0, k = 0;

    // Основной цикл 
    while (i < size1 && j < size2) {
        if (a[i] <= b[j]) {
            result[k++] = a[i++];
        }
        else {
            result[k++] = b[j++];
        }
    }

    // Остаток первого массива 
    int* pa = a + i;  
    while (i < size1) {
        result[k++] = *pa; 
        pa++;
        i++;
    }

    // Остаток второго массива 
    int* pb = b + j;  
    while (j < size2) {
        result[k++] = *pb; 
        j++;
    }

    // Вывод 
    for (int idx = 0; idx < size1 + size2; idx++) {
        cout << result[idx] << " ";
    }
    cout << endl;

    delete[] a;
    delete[] b;
    delete[] result;

    // Упражнение 4
    struct Node {
        int data;
        Node* prev;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 1; i <= SIZE; i++) {
        Node* newNode = new Node{ i, tail, nullptr };
        if (head == nullptr) {
            head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}