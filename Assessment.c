#include <stdio.h>
#include <stdlib.h>

#define max_size 100

void transpose_matrix(int matrix[max_size][max_size], int m, int n) {
    int transpose[max_size][max_size];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }

    FILE *out = fopen("transpose.txt", "w");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(out, "%d ", transpose[i][j]);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}

int main() {
    int matrix[max_size][max_size];
    int m, n;
    FILE *in = fopen("matrix.txt", "r");
    fscanf(in, "%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
        {
            fscanf(in, "%d", &matrix[i][j]);
        }
    }
    fclose(in);
    transpose_matrix(matrix, m, n);
    printf("transpose of matrix in 'transpose.txt'\n");
    return 0;
}
