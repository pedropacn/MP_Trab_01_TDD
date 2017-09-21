#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/lista_func.hpp"

/**
* @brief garante que um caractere é um número com base na tabela ASCII.
* @params char que será verificado
* @return 1 se é um número e 0 do contrário
*/
int ehNumero(char ch){
  if(ch >= 48 && ch <= 57)
    return 1;
  return 0;
}

/**
* @brief garante que um caractere é um elimitador válido para a operação.
* @params String que será verificada
* @params Lista encadeada de delimitadores
* @return 1 se é um delimitador válido e 0 caso contrário
*/
int ehDelimitador(const char * str, t_lista * l){
  t_elemento * ele = l->inicio;
  while(ele != NULL){
    if(!strcmp(str, ele->delimitador))
      return 1;
    ele = ele->proximo;
  }
  return 0;
}

/**
* @brief para descobrir qual o tamanho do trecho da string de input que contém apenas um tipo de caractere.
* @params A posição do primeiro elemento do trecho a ser analizado.
* @params A string de entrada.
* @return um int com o tamanho da sequência
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

/**
* @brief Troca os valores da string para 'n'
* @params A string a ser limpa.
*/
int limpa_string(char * str){
  for (unsigned int i = 0; i < strlen(str); ++i)
    str[i] = 'n';
  return 1;
}

/**
* @brief copia, de uma string de origem pra uma de destino, um trecho de tamanho determinado.
* @params A posição inicial do trecho a ser copiado
* @params O tamanho do trecho a ser copiado
* @params A string de origem
* @params A string de destino
*/
int copia_trecho_de_string(int posicao_inicial, int intervalo, const char * string_entrada, char string_destino[10]){
  int i = 0;
  for (i = 0; i < intervalo; ++i){
    string_destino[i] = string_entrada[posicao_inicial + i];
  }
  string_destino[i] = '\0';
  return 1;
}

/**
* @brief Adiciona opções de delimitadores por meio de lista encadeadas
* @params Uma lista encadeada aonde serão armazenados os possíveis delimitadores
* @params Uma string que será adicionada aos possíveis delimitadores
*/
int adiciona_delimitador(t_lista * lista, const char * str){
  int posicao = 0;
  char temp[20];
  while(str[posicao] != '\n'){
    if(str[posicao] == '['){
      int i = 0;
      ++posicao;
      while(str[posicao] != ']'){
        temp[i] = str[posicao];
        ++i;
        ++posicao;
      }
      temp[i] = '\0';
      insereInicio(temp, lista);
    }
    ++posicao;
  }
  return posicao + 1;
}

int soma_string(const char * string_entrada){
  int soma = 0;
  const int tamanho = strlen(string_entrada);
  char string_em_analise[10];

  /**< variáveis de controle*/
  int delimitador_total = 0, delimitador_em_linha = 0;
  int numeros_total = 0, numeros_em_linha = 0;

  if(!ehNumero(string_entrada[0]) && string_entrada[0] != '/')
    /**< expresão que não começa com número nem o marcador de adição de delimitador*/
    return -1;

  if(string_entrada[tamanho - 1] != '\n')
    /**< expressão sem quebra de linha final*/
    return -1;

  int posicao_inicial_de_numeros = 0;
  t_lista * lista_de_delimitadores;
  lista_de_delimitadores = criarLista();/**< inicializa a lista de delimitadores*/
  insereInicio(",", lista_de_delimitadores);/**< inserção do delimitador padrão*/
  if(string_entrada[0] == '/' && string_entrada[1] == '/')
    /**< significa que delimitadores serão adicionados */
    posicao_inicial_de_numeros = adiciona_delimitador(lista_de_delimitadores, string_entrada);
  for (int i = posicao_inicial_de_numeros; i < tamanho; ++i){
    if(string_entrada[i] != '\n'){
      limpa_string(string_em_analise);
      int tamanho_tipo = tamanho_de_tipo(i, string_entrada);
      copia_trecho_de_string (i, tamanho_tipo, string_entrada, string_em_analise);
      if(ehNumero(string_entrada[i])){
        if(strlen(string_em_analise)>= 4)/**< caso o número exceda o limite de 3 casas*/
          soma += (atoi(string_em_analise)/pow(10, tamanho_tipo - 1));
        else
          soma += atoi(string_em_analise);
        ++numeros_total;
        ++numeros_em_linha;
      }else if(ehDelimitador(string_em_analise, lista_de_delimitadores)){
        ++delimitador_total;
        ++delimitador_em_linha;
      }else{/**< se não é um delimitador válido*/
        return -1;
      }/**<  fim if */
      i += tamanho_tipo - 1; /*desloca o char em análise*/
    }else{/*se é '\n'*/
        /**< reseta a quantidade de numeros e delimitadores em uma linha*/
        delimitador_em_linha = 0;
        numeros_em_linha = 0;
    }/**< fim if*/
    if(delimitador_em_linha >= 4 || numeros_em_linha >= 4)
      /**< mais números ou delimitadores por linha*/
      return -1;
  }/**< fim for*/
  if(numeros_total - delimitador_total != 1)
    /**< quantidade de delimitadores ou de números incorreta*/
    return -1;
  if(numeros_total <= 1)
    /**< quantidade insuficiente de números*/
    return -1;
  return soma;
}