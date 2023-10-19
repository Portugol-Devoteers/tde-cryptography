#include <stdio.h>
#include <stdlib.h>

//Funções para as Rotinas
void printMatriz(unsigned char M[4][4]) {
    printf("Matriz 4x4 resultante:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02X ", M[i][j]); // Imprime o valor hexadecimal do byte
        }
        printf("\n");
    }
}

//Funciona perfeitamente
void SBox (unsigned char M[4][4]) {

    //Sbox
    const unsigned char sBox[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}};

    // Copie a matriz original para a matriz temporária
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            unsigned char valor = M[i][j];
            M [i][j] = sBox[(valor >> 4) & 0x0F][valor & 0x0F];

        }
    }

}

//funciona perfeitamente
void ShiftRows(unsigned char M[4][4]) {
  //a linha 0 se mantem igual
  //Reorganizar a linha 1
  int a = M[1][0];
  for (int j = 1; j < 4; j++) {
    M[1][j-1] = M[1][j]; 
  }
  //Reorganizar a Linha 2
  M[1][3] = a;
  a = M[2][0];
  int b = M[2][1];
  M[2][0] = M[2][2];
  M[2][1] = M[2][3];
  M[2][2] = a;
  M[2][3] = b;
  //Reorganizar a Linha 3
  a = M[3][3];
  for (int j = 3; j > 0; j = j-1) {
    M[3][j] = M[3][j-1]; 
  }
  M[3][0] = a;
  
}

void MixColumns(unsigned char M[4][4]) {
  int matriz[4][4] = {
    {2, 3, 1, 1},
    {1, 2, 3, 1},
    {1, 1, 2, 3},
    {3, 1, 1, 2}
  };
  int temp[4][4];

  temp[0][0] = M[0][0]*matriz[0][0] ^ M[0][1]*matriz[1][0] ^ M[0][2]*matriz[2][0] ^ M[0][3]*matriz[3][0];
  temp[1][0] = M[1][0]*matriz[0][0] ^ M[1][1]*matriz[1][0] ^ M[1][2]*matriz[2][0] ^ M[1][3]*matriz[3][0];
  temp[2][0] = M[2][0]*matriz[0][0] ^ M[2][1]*matriz[1][0] ^ M[2][2]*matriz[2][0] ^ M[2][3]*matriz[3][0];
  temp[3][0] = M[3][0]*matriz[0][0] ^ M[3][1]*matriz[1][0] ^ M[3][2]*matriz[2][0] ^ M[3][3]*matriz[3][0];

  temp[0][01] = M[0][0]*matriz[0][01] ^ M[0][1]*matriz[1][01] ^ M[0][2]*matriz[2][01] ^ M[0][3]*matriz[3][01];
  temp[1][01] = M[1][0]*matriz[0][01] ^ M[1][1]*matriz[1][01] ^ M[1][2]*matriz[2][01] ^ M[1][3]*matriz[3][01];
  temp[2][01] = M[2][0]*matriz[0][01] ^ M[2][1]*matriz[1][01] ^ M[2][2]*matriz[2][01] ^ M[2][3]*matriz[3][01];
  temp[3][01] = M[3][0]*matriz[0][01] ^ M[3][1]*matriz[1][01] ^ M[3][2]*matriz[2][01] ^ M[3][3]*matriz[3][01];
  
  temp[0][02] = M[0][0]*matriz[0][02] ^ M[0][1]*matriz[1][02] ^ M[0][2]*matriz[2][02] ^ M[0][3]*matriz[3][02];
  temp[1][02] = M[1][0]*matriz[0][02] ^ M[1][1]*matriz[1][02] ^ M[1][2]*matriz[2][02] ^ M[1][3]*matriz[3][02];
  temp[2][02] = M[2][0]*matriz[0][02] ^ M[2][1]*matriz[1][02] ^ M[2][2]*matriz[2][02] ^ M[2][3]*matriz[3][02];
  temp[3][02] = M[3][0]*matriz[0][02] ^ M[3][1]*matriz[1][02] ^ M[3][2]*matriz[2][02] ^ M[3][3]*matriz[3][02];

  temp[0][03] = M[0][0]*matriz[0][03] ^ M[0][1]*matriz[1][03] ^ M[0][2]*matriz[2][03] ^ M[0][3]*matriz[3][03];
  temp[1][03] = M[1][0]*matriz[0][03] ^ M[1][1]*matriz[1][03] ^ M[1][2]*matriz[2][03] ^ M[1][3]*matriz[3][03];
  temp[2][03] = M[2][0]*matriz[0][03] ^ M[2][1]*matriz[1][03] ^ M[2][2]*matriz[2][03] ^ M[2][3]*matriz[3][03];
  temp[3][03] = M[3][0]*matriz[0][03] ^ M[3][1]*matriz[1][03] ^ M[3][2]*matriz[2][03] ^ M[3][3]*matriz[3][03];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        M[i][j] = temp[i][j];
    }
  } 
}


//funciona perfeitamente
void AddRoundKey (unsigned char M[4][4], unsigned char Key[4][4]) {

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      M[i][j] = M[i][j] ^ Key[j][i];
    }
  }  
}

