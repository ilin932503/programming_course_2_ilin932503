#include <iostream>
#include <vector>
using namespace std;

struct Run {
    unsigned char value;
    int count;
};

vector<Run> packArray(const int* arr, int n) {
    vector<Run> compressed;
    if (n == 0) return compressed;

    int i = 0;
    while (i < n) {
        int current = arr[i];
        int j = i;
        while (j < n && arr[j] == current) {
            j++;
        }
        compressed.push_back({ static_cast<unsigned char>(current), j - i });
        i = j;
    }
    return compressed;
}

void unpackArray(const vector<Run>& runs, int* output) {
    int idx = 0;
    for (const Run& r : runs) {
        for (int i = 0; i < r.count; ++i) {
            output[idx++] = r.value;
        }
    }
}

int main() {
    // Массив ЗНАЧИТЕЛЬНО больше 1000 элементов
    const int N = 10000;

    // Создаём упорядоченный массив со значениями от 0 до 17
    int* original = new int[N];

    // Заполняем: много повторов каждого числа
    int idx = 0;
    for (int val = 0; val <= 17; val++) {
        int repeats = N / 18;  // примерно поровну для каждого значения
        if (val == 17) repeats += N % 18;  // остаток добавляем к последнему

        for (int i = 0; i < repeats; i++) {
            original[idx++] = val;
        }
    }

    // Упаковка
    vector<Run> packed = packArray(original, N);

    // Распаковка
    int* restored = new int[N];
    unpackArray(packed, restored);

    // Вывод сжатых данных (только "гармошку", не все 10000 чисел!)
    cout << "Сжатые данные (value : count):\n";
    for (const Run& r : packed) {
        cout << (int)r.value << " : " << r.count << "\n";
    }
    cout << endl;

    // Проверка корректности
    bool ok = true;
    for (int i = 0; i < N; i++) {
        if (original[i] != restored[i]) {
            ok = false;
            break;
        }
    }
    cout << "Проверка: " << (ok ? "OK" : "ERROR") << "\n";
    cout << "Исходный размер: " << N << " элементов (" << N * 4 << " байт)\n";
    cout << "Сжатый размер: " << packed.size() << " записей (" << packed.size() * 5 << " байт)\n";
    cout << "Экономи: " << (1 - (double)(packed.size() * 5) / (N * 4)) * 100 << "%\n";

    // Освобождение памяти
    delete[] original;
    delete[] restored;

    return 0;
}