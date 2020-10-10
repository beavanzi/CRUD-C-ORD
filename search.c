#include <stdio.h>
#include <stdlib.h>

#include "main.h"

//A função busca fará a leitura da chave dos registros, retornará 0 se não encontrar o registro, 1 se encontrar
int busca(int chave, char *buffer2, short *tamanho_registro, int *posicao_de_seek) {
    int achou = 0;
    short tam_reg;
    int key;  //será utilizada na conversão da aux para inteiro
    char *aux;
    char buffer[TAM_MAX_REG];
    int posicao_de_leitura;

    rewind(arq);              // volta o ponteiro de L/E no byte 0 do arquivo, pra começar a ler dnv
    fseek(arq, 4, SEEK_SET);  // movendo o ponteiro de L/E em 4 bytes a partir do começo do arquivo p/ pular a LED (não queremos ler ela)
    while (achou == 0) {
        posicao_de_leitura = ftell(arq);            //mostra em qual byte (do arquivo) está sendo realizada a leitura
        fread(&tam_reg, sizeof(short), 1, arq);     // le o tamanho do registro de dentro do arquivo e armazena o valor na tam_reg
        fread(buffer, sizeof(char), tam_reg, arq);  // le do arquivo arq "tamanho" numero de elementos, e armazena na string buffer

        aux = strtok(buffer, "|");  // pega apenas o número do registro de cada registro no buffer, pois vai ler até chegar no |
        key = atoi(aux);            // converte o valor de char da aux para int e armazena em key

        if (chave == key) {
            achou = 1;
            printf("Busca pelo registro de chave %d", key);
            tam_reg = tam_reg + 4;  //+4 pois o fseek não está registrando os 4 bytes do rrn no tamanho do registro
            printf("%s %d bytes", buffer, tam_reg);
            *posicao_de_seek = posicao_de_leitura;  //posicao_de_seek recebe a posicao do registro buscado
        }
    }

    return achou;
}