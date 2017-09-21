#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/string_soma.hpp"

int main()
{
	char arquivo_entrada[100], string[100];
	scanf("%s", arquivo_entrada);
	FILE * f_entrada;
	f_entrada = fopen(arquivo_entrada, "r");
	int ch;
	int i = 0;
	ch = fgetc(f_entrada);
	while(ch != EOF){
		string[i] = ch;
		++i;
		ch = fgetc(f_entrada);
	}

	int d = soma_string(string);
	FILE * f_saida;
	f_saida = fopen("resultado.txt", "w");
	fprintf(f_saida, "%d\n", d);
	fclose(f_entrada);
	fclose(f_saida);
	return 0;
}