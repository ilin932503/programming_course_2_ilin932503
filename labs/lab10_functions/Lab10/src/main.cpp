#include <iostream>
using namespace std;

// Структура для хранения одной складки гармошки
struct Run {
    unsigned char value;
    int count;
};

// А. Функция УПАКОВКИ

Run* packArray(const int* arr, int n, int* outSize) {
    if (n == 0) {
        *outSize = 0;
        return nullptr;
    }

    // Максимум 18 записей (значения от 0 до 17)
    Run* temp = new Run[18];
    int count = 0;

    int i = 0;
    while (i < n) {
        int current = arr[i];
        int j = i;
        while (j < n && arr[j] == current) {
            j++;
        }
        temp[count].value = static_cast<unsigned char>(current);
        temp[count].count = j - i;
        count++;
        i = j;
    }

    // Выделяем точный размер результата
    Run* result = new Run[count];
    for (int k = 0; k < count; k++) {
        result[k] = temp[k];
    }

    delete[] temp;          // освобождаем временный буфер
    *outSize = count;       // передаём количество записей
    return result;
}

// Б. Функция РАСПАКОВКИ
void unpackArray(const Run* runs, int runCount, int* output) {
    int idx = 0;
    for (int i = 0; i < runCount; i++) {
        for (int j = 0; j < runs[i].count; j++) {
            output[idx++] = runs[i].value;
        }
    }
}

int main() 
{
    const int N = 2000;

    // большой упорядоченный массив [0..17]
    int* original = new int[N];
    int pos = 0;
    for (int val = 0; val <= 17; val++) {
        int repeats = N / 18;
        if (val == 17) repeats += N % 18;
        for (int i = 0; i < repeats; i++) {
            original[pos++] = val;
        }
    }

    // УПАКОВКА 
    int compressedSize;
    Run* compressed = packArray(original, N, &compressedSize);

    // РАСПАКОВКА 
    int* restored = new int[N];
    unpackArray(compressed, compressedSize, restored);

    // ВЫВОД РЕЗУЛЬТАТА 
    cout << "Сжато в " << compressedSize << " записей:\n";
    for (int i = 0; i < compressedSize; i++) {
        cout << (int)compressed[i].value << ":" << compressed[i].count << " ";
    }
    cout << "\n\n";

    // ВЫВОД ИНФОРМАЦИИ О ПАМЯТИ
    size_t originalMemory = N * sizeof(int);
    size_t compressedMemory = compressedSize * sizeof(Run);


    cout << "Память до сжатия: " << originalMemory << " байт\n";
    cout << "Память после сжатия: " << compressedMemory << " байт\n";


    // ОСВОБОЖДЕНИЕ ПАМЯТИ
    delete[] original;
    delete[] restored;
    delete[] compressed;

    return 0;
}