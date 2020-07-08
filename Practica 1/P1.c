#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct elemento nodo_aux,nodo_aux1,nodo_aux2; 

struct elemento{ //nodo
	char dato;
	char trans[1000];
	struct elemento *next;
};

struct pila{
	struct elemento *frente;
	int tamano;
};

int crear(struct pila *);
int push(struct pila *, struct elemento);
int pop(struct pila *, struct elemento *);
int vacia(struct pila);
char top(struct pila *p);
int jerarquia(char);
int hacer_archivo(char [],char []);
char *agregar_punto(char []);
struct pila posfijo(char []);
struct pila intermedio(struct pila pila_pos);

int main(){

	char cadena_inf[50];
	struct pila pila_pos;
	crear(&pila_pos);
	struct pila pila_aux;
	crear(&pila_aux);
        
	printf("Inserta expresion: \t");
	scanf("%s",cadena_inf);
        
    //printf("Entrada: %s\n",cadena_inf);
        //agregar el punto
    strcpy(cadena_inf,agregar_punto(cadena_inf));
    
    //printf("Entrada: %s\n",cadena_inf);

        //Expresion posfija
	pila_pos = posfijo(cadena_inf);	
	
		//Lenguaje intermedio
	pila_aux = intermedio(pila_pos);

	pop(&pila_aux,&nodo_aux);
	//printf("%s\n",nodo_aux.trans);

		//Lenguaje final
	hacer_archivo(nodo_aux.trans,cadena_inf);
	
	return 0;
}

char *agregar_punto(char *cadena_inf){

	char cadena_aux[50] = "";
    int aux_bool = 0;
    int aux = strlen(cadena_inf)-1;
    int agregar = 0;

	for(int i=0, j=0 ; i <= aux ; i++){

	if(cadena_inf[i] == '|') agregar = 0;
	else if(cadena_inf[i] == ')' && (cadena_inf[i+1] != '+' || cadena_inf[i+1] != '*')) agregar = 0;
	else if(cadena_inf[i+1] == ')' && (cadena_inf[i-1] != '+' || cadena_inf[i-1] != '*')) agregar = 0;
	else if((cadena_inf[i] == '+' || cadena_inf[i] == '*') && (cadena_inf[i+1] == '+') || cadena_inf[i+1] == '*') agregar = 0;
	else if((cadena_inf[i] == '+' || cadena_inf[i] == '*') && cadena_inf[i+1] == '(') agregar = 1;
	else if(cadena_inf[i] == '(') agregar = 0;
	else if(cadena_inf[i+1] == '+' || cadena_inf[i+1] == '*' || cadena_inf[i+1] == '|') agregar = 0;
	else if(i == aux ) agregar = 0;
	else agregar =1;


	if(agregar == 1){
		cadena_aux[j] = cadena_inf[i];
		j++;
		cadena_aux[j] = '.';
    }else cadena_aux[j] = cadena_inf[i];

    j++;
    }

    strcpy(cadena_inf,cadena_aux);

    return cadena_inf;
}

int hacer_archivo(char *cadena, char *input){
	char cadena_out[1000] ="digraph maquina {\n\tshape = circle;\n\trankdir = LR;\n\t1[shape = box label= \"";
	strcat(cadena_out,input);
	strcat(cadena_out,"\"];\n\t0");
	char aux_char[2];
	aux_char[1] = '\0';

	strcat(cadena_out," [shape = point];\n\t0 -> ");
	aux_char[0] = cadena[0];
	strcat(cadena_out,aux_char);
	strcat(cadena_out,";\n\t");
	aux_char[0] = cadena[strlen(cadena)-2];
	strcat(cadena_out,aux_char);
	strcat(cadena_out," [shape = doublecircle];\n\t");

	char cadena_aux[1000]="";
	char *token;

	token = strtok(cadena,"-");

    while( token != NULL ) {
    	if (!(token[0] == token[2] && token[1] == '*')){
    		aux_char[0] = token[0];
			strcat(cadena_aux,aux_char);
			strcat(cadena_aux," -> ");
			aux_char[0] = token[2];
			strcat(cadena_aux,aux_char);
			strcat(cadena_aux," [label=");
			if(token[1] == '*') strcat(cadena_aux,"ε");
			else{
			aux_char[0] = token[1];
			strcat(cadena_aux,aux_char);
		}
		strcat(cadena_aux,"];\n\t");
    	}
	   	
	    
	      token = strtok(NULL,"-");
    }

	remove("out.dot");
	
	FILE *fp;
	fp = fopen("out.dot", "w");

	strcat(cadena_out,cadena_aux);
	strcat(cadena_out,"}");
	
	fputs(cadena_out , fp);
	fclose(fp);
	return 0;
}

