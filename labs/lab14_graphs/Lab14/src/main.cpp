#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// УПРАЖНЕНИЕ 1

void Exercise1(const string& inFile, const string& outFile) {
    ifstream fin(inFile);
    if (!fin.is_open()) { cerr << "Ошибка: не удалось открыть " << inFile << "\n"; return; }

    int n, m;
    fin >> n >> m;

    // Выделение памяти под матрицу
    vector<vector<int>> M(n, vector<int>(n, 0));

    for (int k = 0; k < m; ++k) {
        int u, v;
        fin >> u >> v;
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            M[u - 1][v - 1] = 1;
            M[v - 1][u - 1] = 1; // Неориентированный граф
        }
    }
    fin.close();

    ofstream fout(outFile);
    if (!fout.is_open()) { cerr << "Ошибка: не удалось создать " << outFile << "\n"; return; }

    fout << n << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout << M[i][j] << " ";
        }
        fout << "\n";
    }
    fout.close();
    cout << " Матрица смежности сохранена в " << outFile << "\n";
}

// УПРАЖНЕНИЕ 2

void Exercise2(const string& inFile, const string& outFile) {
    ifstream fin(inFile);
    if (!fin.is_open()) { cerr << "Ошибка: не удалось открыть " << inFile << "\n"; return; }

    int n;
    fin >> n;

    // Чтение матрицы
    vector<vector<int>> M(n, vector<int>(n));
    int realEdges = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> M[i][j];
            if (i < j && M[i][j] == 1) realEdges++; 
        }
    }
    fin.close();
    int m = realEdges;

   
    vector<int> L(n, 0);
    vector<int> S(n, 0);
    vector<int> D(2 * m, 0);
    vector<int> U(n); // Временный указатель для заполнения D

    // L
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (M[i][j] == 1) L[i]++;
        }
    }

    // S
    S[0] = 0;
    for (int j = 1; j < n; ++j) {
        S[j] = S[j - 1] + L[j - 1];
    }

    for (int j = 0; j < n; ++j) U[j] = S[j];

    // D
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (M[i][j] == 1) {
                D[U[i]] = j;
                U[i]++;
            }
        }
    }

    // Запись результата 
    ofstream fout(outFile);
    if (!fout.is_open()) { cerr << "Ошибка: не удалось создать " << outFile << "\n"; return; }

    fout << n << " " << m << "\n";
    fout << "S:"; for (int x : S) fout << " " << x; fout << "\n";
    fout << "L:"; for (int x : L) fout << " " << x; fout << "\n";
    fout << "D:"; for (int x : D) fout << " " << x; fout << "\n";
    fout.close();
    cout << " Массивы L, S, D сохранены в " << outFile << "\n";
}


// УПРАЖНЕНИЕ 3

void Exercise3(const string& inFile, const string& outFile) {
    ifstream fin(inFile);
    if (!fin.is_open()) { cerr << "Ошибка: не удалось открыть " << inFile << "\n"; return; }

    int n, m;
    fin >> n >> m;

    // Пропускаем S:, L:, D:
    string temp;
    fin >> temp;
    vector<int> S(n);
    for (int i = 0; i < n; ++i) fin >> S[i];

    fin >> temp;
    vector<int> L(n);
    for (int i = 0; i < n; ++i) fin >> L[i];

    fin >> temp;
    vector<int> D(2 * m);
    for (int i = 0; i < 2 * m; ++i) fin >> D[i];
    fin.close();

    // Восстановление ребер по алгоритму обхода S и L
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int k = S[i]; k < S[i] + L[i]; ++k) {
            int v = D[k];
            if (i < v) { // Фильтр дубликатов
                edges.push_back({ i, v });
            }
        }
    }

    // Запись результата 
    ofstream fout(outFile);
    if (!fout.is_open()) { cerr << "Ошибка: не удалось создать " << outFile << "\n"; return; }

    fout << n << " " << edges.size() << "\n";
    for (const auto& e : edges) {
        fout << (e.first + 1) << " " << (e.second + 1) << "\n";
    }
    fout.close();
    cout << " Последовательность ребер сохранена в " << outFile << "\n";
}

int main() {

    Exercise1("input1.txt", "output1.txt");
    Exercise2("output1.txt", "output2.txt");
    Exercise3("output2.txt", "output3.txt");

    return 0;
}