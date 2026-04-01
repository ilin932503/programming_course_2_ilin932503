#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вывода матрицы 
void PrintMatrix(ofstream& out, double** matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            out << fixed << setprecision(2) << matrix[i][j] << "\t";
        }
        out << endl;
    }
}

// Функция приведения матрицы к ступенчатому виду
int GaussJordan(double** matrix, int m, int n, double epsilon = 1e-9) {
    int lead = 0; // Ведущий столбец

    // Проходим по всем строкам
    for (int row = 0; row < m && lead < n; row++) {
        // Выбор ведущего элемента
        int sel = row;
        for (int i = row + 1; i < m; i++) {
            if (fabs(matrix[i][lead]) > fabs(matrix[sel][lead]))
                sel = i;
        }

        // Если весь столбец нулевой, переходим к следующему столбцу
        if (fabs(matrix[sel][lead]) < epsilon) {
            lead++;
            row--; 
            continue;
        }

        // Меняем местами текущую строку и строку с ведущим элементом
        if (sel != row) {
            for (int j = 0; j < n + 1; j++) {
                double temp = matrix[row][j];
                matrix[row][j] = matrix[sel][j];
                matrix[sel][j] = temp;
            }
        }

        // Делим текущую строку на ведущий элемент, чтобы сделать его равным 1
        double div = matrix[row][lead];
        for (int j = 0; j < n + 1; j++) {
            matrix[row][j] /= div;
        }

        // Обнуляем элементы в текущем столбце во всех остальных строках (выше и ниже)
        for (int i = 0; i < m; i++) {
            if (i != row) {
                double sub = matrix[i][lead];
                for (int j = 0; j < n + 1; j++) {
                    matrix[i][j] -= sub * matrix[row][j];
                }
            }
        }

        lead++; // Переходим к следующему ведущему столбцу
    }

    // Проверка на несовместность (строка вида 0 0 ... 0 | b, где b != 0)
    for (int i = 0; i < m; i++) {
        bool allZero = true;
        for (int j = 0; j < n; j++) {
            if (fabs(matrix[i][j]) > epsilon) {
                allZero = false;
                break;
            }
        }
        // Если коэффициенты нулевые, а свободный член нет
        if (allZero && fabs(matrix[i][n]) > epsilon) {
            return 0; // Нет решений
        }
    }

    // Подсчет ранга
    int rank = 0;
    for (int i = 0; i < m; i++) {
        bool zeroRow = true;
        for (int j = 0; j < n; j++) {
            if (fabs(matrix[i][j]) > epsilon) {
                zeroRow = false;
                break;
            }
        }
        if (!zeroRow) rank++;
    }

    if (rank < n) {
        return -1; // Бесконечно много решений 
    }

    return 1; // Единственное решение
}

int main() {

    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    if (!inFile.is_open()) {
        cout << "Error: Cannot open input.txt" << endl;
        return 1;
    }

    int m, n;
    if (!(inFile >> m >> n)) {
        cout << "Error: Invalid input format" << endl;
        return 1;
    }

    // Создание динамической матрицы
    double** matrix = new double* [m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new double[n + 1];
    }

    // Чтение данных
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n + 1; j++) {
            inFile >> matrix[i][j];
        }
    }
    inFile.close();

    // Вывод исходной матрицы
    outFile << "Исходная матрица:" << endl;
    PrintMatrix(outFile, matrix, m, n + 1);
    outFile << endl;

    // Метод Гаусса
    int result = GaussJordan(matrix, m, n);

    // Вывод преобразованной матрицы
    outFile << "Матрица после Гаусса:" << endl;
    PrintMatrix(outFile, matrix, m, n + 1);
    outFile << endl;

    // Результат
    if (result == 1) {
        outFile << "Результат: существует уникальное решение" << endl;

        double* solution = new double[n];
        for (int j = 0; j < n; j++) solution[j] = 0.0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (fabs(matrix[i][j] - 1.0) < 1e-5) {
                    bool isLead = true;
                    for (int k = 0; k < n; k++) {
                        if (k != j && fabs(matrix[i][k]) > 1e-5) {
                            isLead = false;
                            break;
                        }
                    }
                    if (isLead) {
                        solution[j] = matrix[i][n];
                        break;
                    }
                }
            }
        }

        outFile << "Решения: ";
        for (int j = 0; j < n; j++) {
            outFile << "x" << (j + 1) << "=" << fixed << setprecision(2) << solution[j];
            if (j < n - 1) outFile << "; ";
        }
        outFile << endl;

        delete[] solution;
    }
    else if (result == 0) {
        outFile << "Результат: нет решения" << endl;
    }
    else if (result == -1) {
        outFile << "Результат: БЕСКОНЕЧНОЕ количество решений." << endl;
    }

    outFile.close();

    cout << "Program completed. Check output.txt" << endl;

    // Освобождение памяти
    for (int i = 0; i < m; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}