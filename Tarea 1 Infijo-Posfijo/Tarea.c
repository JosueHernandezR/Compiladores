#include <stdio.h>

int isOperator(char c) {
	if (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='(' || c==')'){
		return 1;
	}
	return 0;
}

int precedencia (char x, char y) {
	int prec1, prec2;

	switch(x) {
		case '+':
			prec1=1;
			break;
		case '-':
			prec1=2;
			break;
		case '*':
			prec1=3;
			break;
		case '/':
			prec1=4;
			break;
		case '^':
			prec1=5;
	}

	switch(y) {
	case '+':
		prec2=1;
		break;
	case '-':
		prec2=2;
		break;
	case '*':
		prec2=3;
		break;
	case '/':
		prec2=4;
		break;
	case '^':
		prec2=5;
	}

	return prec1-prec2;
}

int main() {
	char inf [401];
	char post [401];
	char pila [200];
	int ptr=0;
	int j=0;

	scanf("%s", inf);
	for(int i=0; inf[i]!='\0'; i++) {
		if (!isOperator(inf[i])) {
			post[j]=inf[i];
			j++;
		} else if (inf[i]=='(') {
			pila[++ptr]='(';
		} else if (inf[i]==')') {
			while(pila[ptr]!='(' && ptr>0) {
				post[j]=pila[ptr--];
				j++;
			}
			if (pila[ptr]=='(') {
				ptr--;
			}
		} else {
			while(precedencia(inf[i], pila[ptr]) < 0 && pila[ptr]!='(' && ptr>0) {
				post[j]=pila[ptr--];
				j++;
			}
			pila[++ptr]=inf[i];
		}
	}

	while(ptr>0) {
		post[j]=pila[ptr--];
		j++;
	}
	post[j]='\0';
	printf("%s\n", post);

	j=0;ptr=0;

	return 0;
}
