#include <stdio.h>
#include <stdlib.h> // Para atoi

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: ./seu_programa text key operationType\n");
        return 1;
    }

    char *text = argv[1];
    char *key = argv[2];
    int operationType = atoi(argv[3]);
    

    printf("REsultado da criptografia: Askdjajdhajshdhad");

    return 0;
}