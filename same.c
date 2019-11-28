#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include "./filaPonteiro.c"

void imprime(uint32_t matrix[][16]){
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
              } else {
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
            	} else {
            		printf("   ");
          		}
        	}
    	}
    	printf("\033[0m\n");
	}
}
void geraMatriz(uint32_t matrix[][16]){
	for(int i = 0; i < 12; i++){
        for(int j = 0; j < 16; j++){
            int a = randombytes_uniform(4);
            while(a == 0){
              a = randombytes_uniform(4);
            }
            matrix[i][j] = a;
        }
    }
}

void buscaLargura(uint32_t matrix[][16], ixj entrada){
	Fila q;
	inicializaFila(&q);
	insereFila(&q, entrada);
	
	uint32_t corEntrada = matrix[entrada.i][entrada.j];
	if(corEntrada != 0){
		while(!filaVazia(&q)){
			ixj no;
			ixj noVizinho;
			removeFila(&q, &no);
			if(no.i+1 < 12 && corEntrada == matrix[no.i+1][no.j]){
				matrix[no.i+1][no.j] = 0;
				noVizinho.i = no.i + 1;
				noVizinho.j = no.j;
				insereFila(&q, noVizinho);
			}
			if(no.i-1 >= 0 && corEntrada == matrix[no.i-1][no.j]){
				matrix[no.i-1][no.j] = 0;
				noVizinho.i = no.i - 1;
				noVizinho.j = no.j;
				insereFila(&q, noVizinho);
			}
			if(no.j+1 < 16 && corEntrada == matrix[no.i][no.j+1]){
				matrix[no.i][no.j+1] = 0;
				noVizinho.i = no.i;
				noVizinho.j = no.j + 1;
				insereFila(&q, noVizinho);
			}
			if(no.j-1 >= 0 && corEntrada == matrix[no.i][no.j-1]){
				matrix[no.i][no.j-1] = 0;
				noVizinho.i = no.i;
				noVizinho.j = no.j - 1;
				insereFila(&q, noVizinho);
			}
			if(!filaVazia(&q)){
				matrix[no.i][no.j] = 0;
			}
		}
	}
}

void deslocaBaixo(u_int32_t matrix[][16]){
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


void deslocaLado(u_int32_t matrix[][16]){
	for(int col = 0; col < 16; col++){
		for(int i = col; i < 16; i++){
			if(matrix[11][col] == 0 && col+1 < 16 && matrix[11][i] != 0){
				for(int lin = 11; lin >= 0; lin--){
					matrix[lin][col] = matrix[lin][i];
					matrix[lin][i] = 0;
				}
			}
		}
		

	}
}


int main(){
	//inicializa o libsodium
    if(sodium_init() == -1){
        return -1;
    }

    uint32_t matrix[12][16];
    ixj indice;


    geraMatriz(matrix);    
    imprime(matrix);
    
	while(1){
		printf("\nEscolha um indice: ");
		scanf("%i,%i", &indice.i, &indice.j);

		buscaLargura(matrix, indice);
		deslocaBaixo(matrix);
		deslocaLado(matrix);
		imprime(matrix);
	}
    
}
