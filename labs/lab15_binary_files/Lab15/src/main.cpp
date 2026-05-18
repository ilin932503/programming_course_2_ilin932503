#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cmath>

void color_filter() {
    FILE *fin = fopen("input.bmp", "rb");
    if (!fin) {
        printf("Error: Cannot open input.bmp\n");
        return;
    }
    FILE *fout = fopen("output.bmp", "wb"); 
    if (!fout) {
        printf("Error: Cannot create output.bmp\n");
        fclose(fin); return;
    }

    unsigned char header[54];
    if (fread(header, sizeof(unsigned char), 54, fin) != 54) {
        printf("Error: Invalid BMP file.\n");
        fclose(fin); fclose(fout); return;
    }

    int width  = *(int*)&header[18];
    int height = *(int*)&header[22];
    int abs_height = std::abs(height);

    short bitCount = *(short*)&header[28];
    if (bitCount != 24) {
        printf("Error: Only 24-bit BMP supported.\n");
        fclose(fin); fclose(fout); return;
    }

    fwrite(header, sizeof(unsigned char), 54, fout);

    int x1, y1, x2, y2;
    float coeff_R, coeff_G, coeff_B;
    printf("Image size: %d x %d\n", width, abs_height);
    printf("Enter rectangle coordinates (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    printf("Enter RGB coefficients (R G B): ");
    scanf("%f %f %f", &coeff_R, &coeff_G, &coeff_B);

    // Ограничиваем координаты размерами изображения
    if (x1 < 0) x1 = 0; if (y1 < 0) y1 = 0;
    if (x2 >= width) x2 = width - 1; if (y2 >= abs_height) y2 = abs_height - 1;
    if (x1 > x2 || y1 > y2) {
        printf("Warning: Invalid rectangle region. File copied without changes.\n");
    }

    int padding = (4 - (width * 3) % 4) % 4;
    int row_size = width * 3 + padding;
    unsigned char *row = new unsigned char[row_size];

    for (int y = 0; y < abs_height; y++) {
        fread(row, sizeof(unsigned char), row_size, fin);

        // BMP хранит пиксели снизу вверх
        int actual_y = (height > 0) ? (abs_height - 1 - y) : y;
        // Проверка попадания строки в прямоугольник 
        if (actual_y >= y1 && actual_y <= y2) {
            for (int x = 0; x < width; x++) {
                if (x >= x1 && x <= x2) {
                    int b_idx = x * 3;
                    int g_idx = x * 3 + 1;
                    int r_idx = x * 3 + 2;

                    float new_b = row[b_idx] * coeff_B;
                    float new_g = row[g_idx] * coeff_G;
                    float new_r = row[r_idx] * coeff_R;

                    // Ограничиваем диапазон 0..255
                    row[b_idx] = (new_b < 0) ? 0 : ((new_b > 255) ? 255 : (unsigned char)new_b);
                    row[g_idx] = (new_g < 0) ? 0 : ((new_g > 255) ? 255 : (unsigned char)new_g);
                    row[r_idx] = (new_r < 0) ? 0 : ((new_r > 255) ? 255 : (unsigned char)new_r);
                }
            }
        }
        fwrite(row, sizeof(unsigned char), row_size, fout);
    }

    // Копируем остаток файла
    int c;
    while ((c = fgetc(fin)) != EOF) {
        fputc(c, fout);
    }

    delete[] row;
    fclose(fin); fclose(fout);
    printf("Result saved to output.bmp\n");
}

int main() {
    color_filter();
    return 0;
}