struct pila intermedio(struct pila pila_pos){
	struct pila pila_aux;
	crear(&pila_aux);
	char estados[]="abcdefghijklmnopqrstuvwxyz";
	int aux_int = 0;
	char aux_char[2];
	aux_char[1] = '\0';

	while(!vacia(pila_pos)){
		pop(&pila_pos,&nodo_aux);
		if(nodo_aux.dato == '+'){	
			pop(&pila_aux,&nodo_aux1);               
            
			strcpy(nodo_aux.trans,"");

			aux_char[0] = estados[aux_int];
			aux_int++;
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = nodo_aux1.trans[0];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			strcat(nodo_aux.trans,nodo_aux1.trans);

			aux_char[0] = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = nodo_aux1.trans[0];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			aux_char[0] = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = estados[aux_int];
			aux_int++;
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			push(&pila_aux,nodo_aux);
			
		}else if(nodo_aux.dato == '*'){

			pop(&pila_aux,&nodo_aux1);               
            
			strcpy(nodo_aux.trans,"");

			aux_char[0] = estados[aux_int];
			aux_int++;
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = nodo_aux1.trans[0];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			strcat(nodo_aux.trans,nodo_aux1.trans);

			aux_char[0] = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = nodo_aux1.trans[0];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			aux_char[0] = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = estados[aux_int];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			aux_char[0] = nodo_aux.trans[0];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = estados[aux_int];
			aux_int++;
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			push(&pila_aux,nodo_aux);

		}else if(nodo_aux.dato == '|'){
			pop(&pila_aux,&nodo_aux2);
			pop(&pila_aux,&nodo_aux1);

			nodo_aux.dato = nodo_aux.dato;

			aux_char[0] = estados[aux_int];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = nodo_aux1.trans[0];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			strcat(nodo_aux.trans,nodo_aux1.trans);

			aux_char[0] = estados[aux_int];
			aux_int++;
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = nodo_aux2.trans[0];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			strcat(nodo_aux.trans,nodo_aux2.trans);

			aux_char[0] = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = estados[aux_int];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			aux_char[0] = nodo_aux2.trans[strlen(nodo_aux2.trans)-2];
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"*");
			aux_char[0] = estados[aux_int];
			aux_int++;
			strcat(nodo_aux.trans,aux_char);
			strcat(nodo_aux.trans,"-");

			push(&pila_aux,nodo_aux);
			
		}else if(nodo_aux.dato == '.'){
			
			pop(&pila_aux,&nodo_aux2);
			pop(&pila_aux,&nodo_aux1);
              
          	if(strlen(nodo_aux2.trans) <= 4) {
          		strcat(nodo_aux.trans,nodo_aux1.trans);

          		aux_char[0] = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
				strcat(nodo_aux.trans,aux_char); 
	            aux_char[0] = nodo_aux2.trans[strlen(nodo_aux2.trans)-3];
	            strcat(nodo_aux.trans,aux_char);
				aux_char[0] = nodo_aux2.trans[0];
				strcat(nodo_aux.trans,aux_char);
				strcat(nodo_aux.trans,"-");
          	} else {
          		char aux_1 = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
          		char aux_2 = nodo_aux2.trans[0];
          		for(int j = 0 ; j <= strlen(nodo_aux2.trans) -1 ; j++){
          			if(nodo_aux2.trans[j] == aux_2) nodo_aux2.trans[j] = aux_1;
          		}
          		strcat(nodo_aux.trans,nodo_aux1.trans);
          		aux_char[0] = nodo_aux1.trans[strlen(nodo_aux1.trans)-2];
				strcat(nodo_aux.trans,aux_char);
				strcat(nodo_aux.trans,"*");
				aux_char[0] = nodo_aux2.trans[0];
				strcat(nodo_aux.trans,aux_char);
				strcat(nodo_aux.trans,"-");
				strcat(nodo_aux.trans,nodo_aux2.trans);
          	}     

			push(&pila_aux,nodo_aux);
			
		}else {
			nodo_aux1.dato = nodo_aux.dato;
			
			aux_char[0] = estados[aux_int];
			aux_int++;
			strcpy(nodo_aux1.trans,"");
			strcat(nodo_aux1.trans,aux_char);

			strcat(nodo_aux1.trans,&nodo_aux.dato);

			aux_char[0] = estados[aux_int];
			aux_int++;
			strcat(nodo_aux1.trans,aux_char);
			strcat(nodo_aux1.trans,"-");
			
			push(&pila_aux,nodo_aux1);
		}
	}

	return pila_aux;
}

