/*Coleta de livros.txt e alocando em dados.dat, colocando o tamanho na frente
  de cada registro, salvando tudo em binário.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_REG 256
#define DELIM_STR "|"

//GLOBAIS
FILE *arq;

//FUNÇÕES
short leia_registro(FILE *, char *, int); //Utilizada para ler os registros do livro.txt -> leitura primária para jogar em .dat
void menu(int, char, int);                // x é o número que está atribuído em controle, str é o buffer, tamanho_registro é o strlen da buffer2, head é a cabeça da LED do começo do arquivo
int busca(int, char *, short *, int *);   //A função busca fará a leitura da chave dos registros, retornará 0 se não encontrar o registro, 1 se encontrar
void remocao(int);                        //Fará a remoção de um registro qualquer do meu arquivo arq

int main(int argc, char **argv)
{
    //VARIAVEIS PARA A IMPORTAÇÃO
    FILE *aux; //para receber e ler o arquivo livros.txt
    short tam_reg = 0;
    int head = -1; //cabeçalho
    int num_reg = 0;
    char buffer[TAM_MAX_REG];

    //VARIAVEIS PARA AS OPERACOES
    FILE *aux2;                //receberá o arquivo dados.dat para leitura
    FILE *aux3;                //receberá o arquivo operacoes.txt para leitura
    char buffer2[TAM_MAX_REG]; //será usado para armazenar os registros de operacoes.txt
    int controle;              //variável que receberá o número do caso para cada operação

    //Para verificar a abertura do programa:
    if (argc < 3)
    {
        fprintf(stderr, "Numero incorreto de argumentos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s (-i|-e) nome_arquivo\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "-i") == 0)
    { //acessando a funcionalidade de implementação

        arq = fopen("dados.dat", "wb"); //abertura e criação do arquivo para escrever os livros com seu tamanho de registro
        aux = fopen(argv[2], "r");      //abertura do arquivo livros.txt para coletar os registros

        printf("Modo de importacao ativado ... nome do arquivo = %s\n", argv[2]);

        if (arq == NULL)
        {
            printf("\nErro na abertura do arquivo -- programa finalizado.\n");
            system("pause");
            exit(1);
        }

        tam_reg = leia_registro(aux, buffer, TAM_MAX_REG) - 1; //faz a leitura do registro de livros.txt, retornando seu tamanho em tam_reg e o registro em buffer

        fwrite(&head, sizeof(int), 1, arq); //escreve o cabeçalho de dados.dat com -1 na LED de espaços vazios

        while (tam_reg > 0)
        {
            fwrite(&tam_reg, sizeof(short), 1, arq);    //escreve o tamanho do registro a ser inserido
            fwrite(buffer, sizeof(char), tam_reg, arq); //escreve o registro inserido

            tam_reg = leia_registro(aux, buffer, TAM_MAX_REG);
            num_reg++; //conta quantos registros foram coletados
        }

        if (num_reg > 0)
        {
            printf("Operacao concluida.\nQuantidade de registros coletados e inseridos em dados.dat: %d\n", num_reg);
        }
        else
        {
            printf("Erro na operação.\n");
        }

        fclose(aux); //fecha o arquivo livros.txt
        fclose(arq); //fecha o arquivo dados.dat
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);

        if ((aux2 = fopen("dados.dat", "rb")) == NULL)
        {
            printf("Arquivo dados.dat não existe, programa finalizado.\n");
            system("pause");
            exit(1);
        }

        aux3 = fopen("operacoes.txt", "r");

        tam_reg = leia_registro(aux3, buffer2, TAM_MAX_REG); //armazena o tamanho do primeiro registro de operacoes.txt
        printf("\n%d", tam_reg);
        printf("\n%s", buffer2); //RETIRAR ESSA MERDA DEPOIS!!!!!!!!!!!!!!!!!
        while (tam_reg > 0)
        { //SE ENTRAR EM LOOP INFINITO MUDAR O VALOR PARA 1;;;;; APAGAR ISSO AQUI DPS DE CORRIGIR O ERRO
            if (buffer2[0] == 'b')
            {
                printf("teste");

                controle = 1;
            }
            else if (buffer2[0] == 'r')
            {
                controle = 2;
            }
            else if (buffer2[0] == 'i')
            {
                controle = 3;
            }
            else
            {
                printf("tamanho registro: %d bytes\n", tam_reg);
                controle = 0;
            }
            tam_reg = leia_registro(aux3, buffer2, TAM_MAX_REG); //vai ler o próximo registro e assim por diante até o fim do while
        }
    }
    else
    {
        fprintf(stderr, "Opcao \"%s\" nao suportada!\n", argv[1]);
    }

    return 0;
}

// Função bem similar à função input, porém na input era utilizado getchar para ler o caracter, como aqui vamos ler direto de um arquivo, usaremos fgetc
short leia_registro(FILE *arq, char *str, int size)
{                // passa o arquivo do qual vai ser lido, a string em que o caracter vai ser copiado, e o tamanho da string
    short i = 0; // i é a quantidade de caractere do registro, será o retorno da função
    char c = fgetc(arq);
    while ((c != EOF) && (c != '\n'))
    { // enquanto não chegar no final do arquivo, e enquanto não encontrar um \n, pois precisamos ler registro por registro até o \n
        if (size > 0)
        {
            str[i] = c;
            i++;
            size--;
        }
        c = fgetc(arq);
    }
    str[i] = '\0'; // coloca o \0 no final do registro escrito
    return i;      // retorna a quantidade de caracteres do registro
}

void menu(int x, char str, int tamanho_registro)
{ // x é o número que está atribuído em controle, str é o buffer, tamanho_registro é o strlen da buffer2, head é a cabeça da LED do começo do arquivo
    char *num_reg;
    int i = 0;
    short tamanho_reg = tamanho_registro;
    int chave = 0; // número da frente de cada registro
    int posicao_de_seek = 0;
    char *aux; // string pra ser usada na strtok e armazenar apenas o número do registro
    char buffer[TAM_MAX_REG];
    char buffer2[TAM_MAX_REG]; //string que será usada para armazenar os registros de busca

    switch (x)
    {
    case 1: //operação de busca
        for (i = 2; i < strlen(buffer); i++)
        { // começa em dois para pular a letra de comando e o espaço
            buffer2[i - 2] = buffer[i];
        }
        strcpy(aux, buffer2); //realiza a cópia do conteúdo de buffer2 para aux
        num_reg = strtok(aux, "|");
        chave = atoi(num_reg);
        busca(chave, buffer2, &tamanho_reg, &posicao_de_seek);
        break;
    case 2: //operação de remoção
        if (busca(chave, buffer2, &tamanho_reg, &posicao_de_seek) == 1)
        { //verificando se o registro existe, se existir então procedemos com a remoção
            remocao(posicao_de_seek);
            printf("Remocao do registro de chave %d\n", chave);
            printf("Registro removido! (%d vytes)\n", tamanho_reg);
            printf("Posicao: offset = %d bytes\n", posicao_de_seek);
        }
        else
        {
            printf("Remocao do registro de chave %d\n", chave);
            printf("Registro nao encontrado!");
        }

        break;
    default:
        printf("Erro");
        break;
    }
}

//A função busca fará a leitura da chave dos registros, retornará 0 se não encontrar o registro, 1 se encontrar
int busca(int chave, char *buffer2, short *tamanho_registro, int *posicao_de_seek)
{
    int achou = 0;
    short tam_reg;
    int key; //será utilizada na conversão da aux para inteiro
    char *aux;
    char buffer[TAM_MAX_REG];
    int posicao_de_leitura;

    rewind(arq);             // volta o ponteiro de L/E no byte 0 do arquivo, pra começar a ler dnv
    fseek(arq, 4, SEEK_SET); // movendo o ponteiro de L/E em 4 bytes a partir do começo do arquivo p/ pular a LED (não queremos ler ela)
    while (achou == 0)
    {
        posicao_de_leitura = ftell(arq);           //mostra em qual byte (do arquivo) está sendo realizada a leitura
        fread(&tam_reg, sizeof(short), 1, arq);    // le o tamanho do registro de dentro do arquivo e armazena o valor na tam_reg
        fread(buffer, sizeof(char), tam_reg, arq); // le do arquivo arq "tamanho" numero de elementos, e armazena na string buffer

        aux = strtok(buffer, "|"); // pega apenas o número do registro de cada registro no buffer, pois vai ler até chegar no |
        key = atoi(aux);           // converte o valor de char da aux para int e armazena em key

        if (chave == key)
        {
            achou = 1;
            printf("Busca pelo registro de chave %d", key);
            tam_reg = tam_reg + 4; //+4 pois o fseek não está registrando os 4 bytes do rrn no tamanho do registro
            printf("%s %d bytes", buffer, tam_reg);
            *posicao_de_seek = posicao_de_leitura; //posicao_de_seek recebe a posicao do registro buscado
        }
    }

    return achou;
}

//Fará a remoção de um registro qualquer do meu arquivo arq
void remocao(int posicao_de_seek)
{
    int LED;
    rewind(arq);
    fread(&LED, sizeof(int), 1, arq); //verificando se a LED está vazia ou se tem algum espaço vazio no registro
    rewind(arq);
    fwrite(&posicao_de_seek, sizeof(int), 1, arq); //escreve o primeiro registro de arq na posicao de seek
    fseek(arq, posicao_de_seek + 2, SEEK_SET);     //reposiciona o ponteiro de L/E do arquivo arq em (posicao_de_seek + 2) unidades a partir do começo do arquivo
    fwrite(&LED, sizeof(int), 1, arq);             //escreve o que estiver no arquivo, uma vez, na LED
}