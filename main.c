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
    LEDHead = -1;

    //VARIAVEIS PARA A IMPORTAÇÃO
    FILE *flivros;  //para receber e ler o arquivo livros.txt
    short tam_reg = 0;
    int num_reg = 0;
    char buffer_livros[TAM_MAX_REG];

    //VARIAVEIS PARA AS OPERACOES
    FILE *foperacoes;                    //receberá o arquivo operacoes.txt para leitura
    char buffer_operacoes[TAM_MAX_REG];  //será usado para armazenar os registros de operacoes.txt
    int controle;                        //variável que receberá o número do caso para cada operação

    //Para verificar a abertura do programa:
    if (argc < 3) {
        fprintf(stderr, "Numero incorreto de argumentos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-i") == 0) {  //acessando a funcionalidade de implementação

        arquivo_dat = fopen("dados.dat", "wb");  //abertura e criação do arquivo para escrever os livros com seu tamanho de registro
        flivros = fopen(argv[2], "r");           //abertura do arquivo livros.txt para coletar os registros

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);

        if (arquivo_dat == NULL) {
            printf("\nErro na abertura do arquivo -- programa finalizado.\n");
            system("pause");
            exit(1);
        }

        tam_reg = leia_registro(flivros, buffer_livros, TAM_MAX_REG);  //faz a leitura do registro de livros.txt, retornando seu tamanho em tam_reg e o registro em buffer

        fwrite(&LEDHead, sizeof(int), 1, arquivo_dat);  //escreve o cabeçalho de dados.dat com -1 na LED de espaços vazios

        while (tam_reg > 0) {
            fwrite(&tam_reg, sizeof(short), 1, arquivo_dat);            //escreve o tamanho do registro a ser inserido
            fwrite(buffer_livros, sizeof(char), tam_reg, arquivo_dat);  //escreve o registro inserido

            tam_reg = leia_registro(flivros, buffer_livros, TAM_MAX_REG);
            num_reg++;  //conta quantos registros foram coletados
        }

        if (num_reg > 0) {
            printf("Operacao concluida.\nQuantidade de registros coletados e inseridos em dados.dat: %d\n", num_reg);
        } else {
            printf("Erro na operação.\n");
        }

        fclose(flivros);      //fecha o arquivo livros.txt
        fclose(arquivo_dat);  //fecha o arquivo dados.dat
    } else if (strcmp(argv[1], "-e") == 0) {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);

        if ((arquivo_dat = fopen("dados.dat", "r+b")) == NULL) {
            printf("Arquivo dados.dat não existe, programa finalizado.\n");
            system("pause");
            exit(1);
        }

        foperacoes = fopen("operacoes.txt", "r");

        tam_reg = leia_registro(foperacoes, buffer_operacoes, TAM_MAX_REG);  //armazena o tamanho do primeiro registro de operacoes.txt
        while (tam_reg > 0) {
            switch (buffer_operacoes[0]) {
                case BUSCA:
                    menu(1, buffer_operacoes, tam_reg);
                    break;
                case REMOCAO:
                    menu(2, buffer_operacoes, tam_reg);
                    break;
                case INSERCAO:
                    controle = 3;
                    break;
                default:
                    printf("Erro na leitura das operações do modo exportação.");
                    break;
            }
            tam_reg = leia_registro(foperacoes, buffer_operacoes, TAM_MAX_REG);
        }
    } else {
        fprintf(stderr, "Opcao \"%s\" nao suportada!\n", argv[1]);
    }

    return 0;
}