/*Coleta de livros.txt e alocando em dados.dat, colocando o tamanho na frente
  de cada registro, salvando tudo em binário.*/

#include "main.h"

#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "read_record.h"
#include "remove.h"
#include "search.h"

int main(int argc, char **argv) {
    //VARIAVEIS PARA A IMPORTAÇÃO
    FILE *aux;  //para receber e ler o arquivo livros.txt
    short tam_reg = 0;
    int head = -1;  //cabeçalho
    int num_reg = 0;
    char buffer[TAM_MAX_REG];

    //VARIAVEIS PARA AS OPERACOES
    FILE *aux2;                 //receberá o arquivo dados.dat para leitura
    FILE *aux3;                 //receberá o arquivo operacoes.txt para leitura
    char buffer2[TAM_MAX_REG];  //será usado para armazenar os registros de operacoes.txt
    int controle;               //variável que receberá o número do caso para cada operação

    //Para verificar a abertura do programa:
    if (argc < 3) {
        fprintf(stderr, "Numero incorreto de argumentos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-i") == 0) {  //acessando a funcionalidade de implementação

        arquivo_dat = fopen("dados.dat", "wb");  //abertura e criação do arquivo para escrever os livros com seu tamanho de registro
        aux = fopen(argv[2], "r");               //abertura do arquivo livros.txt para coletar os registros

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);

        if (arquivo_dat == NULL) {
            printf("\nErro na abertura do arquivo -- programa finalizado.\n");
            system("pause");
            exit(1);
        }

        tam_reg = leia_registro(aux, buffer, TAM_MAX_REG);  //faz a leitura do registro de livros.txt, retornando seu tamanho em tam_reg e o registro em buffer

        fwrite(&head, sizeof(int), 1, arquivo_dat);  //escreve o cabeçalho de dados.dat com -1 na LED de espaços vazios

        while (tam_reg > 0) {
            fwrite(&tam_reg, sizeof(short), 1, arquivo_dat);     //escreve o tamanho do registro a ser inserido
            fwrite(buffer, sizeof(char), tam_reg, arquivo_dat);  //escreve o registro inserido

            tam_reg = leia_registro(aux, buffer, TAM_MAX_REG);
            num_reg++;  //conta quantos registros foram coletados
        }

        if (num_reg > 0) {
            printf("Operacao concluida.\nQuantidade de registros coletados e inseridos em dados.dat: %d\n", num_reg);
        } else {
            printf("Erro na operação.\n");
        }

        fclose(aux);          //fecha o arquivo livros.txt
        fclose(arquivo_dat);  //fecha o arquivo dados.dat
    } else if (strcmp(argv[1], "-e") == 0) {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);

        if ((arquivo_dat = fopen("dados.dat", "rb")) == NULL) {
            printf("Arquivo dados.dat não existe, programa finalizado.\n");
            system("pause");
            exit(1);
        }

        aux3 = fopen("operacoes.txt", "r");

        tam_reg = leia_registro(aux3, buffer2, TAM_MAX_REG);  //armazena o tamanho do primeiro registro de operacoes.txt
        while (tam_reg > 0) {
            switch (buffer2[0]) {
                case BUSCA:
                    menu(1, buffer2, tam_reg);
                    break;
                case REMOCAO:
                    controle = 2;
                    break;
                case INSERCAO:
                    controle = 3;
                    break;
                default:
                    printf("tamanho registro: %d bytes\n", tam_reg);
                    controle = 0;
                    break;
            }
            tam_reg = leia_registro(aux3, buffer2, TAM_MAX_REG);
        }
    } else {
        fprintf(stderr, "Opcao \"%s\" nao suportada!\n", argv[1]);
    }

    return 0;
}