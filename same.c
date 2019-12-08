#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./filaPonteiro.c"

void imprime(int matrix[][16], int score){
	printf("\033[0mX  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            if(j == 0){
                if(i<10){
                	printf("\033[0m%i  ",i);
                }else {
                    printf("\033[0m%i ", i);
                }
            }
            if(j > 8 ){
              if(matrix[i][j] == 1){
                	printf("\033[0;31m\u29E0  ");
              } else if(matrix[i][j] == 2){
                	printf("\033[0;34m\u29E0  ");
              } else if(matrix[i][j] == 3) {
                  	printf("\033[0;32m\u29E0  ");
              } else if(matrix[i][j] == 4) {
                  	printf("\033[0;33m\u29E0  ");
              } else if(matrix[i][j] == 5) {
                  	printf("\033[0;35m\u29E0  ");
			  }	else {
              		printf("   ");
              }
         	} else {
            	if(matrix[i][j] == 1){
					//vermelho
            	    printf("\033[0;31m\u29E0  ");
            	} else if(matrix[i][j] == 2){
					//azul
                	printf("\033[0;34m\u29E0  ");
            	} else if(matrix[i][j] == 3) {
					//verde
                 	printf("\033[0;32m\u29E0  ");
            	} else if(matrix[i][j] == 4) {
					//verde
                 	printf("\033[0;33m\u29E0  ");
            	} else if(matrix[i][j] == 5) {
					//verde
                 	printf("\033[0;35m\u29E0  ");
            	} else {
            		printf("   ");
          		}
        	}
    	}
    	printf("\033[0m\n");
	}
	printf("\nPontuação atual: %i\n", score);
}
void geraMatriz(int matrix[][16], int dificuldade){
	for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            int a = rand() % (dificuldade+3);
            while(a == 0){
              a = rand() % (dificuldade+3);
            }
            matrix[i][j] = a;
        }
    }
}

int buscaLargura(int matrix[][16], ixj entrada, int pesquisa, int *score){
	Fila q;
	inicializaFila(&q);
	insereFila(&q, entrada);
	int efetividade = 1;
	int corEntrada = matrix[entrada.i][entrada.j];
	if(corEntrada != 0){
		while(!filaVazia(&q)){
			ixj no;
			ixj noVizinho;
			removeFila(&q, &no);
			if(no.i+1 < 12 && corEntrada == matrix[no.i+1][no.j]){
				if(pesquisa == 1){
					return 1;
				} else {
					matrix[no.i+1][no.j] = 0;
					noVizinho.i = no.i + 1;
					noVizinho.j = no.j;
					insereFila(&q, noVizinho);
				}
			}
			if(no.i-1 >= 0 && corEntrada == matrix[no.i-1][no.j]){
				if(pesquisa == 1){
					return 1;
				} else {
				matrix[no.i-1][no.j] = 0;
				noVizinho.i = no.i - 1;
				noVizinho.j = no.j;
				insereFila(&q, noVizinho);
				}
			}
			if(no.j+1 < 16 && corEntrada == matrix[no.i][no.j+1]){
				if(pesquisa == 1){
					return 1;
				} else {
					matrix[no.i][no.j+1] = 0;
					noVizinho.i = no.i;
					noVizinho.j = no.j + 1;
					insereFila(&q, noVizinho);
				}
			}
			if(no.j-1 >= 0 && corEntrada == matrix[no.i][no.j-1]){
				if(pesquisa == 1){
					return 1;
				} else {
					matrix[no.i][no.j-1] = 0;
					noVizinho.i = no.i;
					noVizinho.j = no.j - 1;
					insereFila(&q, noVizinho);
				}
			}
			if(!filaVazia(&q) && pesquisa == 0){
				matrix[no.i][no.j] = 0;
				efetividade++;
			}
		}
		if(score != NULL && efetividade > 1){
			*score = *score + ((efetividade-2) * (efetividade-2));
		}
		return 0;
	}
	return 0;
}

void deslocaBaixo(int matrix[][16]){
	//descola pra baixo
	for(int col = 15; col >= 0; col--){
		Fila q;
		inicializaFila(&q);
		for(int lin = 11; lin >= 0; lin--){
			if(matrix[lin][col] != 0){
				ixj hold;
				hold.i = matrix[lin][col];
				insereFila(&q, hold);
				matrix[lin][col] = 0;
			}
		}
		for(int lin = 11; lin >= 0 && !filaVazia(&q); lin--){
			ixj volta;
			removeFila(&q, &volta);
			matrix[lin][col] = volta.i;
		}
	}
}


void deslocaLado(int matrix[][16], int *venceu){
	*venceu = 0;
	for(int col = 0; col < 16; col++){
		for(int i = col; i < 16; i++){
			if(matrix[11][col] == 0 && col+1 < 16 && matrix[11][i] != 0){
				for(int lin = 11; lin >= 0; lin--){
					matrix[lin][col] = matrix[lin][i];
					matrix[lin][i] = 0;
				}
			}
		}
		*venceu = *venceu + matrix[11][col];
	}
}

int checaValidade(int matrix[][16]){
	for(int i = 11; i >= 0; i--){
		for(int j = 0; j < 16; j++){
			ixj teste;
			teste.i = i;
			teste.j = j;
			if(buscaLargura(matrix, teste, 1, NULL) == 1){
				return 1;
			}
		}
	}
	return 0;
}

void iniciaJogo(int modo){
	int matrix[12][16];
    ixj indice;
	int jogadasValidas = 1, venceu = 1;

    geraMatriz(matrix, modo);    
	int pontuacao = 0;
    imprime(matrix, pontuacao);
    
	while(jogadasValidas == 1 && venceu != 0){
		printf("\nEscolha um indice (linha,coluna): ");
		scanf("%i,%i", &indice.i, &indice.j);

		buscaLargura(matrix, indice, 0, &pontuacao);
		deslocaBaixo(matrix);
		deslocaLado(matrix, &venceu);
		if(venceu != 0){
			jogadasValidas = checaValidade(matrix);
		}
		imprime(matrix, pontuacao);
	}
	if(venceu == 0){
		printf("\nVocê ganhou.\n");

	} else {
		printf("\nVocê perdeu.\n");

	}
}

int main(){

	srand(time(NULL));
	
	int modo;

	do{
		printf("(1) Fácil\n(2) Médio\n(3) Difícil\n\nSelecione uma dificuldade: ");
		scanf("%i", &modo);
	}while(!(modo > 0 && modo < 4));

	iniciaJogo(modo); 

}
