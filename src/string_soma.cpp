#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int ehDelimitador(char ch){
  if(ch == ',')
    return 1;
  return 0;
}

int char_para_int(char ch){
  return ch - 48;
}


int soma_string(const char * string_entrada){
  int soma = 0;
  int tamanho = strlen(string_entrada);

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
    if(string_entrada[i] != '\n'){
      if(ehNumero(string_entrada[i])){
        soma += char_para_int(string_entrada[i]);
        ++numeros_total;
        ++numeros_em_linha;
      }else if(ehDelimitador(string_entrada[i])){
        ++delimitador_total;
        ++delimitador_em_linha;
      }else{/*se não é um delimitador válido*/
        return -1;
      }/* fim if */
    }else{/*se é '\n'*/
        /*reseta a quantidade de numeros e delimitadores em uma linha*/
        delimitador_em_linha = 0;
        numeros_em_linha = 0;
    }/*fim if*/
  }/*fim for*/
  if(delimitador_em_linha >= 4 || numeros_em_linha >= 4)
    /*mais números ou delimitadores por linha*/
    return -1;
  if(numeros_total - delimitador_total != 1)
    /*quantidade de delimitadores ou de números incorreta*/
    return -3;
  if(numeros_total <= 1)
    /*quantidade insuficiente de números*/
    return -1;
  return soma;
}