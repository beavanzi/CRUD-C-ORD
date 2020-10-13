#include <string.h>

#include "main.h"

void remocao(int posicao_de_seek) {
    short tam_reg = 0;
    int num = 0, num2 = 0;
    char buffer[5], buffer_reg[TAM_MAX_REG], LEDHEAD_string[5];

    buffer[0] = '\0';
    sprintf(LEDHEAD_string, "%d", LEDHead);  //transforma int em string
    strcat(buffer, "*");
    strcat(buffer, LEDHEAD_string);
    printf("\n%s", buffer);

    fseek(arquivo_dat, (posicao_de_seek + 2), SEEK_SET);
    num = fwrite(buffer, sizeof(char), (strlen(buffer)), arquivo_dat);
    LEDHead = posicao_de_seek;
    printf("\n%d", num);

    fseek(arquivo_dat, posicao_de_seek, SEEK_SET);
    fread(&tam_reg, sizeof(short), 1, arquivo_dat);         // le o tamanho do registro de dentro do arquivo e armazena o valor na tam_reg
    fread(buffer_reg, sizeof(char), tam_reg, arquivo_dat);  // le do arquivo arq "tamanho" numero de elementos, e armazena na string buffer
    printf("\n\n%s", buffer_reg);

    rewind(arquivo_dat);
    num2 = fwrite(&LEDHead, sizeof(short), 4, arquivo_dat);
    printf("\n%d", num2);
}