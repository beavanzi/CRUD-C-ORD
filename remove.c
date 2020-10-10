#include "main.h"

void remocao(int posicao_de_seek) {
    int LED;
    rewind(arq);
    fread(&LED, sizeof(int), 1, arq);  //verificando se a LED está vazia ou se tem algum espaço vazio no registro
    rewind(arq);
    fwrite(&posicao_de_seek, sizeof(int), 1, arq);  //escreve o primeiro registro de arq na posicao de seek
    fseek(arq, posicao_de_seek + 2, SEEK_SET);      //reposiciona o ponteiro de L/E do arquivo arq em (posicao_de_seek + 2) unidades a partir do começo do arquivo
    fwrite(&LED, sizeof(int), 1, arq);              //escreve o que estiver no arquivo, uma vez, na LED
}