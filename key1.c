#include <stdio.h>
#include <string.h>

void chaveParaMatriz(char chave[], unsigned char M[4][4]) {
    int i, j, k = 0;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            M[j][i] = (unsigned char)chave[k];
            k++;
        }
    }
}

int main() {
    char chave[17]; // Uma chave de 16 caracteres + o caractere nulo '\0'
    unsigned char M[4][4];
    
    printf("Digite uma chave: ");
    scanf("%16s", chave);
    printf("%s\n", chave);
    
    int len = strlen(chave);
    
    if (len < 16) {
        // Preencha o restante dos caracteres com espaços em branco
        for (int i = len; i < 16; i++) {
            chave[i] = ' ';
        }
    } else if (len > 16) {
        printf("A chave digitada tem mais de 16 caracteres e é maior do que o permitido.\n");
        return 1; // Saída com erro
    }
    
    chaveParaMatriz(chave, M);
    
    printf("Matriz 4x4 resultante:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02X ", M[j][i]); // Imprime o valor hexadecimal do byte
        }
        printf("\n");
    }

    // Agora, imprima os dois dígitos de M[0][0] separadamente
    unsigned char valor = M[0][0];
    printf("Dígitos de M[0][0]: %02X %02X\n", (valor >> 4) & 0x0F, valor & 0x0F);

    //printar a key 1
    for (int j = 0; j < 4; j++) {
        printf("%02X ", M[j][0]); // Imprime o valor hexadecimal do byte
    }

    return 0; // Saída com sucesso
}
