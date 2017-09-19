#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
*Função para garantir que um caractér é um
*número com base na tabela ASCII.
*Parâmetro: char que será verificado
*Retorno: 1 se é um número e 0 do contrário
*/
int ehNumero(char ch){
  if(ch >= 48 && ch <= 57)
    return 1;
  return 0;
}

/*
*Função para garantir que um caractér é um
*delimitador válido para a operação.
*Parâmetro: char que será verificado
*Retorno: 1 se é um delimitador válido
*e 0 caso contrário
*/
int ehDelimitador(const char * str){
  if(!strcmp(str, ","))
    return 1;
  return 0;
}

int char_para_int(char ch){
  return ch - 48;
}

/*
*Função para descobrir qual o tamanho do trecho da
*string dde input que contém apenas um tipo de 
*caracter.
*Parâmetros:
*A posição do primeiro elemento do trecho a ser analizado.
*A string de entrada.
*Saída:
*um int com o tamanho da sequência
*/
int tamanho_de_tipo(int posicao_inicial, const char * str){
  int tamanho = 0;
  if(ehNumero(str[posicao_inicial])){
    while (ehNumero(str[posicao_inicial + tamanho]))
      ++tamanho;
  }else{
    while (!ehNumero(str[posicao_inicial + tamanho]) && str[posicao_inicial + tamanho] != '\n'){
      ++tamanho;
    }
  }
  return tamanho;
}

/*
*Troca os valores da string para 'n'
*Parâmetro:
*A string a ser limpa.
*/
int limpa_string(char * str){
  for (int i = 0; i < strlen(str); ++i)
    str[i] = 'n';
  return 1;
}

/*
*copia, de uma string de origem pra uma de destino, um trecho de
*tamanho determinado.
*parâmetros:
*A posição inicial do trecho a ser copiado
*O tamanho do trecho a ser copiado
*A string de origem
*A string de destino
*/
int copia_trecho_de_string(int posicao_inicial, int intervalo, const char * string_entrada, char string_destino[10]){
  int i = 0;
  for (i = 0; i < intervalo; ++i){
    string_destino[i] = string_entrada[posicao_inicial + i];
  }
  string_destino[i] = '\0';
  return 1;
}

int soma_string(const char * string_entrada){
  int soma = 0;
  const int tamanho = strlen(string_entrada);
  char string_em_analise[10];

  /*variáveis de controle*/
  int delimitador_total = 0, delimitador_em_linha = 0;
  int numeros_total = 0, numeros_em_linha = 0;

  if(!ehNumero(string_entrada[0]))
    /*expresão que não começa com número*/
    return -1;

  if(string_entrada[tamanho - 1] != '\n')
    /*expressão sem quebra de linha final*/
    return -1;
  for (int i = 0; i < tamanho; ++i){
    limpa_string(string_em_analise);
    int tamanho_tipo = tamanho_de_tipo(i, string_entrada);
    copia_trecho_de_string (i, tamanho_tipo, string_entrada, string_em_analise);
    if(string_entrada[i] != '\n'){
      if(ehNumero(string_entrada[i])){
        if(strlen(string_em_analise)>= 4)/*caso o número exceda o limite de 3 casas*/
          soma += (atoi(string_em_analise)/pow(10, tamanho_tipo - 1));
        else
          soma += atoi(string_em_analise);
        ++numeros_total;
        ++numeros_em_linha;
      }else if(ehDelimitador(string_em_analise)){
        ++delimitador_total;
        ++delimitador_em_linha;
      }else{/*se não é um delimitador válido*/
        return -1;
      }/* fim if */
      i += tamanho_tipo - 1; /*desloca o char em análise*/
    }else{/*se é '\n'*/
        /*reseta a quantidade de numeros e delimitadores em uma linha*/
        delimitador_em_linha = 0;
        numeros_em_linha = 0;
    }/*fim if*/
    if(delimitador_em_linha >= 4 || numeros_em_linha >= 4)
      /*mais números ou delimitadores por linha*/
      return -1;
  }/*fim for*/
  if(numeros_total - delimitador_total != 1)
    /*quantidade de delimitadores ou de números incorreta*/
    return -1;
  if(numeros_total <= 1)
    /*quantidade insuficiente de números*/
    return -1;
  return soma;
}