//Funções para Cuspir a Key, funcional
//////////////////////
//////////////////////
//////////////////////
//////////////////////
//////////////////////
//////////////////////

void Rot(unsigned char matrix[4][4], unsigned char g[4]) {
    for (int i = 0; i < 3; i++) {
        // Copia os elementos da última linha da matriz no vetor g
        g[i] = matrix[i + 1][3];

    }
  g[3] = matrix[0][3];
}

void SBox2 (unsigned char g[4]) {

  //Sbox
  const unsigned char sBox[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}};


  for (int i = 0; i < 4; i++) {
    unsigned char valor = g[i];
      g [i] = sBox[(valor >> 4) & 0x0F][valor & 0x0F];   
  } 

}

void Rcon(int round, unsigned char g[4]) {
  unsigned int result = 0;

  // Use um switch para determinar o valor com base no round
  switch (round) {
    case 1:
      result = 0x01;
      break;
    case 2:
      result = 0x02;
      break;
    case 3:
      result = 0x04;
      break;
    case 4:
      result = 0x08;
      break;
    case 5:
      result = 0x10;
      break;
    case 6:
      result = 0x20;
      break;
    case 7:
      result = 0x40;
      break;
    case 8:
      result = 0x80;
      break;
    case 9:
      result = 0x1B;
      break;
    case 10:
      result = 0x36;
      break;

    default:
      // Valor padrão caso o round seja inválido
      result = 0x00000000;
    }


    // Realize a operação XOR com todos os elementos da matriz M

    g[0] = g[0]^result;



}

void fim(unsigned char matrix[4][4], unsigned char g[4]) {
  // Faz o XOR entre a primeira linha e o vetor g
  for (int j = 0; j < 4; j++) {
    matrix[j][0] ^= g[j];
  }

  // Faz o XOR com as linhas subsequentes
  for (int i = 1; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix[j][i] ^= matrix[j][i-1];
    }
  }
}

//funciona perfeitamente
void cuspirkey (unsigned char M[4][4], int round){


  unsigned char g[4];

  Rot (M, g);
  SBox2 (g);
  Rcon (round, g);
  fim (M, g);
  //printMatriz(M);

}


int main(int argc, char *argv[]) {
    char texto[10000];
    strcpy(texto, argv[1]);

    char chave[17];
    strcpy(chave, argv[2]);// A chave pode ter até 16 caracteres + 1 para o caractere nulo
    char RKey [4][4];

    // Leitura do texto
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            texto[i] = '\0';
        break;
        }
    }

    // Leitura da chave
    for (int i = 0; chave[i] != '\0'; i++) {
        if (chave[i] == '\n') {
            chave[i] = '\0';
        break;
        }
    }

    // Preencher a chave com caracteres vazios (espaços em branco) até 16 caracteres
    int chave_len = strlen(chave);
    for (int i = chave_len; i < 16; i++) {
        chave[i] = ' ';
    }
    chave[16] = '\0'; // Certifique-se de terminar a cadeia com nulo

    //Colocando a chave em uma key de round em formato hex
    int texto_index = 0;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {

        RKey[j][i] = (unsigned char)chave[texto_index];
        texto_index++;
      }
    } 
  
    //verificando quantas matrizes são necessárias
    div_t resultado = div(strlen(texto), 16);

    int q_M = resultado.quot;
    int resto = resultado.rem;

    if (resto != 0){
        q_M = q_M + 1;
    }


    char matriz[q_M][4][4];

    //Colocando o texto digitado em matrizes de matrizes
    texto_index = 0;
    for (int z = 0; z < q_M; z++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {

                matriz[z][i][j] = (unsigned char)texto[texto_index];
                texto_index++;
            }
        }
    }

    
    
   // 
  
    // Rodada 0, adicionar a chave de rodada sem expanção 
    for (int z = 0; z < q_M; z++) {

      //está adicionando a key correta
      AddRoundKey(matriz[z], RKey);

      //printMatriz(RKey);

    }
    //9 rodadas comuns, com o ciclo de encriptação completo
  for (int contador = 1; contador < 10; contador++) {

    cuspirkey (RKey, contador);
    //printMatriz(RKey);

    for (int z = 0; z < q_M; z++) {

      SBox(matriz[z]);      
      ShiftRows(matriz[z]);
      MixColumns(matriz[z]);
      AddRoundKey(matriz[z], RKey);
      
      //printMatriz(matriz[z]);

    }  
  }

  
  //Round final de encriptador
  int contador = 10;
  cuspirkey (RKey, contador);
  //printMatriz(RKey);
  for (int z = 0; z < q_M; z++) {

    SBox(matriz[z]);
    ShiftRows(matriz[z]);
    AddRoundKey(matriz[z], RKey);
    
    //printMatriz(matriz[z]);

  }

  //printa para teste de leitura, funcionando perfeitamente
  // printf("Matriz ?x4x4:\n");
  for (int z = 0; z < q_M; z++) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          printf("%02X ", (unsigned char)matriz[z][i][j]); // Imprime o valor hexadecimal do byte
      }
    }
  }

    return 0;
}
