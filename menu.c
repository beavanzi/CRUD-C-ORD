#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "remove.h"
#include "search.h"

void menu(int x, char *str, int tamanho_registro) {  // x é o número que está atribuído em controle, str é o buffer, tamanho_registro é o strlen da buffer2, head é a cabeça da LED do começo do arquivo
    char *num_reg;
    int i = 0;
    short tamanho_reg = tamanho_registro;
    int chave = 0;  // número da frente de cada registro
    int posicao_de_seek = 0;
    char aux[TAM_MAX_REG];  // string pra ser usada na strtok e armazenar apenas o número do registro
    char buffer[TAM_MAX_REG];
    char buffer2[TAM_MAX_REG];  //string que será usada para armazenar os registros de busca

    for (i = 2; i < tamanho_reg; i++) {  // começa em dois para pular a letra de comando e o espaço
        buffer2[i - 2] = str[i];
        aux[i - 2] = str[i];
    }
    aux[i - 2] = '\0';
    chave = atoi(aux);

    switch (x) {
        case 1:  //operação de busca
            busca(chave, &posicao_de_seek);
            break;
        case 2:                                         //operação de remoção
            if (busca(chave, &posicao_de_seek) == 1) {  //verificando se o registro existe, se existir então procedemos com a remoção
                remocao(posicao_de_seek);
                printf("Remocao do registro de chave %d\n", chave);
                printf("Registro removido! (%d vytes)\n", tamanho_reg);
                printf("Posicao: offset = %d bytes\n", posicao_de_seek);
            } else {
                printf("Remocao do registro de chave %d\n", chave);
                printf("Registro nao encontrado!");
            }

            break;
        default:
            printf("Erro");
            break;
    }
}
