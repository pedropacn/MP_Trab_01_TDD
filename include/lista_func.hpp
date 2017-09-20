typedef struct elemento{
	char delimitador[20];
	struct elemento * proximo;
}t_elemento;

typedef struct lista{
	t_elemento * inicio;
	t_elemento * fim;
}t_lista;

t_lista * criarLista();
void insereInicio(const char str[20], t_lista * l);
int lista_tamanho(t_lista * l);
void imprimir(t_lista * l);