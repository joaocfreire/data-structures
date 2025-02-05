#include <stdio.h>
#include <stdlib.h>

/* ------------------------------- LISTA 6 ---------------------------------- */

/*
 * 1) Construa um arquivo .txt para armazenar duas matrizes quadradas de ordem n.
 * a) Faça um programa que leia esse arquivo e execute o produto de A por B.
 *    Armazene o resultado C=A.B em um novo arquivo.txt.
 * b) Transforme as matrizes em arquivos binários e refaça agora o produto multiplicando
 *    antes as diagonais principais de A e B por valores inteiros k1 e k2 respectivamente.
 *    As novas diagonais obtidas devem ser sobreescritas em A e B.
 */

#define ORDER 3

void matrix_multiplication_1(char* filename1, char* filename2) {
    FILE *file = fopen(filename1, "r");

    if (file != NULL) {
        int matrix_a[ORDER][ORDER];
        int matrix_b[ORDER][ORDER];
        int elem, i = 0, j = 0, k;

        // Leitura da matriz A
        while (i < ORDER) {
            fscanf(file, "%d", &elem);
            matrix_a[i][j] = elem;
            j++;
            if (j == ORDER) {
                j = 0;
                i++;
            }
        }

        i = 0;

        // Leitura da matriz B
        while (!feof(file)) {
            fscanf(file, "%d", &elem);
            matrix_b[i][j] = elem;
            j++;
            if (j == ORDER) {
                j = 0;
                i++;
            }
        }

        fclose(file); // Fecha o arquivo após a leitura

        // Inicializa a matriz C com zeros
        int matrix_c[ORDER][ORDER];
        for (i = 0; i < ORDER; i++) {
            for (j = 0; j < ORDER; j++) {
                matrix_c[i][j] = 0;
            }
        }

        // Multiplica A por B e armazena em C
        for (i = 0; i < ORDER; i++) {
            for (j = 0; j < ORDER; j++) {
                for (k = 0; k < ORDER; k++) {
                    matrix_c[i][j] = matrix_c[i][j] + matrix_a[i][k] * matrix_b[k][j];
                }
            }
        }

        // Imprime a matriz C
        printf("Matriz C:\n");
        for (i = 0; i < ORDER; i++) {
            for (j = 0; j < ORDER; j++) {
                printf("%d ", matrix_c[i][j]);
            }
            printf("\n");
        }

        // Armazena o resultado em outro arquivo texto
        file = fopen(filename2, "w");
        for (i = 0; i < ORDER; i++) {
            for (j = 0; j < ORDER; j++) {
                fprintf(file, "%d\n", matrix_c[i][j]);
            }
        }

        fclose(file); // Fecha o arquivo após a escrita
    }
}

void matrix_multiplication_2(char* filename1, char* filename2, char* filename3, int k1, int k2) {
    FILE *in = fopen(filename1, "r");
    FILE *out = fopen(filename2, "wb+");

    // Verificação de erros
    if (in == NULL || out == NULL)
        exit(1);

    // Preenche o arquivo binário com os mesmos dados do arquivo texto
    int elem;
    while (fscanf(in, "%d", &elem) == 1)
        fwrite(&elem, sizeof(int), 1, out);

    fclose(in); // Fecha o arquivo texto de entrada após fazer a leitura

    fseek(out, 0, SEEK_SET); // Posiciona o cursor no início do arquivo binário

    int i = 0, j = 0, k;
    int matrix_a[ORDER][ORDER];
    int matrix_b[ORDER][ORDER];

    // Leitura da matriz A e multiplicação da diagonal por k1
    while (i < ORDER) {
        fread(&elem, sizeof(int), 1, out);
        if (i == j)
            elem *= k1;
        matrix_a[i][j] = elem;
        j++;
        if (j == ORDER) {
            j = 0;
            i++;
        }
    }

    i = 0;

    // Leitura da matriz B e multiplicação da diagonal por k2
    while (fread(&elem, sizeof(int), 1, out)) {
        if (i == j)
            elem *= k2;
        matrix_b[i][j] = elem;
        j++;
        if (j == ORDER) {
            j = 0;
            i++;
        }
    }

    fseek(out, 0, SEEK_SET); // Posiciona o cursor no início do arquivo binário

    // Atualização da matriz A no arquivo
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            fwrite(&matrix_a[i][j], sizeof(int), 1, out);
        }
    }

    // Atualização da matriz B no arquivo
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            fwrite(&matrix_b[i][j], sizeof(int), 1, out);
        }
    }

    fclose(out); // Fecha o arquivo binário após a leitura e atualização

    // Inicializa a matriz C com zeros
    int matrix_c[ORDER][ORDER];
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            matrix_c[i][j] = 0;
        }
    }

    // Multiplica A por B e armazena em C
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            for (k = 0; k < ORDER; k++) {
                matrix_c[i][j] = matrix_c[i][j] + matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }

    // Imprime a matriz C
    printf("Matriz C:\n");
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            printf("%d ", matrix_c[i][j]);
        }
        printf("\n");
    }

    // Armazena o resultado em outro arquivo binário
    out = fopen(filename3, "wb+");

    if (out != NULL) {
        for (i = 0; i < ORDER; i++) {
            for (j = 0; j < ORDER; j++) {
                fwrite(&matrix_c[i][j], sizeof(int), 1, out);
            }
        }
    }
    
    fclose(out); // Fecha o novo arquivo binário após a escrita

}

int main() {
    char *filename1, *filename2, *filename3;

    filename1 = "../src/files/matrix.txt";
    filename2= "../src/files/matrix_c.txt";
    matrix_multiplication_1(filename1, filename2);

    int k1, k2;
    printf("\nDigite dois valores k1 e k2:");
    scanf("%d %d", &k1, &k2);
    printf("\n");

    filename1 = "../src/files/matrix.txt";
    filename2 = "../src/files/matrix.bin";
    filename3 = "../src/files/matrix_c.bin";
    matrix_multiplication_2(filename1, filename2, filename3, k1, k2);

    return 0;
}
