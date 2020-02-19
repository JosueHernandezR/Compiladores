#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct elemento { //nodo
	char dato;
	struct elemento *next;
};

struct pila {
	struct elemento *frente;
	int tamano;
};

int crear(struct pila *);
int push(struct pila *, struct elemento);
int pop(struct pila *, struct elemento *);
int vacia(struct pila);

int main(int argc, char const *argv[]) {
	if(argc<2) {		
		//Esto pasa si no se ingresa un argumento entre comillas
		printf("Ingrese una expresión regular\n");
		exit(1);
	}
	//Instancias de los struct de la pila
	struct pila pila1,pila2;
	struct elemento e1;
	struct elemento e2;
	//Crear dos pilas de tipo entero
	crear(&pila1);
	crear(&pila2);
	//Contador para la iteración de la pila
	int i;
	//Iteracion caracter por caracter
	for (i = 0; argv[1][i] != 0; i++) {
		//Validaciones
		if (argv[1][i] == '(') {
			e1.dato=argv[1][i];
			push(&pila1,e1);
		} else if (argv[1][i] == ')') {
			pop(&pila1,&e1);
			while (e1.dato != '(') {
				push(&pila2,e1);
				pop(&pila1,&e1);
			}			
		} else if (argv[1][i] == '*' || argv[1][i] == '+' || argv[1][i] == '.' || argv[1][i] == '|') {
			if (vacia(pila1)) {
				e1.dato = argv[1][i];
				push(&pila1,e1);
			} else {
				pop(&pila1,&e1);
				if (e1.dato == '(') {
					push(&pila1,e1);
					e1.dato = argv[1][i];
					push(&pila1,e1);
				} else {
					push(&pila1,e1);
					while(1) {
						pop(&pila1,&e1);
						if (argv[1][i] == '*' ||  argv[1][i] == '+' || e1.dato == '+') {					
							push(&pila1,e1);
							e1.dato = argv[1][i];
							push(&pila1,e1);
							break;
						} else if (argv[1][i] == '*' && (e1.dato == '.' || e1.dato == '|')) {
							push(&pila1,e1);
							e1.dato = argv[1][i];
							push(&pila1,e1);
							break;
						}
						else if (argv[1][i] == '.' && e1.dato == '.') {
							push(&pila1,e1);
							e1.dato = argv[1][i];
							push(&pila1,e1);
							break;
						}
						else if (argv[1][i] == '.' && (e1.dato == '+' || e1.dato == '*') || argv[1][i] == '|' && (e1.dato == '+' || e1.dato == '.' ||  e1.dato == '*')) {
							push(&pila2,e1);
						}
					}
				}
			}
		} else {
			e1.dato = argv[1][i];
			push(&pila2,e1);
		}
	}
	while(!vacia(pila1)) {
		pop(&pila1,&e1);
		push(&pila2,e1);
	}
	while(!vacia(pila2)) {
		pop(&pila2,&e1);
		push(&pila1,e1);
	}
	while(!vacia(pila1)) {
		pop(&pila1,&e1);
		printf("%c",e1.dato);
	}
	printf("\n");
/*
	struct elemento e1;
	struct elemento e2;
	struct elemento e3;

	e1.dato = 'a';
	e2.dato = 'b';
	e3.dato = 'c';

	push(&pila1,e1);
	push(&pila1,e2);
	push(&pila1,e3);

	printf("Tamano :%d\n",pila1.tamano);

	struct elemento fuera;

	pop(&pila1,&fuera);

	printf("%c\n", fuera.dato);
	printf("Tamano :%d\n",pila1.tamano);

	pop(&pila1,&fuera);

	printf("%c\n", fuera.dato);
	printf("Tamano :%d\n",pila1.tamano);

	pop(&pila1,&fuera);

	printf("%c\n", fuera.dato);
	printf("Tamano :%d\n",pila1.tamano);
*/
	return 0;
}

int crear(struct pila *p) {
	p -> frente = NULL;
	p -> tamano = 0;
	return 1;
}

int push(struct pila *p, struct elemento elemento) {
	struct elemento *nuevo = (struct elemento *) malloc(sizeof(struct elemento));
	if(nuevo == NULL) {
		return -1; 
	}
	nuevo -> dato = elemento.dato;
	nuevo -> next = NULL;
	nuevo -> next = p -> frente;
	p -> frente = nuevo;
	p -> tamano ++;
	return 1;
}


int pop(struct pila *p, struct elemento *elemento) {
	if(vacia(*p)) {
		return -1;
	}
	elemento -> dato = p -> frente -> dato;
	p -> frente = p -> frente -> next;
	p -> tamano --;
}

int vacia(struct pila p) {
	if(p.tamano == 0) {
		return 1;
	}
	return 0;
}

int tamano(struct pila p) {
	return p.tamano;
}