#ifndef _FUNCOESBUSCA_H
#define _FUNCOESBUSCA_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void check ( char * letra, char other){ // Transforma letras maiusculas em minusculas para comparar.
	if (isupper(other))	*letra = tolower(other);
	else *letra = other;
}


int verticalReversa(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	 for(j = 0; j < colunaMax;j++){
	 	
		 for(i = linhaMax-1; i >= 0;i--){
			
			if(tolower(bp[i][j]) == palavra[indWord])
			{
				if(indWord == 0){
					*pI = i;
					*pJ = j;
				}
				existWord++;
				indWord++;
			}else{
				if(tolower(bp[i][j]) != palavra[0]){
					indWord = 0;
					existWord = 0;  
				}else{
				     *pI = i;
					 *pJ = j;
				}
			}
				
			if(sizeWord == existWord){
				
				for(cont = 0; cont < sizeWord; cont++)
				{
					bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
					*pI -= 1;
				}
				
				strcpy(direcao,"VR");
				return 1;
			}
		  }
		}
		
	return 0;
}

int verticalDireta(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{	
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	for(j = 0; j < colunaMax;j++)
	{
			for(i = 0; i < linhaMax;i++)
			{
				if(tolower(bp[i][j]) == palavra[indWord])
				{
					if(indWord == 0){
						*pI = i;
						*pJ = j;
					}
					existWord++;
					indWord++;
				}else{
					if(tolower(bp[i][j]) != palavra[0]){
						indWord = 0;
						existWord = 0;  
					}else{
						*pI = i;
						*pJ = j;
					}
				}
		
				if(sizeWord == existWord){
					for(cont = 0; cont < sizeWord; cont++)
					{
						bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
						*pI += 1;
					}
					strcpy(direcao,"VD");
					return 1;
				}
			}
		}
	
	return 0;
}

int horizontalDireta(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	/*BUSCA HORIZONTAL DIRETA*/
	for(i = 0; i < linhaMax;i++)
	{
		for(j = 0; j < colunaMax;j++)
		{
			if(tolower(bp[i][j]) == palavra[indWord])
			{
				//guarda a posição da primeira letra dentro da tabela
				if(indWord == 0){
					*pI = i;
					*pJ = j;
				}
				existWord++;
				indWord++;
			}else{
				if(tolower(bp[i][j]) != palavra[0]){
					indWord = 0;
					existWord = 0;  
				}else{
				     *pI = i;
					 *pJ = j;
				}
			}
		
			if(sizeWord == existWord){
				for(cont = 0; cont < sizeWord; cont++)
			    {
					bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
					*pJ += 1;
				}
				strcpy(direcao,"HD");
				return 1;
			}
	    }
	 }
	 
	return 0;
}

int horizontalReversa(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	for(i = 0; i < linhaMax;i++)
	 {
		for(j = colunaMax-1; j >= 0;j--)
	    {
			if(tolower(bp[i][j]) == palavra[indWord])
			{
				if(indWord == 0){
					*pI = i;
					*pJ = j;
				}
				existWord++;
				indWord++;
			}else{
				/*Se a primeira letra da palavra recebida for diferente da letra da tabela reinicie os parametros*/
				if(tolower(bp[i][j]) != palavra[0]){
					indWord = 0;
					existWord = 0;  
				}else{
				     *pI = i;
					 *pJ = j;
				}
			}
			/*se encontrou a palavra saia do loop*/	
			if(sizeWord == existWord){
				for(cont = 0; cont < sizeWord; cont++)
				{
					bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
					*pJ -= 1;
				}
				strcpy(direcao,"HR");
				return 1;
			}
		  }
		}
}

int diagonalAcimaDireita(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{	
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	for(j = 0; j < colunaMax;j++)
	{
		for(i = 0; i < linhaMax;i++)
		{
			if (tolower(bp[i][j]) == palavra[0])
			{
				*pI = i;
				*pJ = j;
				if (palavra[1] == tolower(bp[i - 1][j + 1]))
				{
					for (indWord = 0; indWord < sizeWord; indWord++){
						if (palavra[indWord] != tolower(bp[i - indWord][j + indWord])){
							indWord = 0;
							existWord = 0;
							break;
						}else{
							existWord++;
						}
					}
				}
			}
			if(sizeWord == existWord){
				for(cont = 0; cont < sizeWord; cont++)
				{
					*pI -= cont;
					*pJ += cont;
					bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
				}
				strcpy(direcao,"DAD");
				return 1;
			}
		}
	}
	
	return 0;
}

int diagonalAcimaEsquerda(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{	
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	for(j = 0; j < colunaMax;j++)
	{
		for(i = 0; i < linhaMax;i++)
		{
			if (tolower(bp[i][j]) == palavra[0]) 
			{
				*pI = i;
				*pJ = j;
				if (palavra[1] == tolower(bp[i - 1][j + 1]))
				{
					for (indWord = 0; indWord < sizeWord; indWord++){
						if (palavra[indWord] != tolower(bp[i - indWord][j - indWord])){
							indWord = 0;
							existWord = 0;
							break;
						}else{
							existWord++;
						}
					}
				}
			}
			if(sizeWord == existWord){
				for(cont = 0; cont < sizeWord; cont++)
				{
					*pI -= cont;
					*pJ -= cont;
					bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
				}
				strcpy(direcao,"DAE");
				return 1;
			}
		}
	}
	
	return 0;
}

int diagonalAbaixoDireita(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{	
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	for(j = 0; j < colunaMax;j++)
	{
		for(i = 0; i < linhaMax;i++)
		{
			if (tolower(bp[i][j]) == palavra[0]) 
			{
				*pI = i;
				*pJ = j;
				if (palavra[1] == tolower(bp[i - 1][j + 1]))
				{
					for (indWord = 0; indWord < sizeWord; indWord++){
						if (palavra[indWord] != tolower(bp[i + indWord][j + indWord])){
							indWord = 0;
							existWord = 0;
							break;
						}else{
							existWord++;
						}
					}
				}
			}
			if(sizeWord == existWord){
				for(cont = 0; cont < sizeWord; cont++)
				{
					*pI += cont;
					*pJ += cont;
					bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
				}
				strcpy(direcao,"DaD");
				return 1;
			}
		}
	}
	
	return 0;
}

int diagonalAbaixoEsquerda(char **bp, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{	
	int i,j,cont,sizeWord, existWord = 0, indWord = 0;
	//inicializa
	sizeWord = strlen(palavra);
	
	for(j = 0; j < colunaMax;j++)
	{
		for(i = 0; i < linhaMax;i++)
		{
			if (tolower(bp[i][j]) == palavra[0]) 
			{
				*pI = i;
				*pJ = j;
				if (palavra[1] == tolower(bp[i - 1][j + 1]))
				{
					for (indWord = 0; indWord < sizeWord; indWord++){
						if (palavra[indWord] != tolower(bp[i + indWord][j - indWord])){
							indWord = 0;
							existWord = 0;
							break;
						}else{
						existWord++;
						}
					}
				}
			}
			if(sizeWord == existWord){
				for(cont = 0; cont < sizeWord; cont++)
				{
					*pI += cont;
					*pJ -= cont;
					bp[*pI][*pJ] = toupper(bp[*pI][*pJ]);
				}
				strcpy(direcao,"DaE");
				return 1;
			}
		}
	}
	
	return 0;
}

int buscaPalavra(char **matriz, char palavra[], int *pI, int *pJ, char *direcao, int linhaMax, int colunaMax)
{
	int found = horizontalDireta(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	if(!found) found = horizontalReversa(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	if(!found) found = verticalDireta(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	if(!found) found = verticalReversa(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	if(!found) found = diagonalAcimaDireita(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	if(!found) found = diagonalAcimaEsquerda(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	if(!found) found = diagonalAbaixoDireita(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	if(!found) found = diagonalAbaixoEsquerda(matriz, palavra,pI,pJ,direcao,linhaMax,colunaMax);
	
	return found;
}
#endif

