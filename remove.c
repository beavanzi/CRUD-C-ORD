#include "main.h"

void remocao(int posicao_de_seek) {
    int LED;
    rewind(arquivo_dat);
    fread(&LED, sizeof(int), 1, arquivo_dat);  //verificando se a LED está vazia ou se tem algum espaço vazio no registro
    rewind(arquivo_dat);
    fwrite(&posicao_de_seek, sizeof(int), 1, arquivo_dat);  //escreve o primeiro registro de arq na posicao de seek
    fseek(arquivo_dat, posicao_de_seek + 2, SEEK_SET);      //reposiciona o ponteiro de L/E do arquivo arq em (posicao_de_seek + 2) unidades a partir do começo do arquivo
    fwrite(&LED, sizeof(int), 1, arquivo_dat);              //escreve o que estiver no arquivo, uma vez, na LED
}