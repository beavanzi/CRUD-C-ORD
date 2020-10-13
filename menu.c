#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "remove.h"
#include "search.h"

void menu(int x, char *str, int tamanho_chave) {  // x é o número que está atribuído em controle, str é o buffer, tamanho_registro é o strlen da buffer2, head é a cabeça da LED do começo do arquivo
    char *num_reg;
    short *tam_reg;
    int i = 0;
    int achou;
    int chave = 0;  // número da frente de cada registro
    int posicao_de_seek = 0;
    char chave_da_operacao[TAM_MAX_REG];  // string pra ser usada na strtok e armazenar apenas o número do registro
                                          // char buffer2[TAM_MAX_REG];  //string que será usada para armazenar os registros de busca

    for (i = 2; i < tamanho_chave; i++) {  // começa em dois para pular a letra de comando e o espaço
                                           //  buffer2[i - 2] = str[i];
        chave_da_operacao[i - 2] = str[i];
    }
    chave_da_operacao[i - 2] = '\0';
    chave = atoi(chave_da_operacao);

    switch (x) {
        case 1:  //operação de busca
            achou = busca(chave, &posicao_de_seek, tam_reg);
            if (!achou) {
                printf("\n\nBusca pelo registro de chave '%d'\n", chave);
                printf("Erro: registro nao encontrado!");
            }
            break;
        case 2:                                                  //operação de remoção
            if (busca(chave, &posicao_de_seek, tam_reg) == 1) {  //verificando se o registro existe, se existir então procedemos com a remoção
                remocao(posicao_de_seek);
                printf("\n\nRemocao do registro de chave '%d'\n", chave);
                printf("Registro removido! (%d bytes)\n", tam_reg);
                printf("Posicao: offset = %d bytes\n", posicao_de_seek);
            } else {
                printf("\n\nRemocao do registro de chave '%d'\n", chave);
                printf("Registro nao encontrado!\n");
            }
            break;
        default:
            printf("Erro");
            break;
    }
}