struct pila posfijo(char cadena_inf[]){
	struct pila pila_aux;
	crear(&pila_aux);
    struct pila pila_pos;
	crear(&pila_pos);   
    
    for (int i = 0 ; i <= strlen(cadena_inf)-1 ; i++ ){
		if(cadena_inf[i] == '('){
			nodo_aux.dato = cadena_inf[i];
			push(&pila_aux,nodo_aux);
		}else if(cadena_inf[i] == ')'){
			pop(&pila_aux,&nodo_aux);
			while(nodo_aux.dato != '('){
				push(&pila_pos,nodo_aux);
				pop(&pila_aux,&nodo_aux);
			}			
		}else{
			while( !vacia(pila_aux) && ( jerarquia(top(&pila_aux)) >= jerarquia(cadena_inf[i]) )){
				pop(&pila_aux,&nodo_aux);
				push(&pila_pos,nodo_aux);
			}
			nodo_aux.dato = cadena_inf[i];
			push(&pila_aux,nodo_aux);
		}
	}	    

    while(!vacia(pila_pos)){
		pop(&pila_pos,&nodo_aux);
		push(&pila_aux,nodo_aux);
	}

	return pila_aux;
}

int jerarquia(char c){
	if( c == '+' || c == '*') return 3;
	if( c == '.' ) return 2;
	if( c == '|' ) return 1;
	if( c == '(' ) return 0;
}

int crear(struct pila *p){
	p -> frente = NULL;
	p -> tamano = 0;
	return 1;
}

int push(struct pila *p, struct elemento elemento){
	struct elemento *nuevo = (struct elemento *) malloc(sizeof(struct elemento));
	if(nuevo == NULL) return -1;
	nuevo -> dato = elemento.dato;
	strcpy (nuevo -> trans, elemento.trans);
	nuevo -> next = NULL;

	nuevo -> next = p -> frente;
	p -> frente = nuevo;
	p -> tamano ++;
	return 1;
}


int pop(struct pila *p, struct elemento *elemento){
	if(vacia(*p)) return -1;
	elemento -> dato = p -> frente -> dato;
	strcpy(elemento -> trans, p -> frente -> trans);
	p -> frente = p -> frente -> next;
	p -> tamano --;
}

int vacia(struct pila p){
	if(p.tamano == 0) return 1;
	return 0;
}

int tamano(struct pila p){
	return p.tamano;
}

char top(struct pila *p){
	if(vacia(*p)) return -1;
	return p -> frente -> dato;
}