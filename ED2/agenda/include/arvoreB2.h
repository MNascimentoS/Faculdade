#ifndef ARVORE_B_H
#define ARVORE_B_H

/* Autores: José Diôgo e Fernando Maia, Wellington Correia, Mateus Nascimento
 * 
 * 
 **/
#include <string.h>
#include "contato.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define ORDEM 4//ordem da arvoreB
#define FALSE 0
#define TRUE  1
#define agendaPorTel "_agendaPortelefone.dat"


int cont = -1, count = 0; int flag = 0;

typedef struct pagina *Apontador;//definicao dos ponteiros para as proximas paginas

typedef struct pagina//ou nó
{
  int numChaves;//Total de chaves na página
  Contato contato[ORDEM*2];//chaves
  int pageNum;//numero da pagina
  int num;
  Apontador apontador[(ORDEM*2)+1];//total de ponteiros
} Pagina;


void ins2(Contato contato, Apontador apontador, int *cresceu, Contato *contatoRetorno, Apontador *apontadorRetorno);
void saveAux2(Apontador p, int Nivel);
void insereNaPagina2(Apontador apontador, Contato contato,  Apontador apDir);
void insere2(Contato contato, Apontador *apontador);
void salvar2(Apontador page, Contato Reg[]);
int file_exists2(const char *filename);
void em_ordem2(Apontador raiz);
void buscaInteligente2(Contato Reg, Apontador Ap);
void Busca2(Contato Reg, Apontador Ap);
void buscainFile2(Contato Reg, Apontador pag);
void carregarArvore2(Apontador *apontador);
void buscainFileSmart2(Contato Reg, Apontador pag);
void buscaEmail2(Contato Reg, Apontador Ap);
void buscainFileSmartEmail2(Contato Reg, Apontador pag);

//Carrega os registros na arvore
void carregarArvore2(Apontador *apontador)
{
	Contato c;
	if(file_exists2(agendaPorTel))
	{
		FILE *f = fopen(agendaPorTel, "rb");
	    //verifica todos os registros
		while(fread(&c, sizeof(Contato), 1, f) == 1)
		{
			//enquanto houver registros, carregue-os
			if(strcmp(c.nome,"") != 0){
				insere2(c, apontador);
			} 
		}
	}else return;
}

void Busca2(Contato Reg, Apontador Ap){
  int i;

  if (Ap == NULL)
  {
    printf("\n Contato nao encontrado: %s\n", Reg.telCelular);
    return;
  }
  i = 1;
  while (i < Ap->numChaves && strcmp(Reg.telCelular, Ap->contato[i - 1].telCelular) > 0)
    i++;
  if (strcmp(Reg.telCelular,Ap->contato[i - 1].telCelular) == 0)
  {
    buscainFile2(Ap->contato[i-1],Ap);
    return;
  }
  if (strcmp(Reg.telCelular,Ap->contato[i - 1].telCelular) < 0)
    Busca2(Reg, Ap->apontador[i-1]);
  else
    Busca2(Reg, Ap->apontador[i]);
}

void buscainFile2(Contato Reg, Apontador pag)
{
    Contato reg[2*ORDEM];
    int i;
    FILE *arq = fopen(agendaPorTel,"rb");
    if (arq == NULL)
		exit(1);
    fseek(arq, pag->pageNum*(2*ORDEM*sizeof(Contato)), SEEK_SET);
    fread(reg, (2*ORDEM*sizeof(Contato)),1,arq);
    fclose(arq);
    for(i = 0; i < 2*ORDEM; i++){
        if (strcmp(Reg.telCelular,reg[i].telCelular) == 0 && strcmp(Reg.telCelular,"") != 0)
        { 
		 printf("\n  Nome: %s\n", reg[i].nome);
         printf("  CPF: %s\n", reg[i].cpf);
         printf("  Data de nascimento: %d/%d/%d\n", reg[i].dataNascimento.dia, reg[i].dataNascimento.mes, reg[i].dataNascimento.ano);
         printf("  Profissão: %s\n", reg[i].profissao);
         printf("  Email: %s\n", reg[i].email);
         printf("  Telefone Celular: %s\n",reg[i].telCelular);
         printf("  Telefone Comercial: %s\n",reg[i].telComercial);
         printf("  Telefone Residencial: %s\n\n",reg[i].telResidencial);
		}
    }
}

void buscaInteligente2(Contato Reg, Apontador Ap){
  int i;

  if (Ap == NULL)
  {
    printf("\n Contato nao encontrado: %s\n", Reg.telCelular);
    return;
  }
  i = 1;
  while (i < Ap->numChaves && strstr(Ap->contato[i - 1].telCelular, Reg.telCelular) != 0)
    i++;
  if (strstr(Ap->contato[i - 1].telCelular, Reg.telCelular) != 0)
  {
	  
    buscainFileSmart2(Reg,Ap);
    return;
  }
  if (strstr(Ap->contato[i - 1].nome, Reg.telCelular) != 0)
    buscainFileSmart2(Reg, Ap->apontador[i-1]);
  else
    buscaInteligente2(Reg, Ap->apontador[i]);
}

void buscaEmail2(Contato Reg, Apontador Ap){
  int i;

  if (Ap == NULL)
  {
    printf("\n Contato nao encontrado: %s\n", Reg.email);
    return;
  }
  i = 1;
  while (i < Ap->numChaves && strcmp(Ap->contato[i - 1].email, Reg.email) != 0)
    i++;
  if (strcmp(Ap->contato[i - 1].email, Reg.email) == 0)
  {
    buscainFileSmartEmail2(Reg,Ap);
    return;
  }
  if (strcmp(Ap->contato[i - 1].email, Reg.email) != 0)
    buscaEmail2(Reg, Ap->apontador[i-1]); //Possível erro
  else
    buscaEmail2(Reg, Ap->apontador[i]);
}

void buscainFileSmartEmail2(Contato Reg, Apontador pag)
{
    Contato reg[2*ORDEM];
    int i;
    FILE *arq = fopen(agendaPorTel,"rb");
    if (arq == NULL)
		exit(1);
    fseek(arq, pag->pageNum*(2*ORDEM*sizeof(Contato)), SEEK_SET);
    fread(reg, (2*ORDEM*sizeof(Contato)),1,arq);
    fclose(arq);
    for(i = 0; i < 2*ORDEM; i++){
        if(strcmp(reg[i].email, Reg.email) == 0 && strcmp(reg[i].nome,"") != 0)
        { 
		 printf("\n  Nome: %s\n\n", reg[i].nome);
         printf("  CPF: %s\n", reg[i].cpf);
         printf("  Data de nascimento: %d/%d/%d\n", reg[i].dataNascimento.dia, reg[i].dataNascimento.mes, reg[i].dataNascimento.ano);
         printf("  Profissão: %s\n", reg[i].profissao);
         printf("  Email: %s\n", reg[i].email);
         printf("  Telefone Celular: %s\n",reg[i].telCelular);
         printf("  Telefone Comercial: %s\n",reg[i].telComercial);
         printf("  Telefone Residencial: %s\n\n",reg[i].telResidencial);
		}
    }
}


void listarTodosComTelTrabalho2(Apontador raiz)
{
   int i;
   
   if(raiz != NULL)
   {
     for (i = 0; i < raiz->numChaves; i++)
      {
        em_ordem2(raiz->apontador[i]);
        //se tiver numero de contato exiba
        if(strcmp(raiz->contato[i].telComercial,"0") != 0)
        {
		   printf("\n  Nome: %s\n", raiz->contato[i].nome);
		   printf("  CPF: %s\n", raiz->contato[i].cpf);
		   printf("  Data de nascimento: %d/%d/%d\n", raiz->contato[i].dataNascimento.dia, raiz->contato[i].dataNascimento.mes, raiz->contato[i].dataNascimento.ano);
		   printf("  Profissao: %s\n", raiz->contato[i].profissao);
           printf("  Email: %s\n", raiz->contato[i].email);
           printf("  Telefone Celular: %s\n",raiz->contato[i].telCelular);
           printf("  Telefone Comercial: %s\n",raiz->contato[i].telComercial);
           printf("  Telefone Residencial: %s\n",raiz->contato[i].telResidencial); 
           printf("\n");
	    }
      }
     em_ordem2(raiz->apontador[i]);
    }	
}

void buscainFileSmart2(Contato Reg, Apontador pag)
{
    Contato reg[2*ORDEM];
    int i;
    FILE *arq = fopen(agendaPorTel,"rb");
    if (arq == NULL)
		exit(1);
    fseek(arq, pag->pageNum*(2*ORDEM*sizeof(Contato)), SEEK_SET);
    fread(reg, (2*ORDEM*sizeof(Contato)),1,arq);
    fclose(arq);
    for(i = 0; i < 2*ORDEM; i++){
        if(strstr(reg[i].telCelular, Reg.telCelular) != 0 && strcmp(reg[i].telCelular,"") != 0)
        { 
		 printf("\n  Nome: %s\n", reg[i].nome);
         printf("  CPF: %s\n", reg[i].cpf);
         printf("  Data de nascimento: %d/%d/%d\n", reg[i].dataNascimento.dia, reg[i].dataNascimento.mes, reg[i].dataNascimento.ano);
         printf("  Profissão: %s\n", reg[i].profissao);
         printf("  Email: %s\n", reg[i].email);
         printf("  Telefone Celular: %s\n",reg[i].telCelular);
         printf("  Telefone Comercial: %s\n",reg[i].telComercial);
         printf("  Telefone Residencial: %s\n\n",reg[i].telResidencial);
		}
    }
}

void em_ordem2(Apontador raiz){
  int i;
  if (raiz != NULL)
   {
     for (i = 0; i < raiz->numChaves; i++)
      {
        em_ordem2(raiz->apontador[i]);
        printf("\n  Nome: %s\n", raiz->contato[i].nome);
        printf("  CPF: %s\n", raiz->contato[i].cpf);
        printf("  Data de nascimento: %d/%d/%d\n", raiz->contato[i].dataNascimento.dia, raiz->contato[i].dataNascimento.mes, raiz->contato[i].dataNascimento.ano);
        printf("  Profissao: %s\n", raiz->contato[i].profissao);
        printf("  Email: %s\n", raiz->contato[i].email);
        printf("  Telefone Celular: %s\n",raiz->contato[i].telCelular);
        printf("  Telefone Comercial: %s\n",raiz->contato[i].telComercial);
        printf("  Telefone Residencial: %s\n",raiz->contato[i].telResidencial);
        
        printf("\n");
      }
     em_ordem2(raiz->apontador[i]);
    }
}

//inicializa o dicionario
typedef Apontador TipoDicionario;
void inicializa2(TipoDicionario *dicionario)
{
	*dicionario = NULL;
	//carrega a arvore
	carregarArvore2(dicionario);
}
/*insere na página*/
void insereNaPagina2(Apontador apontador, Contato contato,  Apontador apDir)
{
	short naoAchouPosicao;
	int k;
	k = apontador->numChaves;//total de chaves 
	naoAchouPosicao = (k > 0);//verifica se já existe chaves 
	//se já existir chaves, procure a melhor posicao para salvar
	while(naoAchouPosicao)
	{
		if(strcmp(contato.telCelular, apontador->contato[k-1].telCelular) > 0)//compara com as chaves pertencentes a pagina, pelo nome caso seja um nome maior  faca a atribuicao posterior
		{
			naoAchouPosicao = FALSE;
			break;
		}
		apontador->contato[k] = apontador->contato[k-1];//se ainda nao encontrou, verifique o proximo contato
		apontador->apontador[k+1] = apontador->apontador[k];
		k--;
		if(k < 1) naoAchouPosicao = FALSE;//se já percorreu todas as posicoes, saia
	}
	apontador->contato[k] = contato;
	apontador->apontador[k+1] = apDir;
	apontador->numChaves++;
}
/*Insere na árvore B*/
void insere2(Contato contato, Apontador *apontador)
{
	int cresceu;flag = 1;
	Contato contatoRetorno;
	Apontador apontadorRetorno;
	Apontador apontadorTemp;
	//insere na arvore
	ins2(contato, *apontador, &cresceu, &contatoRetorno, &apontadorRetorno);
	//se a arvore cresceu na altura pela raiz
	if(cresceu)
	{
		apontadorTemp = (Apontador) malloc(sizeof(Pagina));
		apontadorTemp->numChaves = 1;
		apontadorTemp->contato[0] = contatoRetorno;
		apontadorTemp->apontador[1] = apontadorRetorno;
		cont++; 
		apontadorTemp->pageNum = cont;
		apontadorTemp->apontador[0] = *apontador;
		*apontador = apontadorTemp;
	}
	
	//save in the file
	if(flag == 1) saveAux2(*apontador, 2*ORDEM);
}

//aux para insercao
void ins2(Contato contato, Apontador apontador, int *cresceu, Contato *contatoRetorno, Apontador *apontadorRetorno)
{
	Apontador apontadorTemp;
	Contato aux;
	int i, j;
	
	if(apontador == NULL)
	{
		*cresceu = 1;//a arvore cresceu da raiz
		*contatoRetorno = contato;
		*apontadorRetorno = NULL;
		return;
	}
	i = 1;
	while(i < apontador->numChaves && strcmp(contato.telCelular, apontador->contato[i-1].telCelular) > 0) i++; 

	//se as chaves forem iguais
	if(strcmp(contato.telCelular, apontador->contato[i-1].telCelular) == 0)
	{
		flag = 0;
		printf(" Já existe um contato com este nome. Verifique o nome do contato e tente novamente :(\n");
		return;
	}
	//se a letra for menor
	if(strcmp(contato.telCelular, apontador->contato[i-1].telCelular) < 0) ins2(contato, apontador->apontador[i-1], cresceu, contatoRetorno, apontadorRetorno);
	else ins2(contato, apontador->apontador[i], cresceu, contatoRetorno, apontadorRetorno);//caso maior
	
	//caso nao cresca
	if(!*cresceu) return;
	
	//verificando a ordem
	if(apontador->numChaves < 2*ORDEM)
	{
		//verifica se a pagina tem espaco
		insereNaPagina2(apontador, *contatoRetorno, *apontadorRetorno);
		*cresceu = 0;
		return;
	}
	
	//repartir *split - Pagina tem que ser dividida
	apontadorTemp = (Apontador) malloc(sizeof(Apontador));
	apontadorTemp->numChaves = 0;
	apontadorTemp->apontador[0] = NULL;
	cont++;
	apontadorTemp->pageNum = cont;
	
	if(i <= ORDEM + 1)
	{
		insereNaPagina2(apontadorTemp, apontador->contato[2*ORDEM -1], apontador->apontador[2*ORDEM]);
		apontador->numChaves--;
		insereNaPagina2(apontador, *contatoRetorno, *apontadorRetorno);
	}
	else
	{
		insereNaPagina2(apontadorTemp, *contatoRetorno, *apontadorRetorno);
	}
	
	for(j = ORDEM + 2; j <= 2*ORDEM; j++) insereNaPagina2(apontadorTemp, apontador->contato[j - 1], apontador->apontador[j]);

	apontador->numChaves = ORDEM;
	apontadorTemp->apontador[0] = apontador->apontador[ORDEM + 1]; 
	*contatoRetorno = apontador->contato[ORDEM];
	*apontadorRetorno = apontadorTemp;
	
	for(j = ORDEM; j < apontador->numChaves+2; j++){
		strcpy(aux.nome, "a");
		aux.rank = 0;
		apontador->contato[j] = aux;
	}
}

int file_exists2(const char *filename)
{
  FILE *arquivo;

  if((arquivo = fopen(filename, "rb")))
  {
    fclose(arquivo);
    return 1;
  }
  return 0;
}


void salvar2(Apontador page, Contato Reg[])
{
    FILE* arq;
    if (!file_exists2(agendaPorTel)){
        arq = fopen(agendaPorTel,"wb");
        if (arq == NULL)
            exit(1);
        fseek(arq, page->pageNum*(2*ORDEM*sizeof(Contato)), SEEK_SET);
        fwrite(Reg,(2*ORDEM*sizeof(Contato)),1,arq);
        fclose(arq);
    }

    else{
        arq = fopen(agendaPorTel,"r+b");
        if (arq == NULL)
            exit(1);
        fseek(arq, page->pageNum*(2*ORDEM*sizeof(Contato)), SEEK_SET);
        fwrite(Reg, 2*ORDEM*sizeof(Contato),1,arq);
        fclose(arq);
    }
}

void saveAux2(Apontador p, int Nivel)
{
  int i,j;

  if (p == NULL)
    return;
  for (i = 0; i < p->numChaves; i++)
    salvar2(p, p->contato);
  for (j = 0; j <= p->numChaves; j++)
    saveAux2(p->apontador[j], Nivel + 1);
}
//----------------------------------Remover------------------------------------
void salvarRemocao2(Apontador p)
{
    FILE* arq;
    int i;
    arq = fopen(agendaPorTel,"wb");
    if (arq == NULL)
         exit(1);
                  
    if(p != NULL)
    {
     for (i = 0; i < p->numChaves; i++)
      {
        salvarRemocao2(p->apontador[i]);
		fwrite(&p->contato[i],sizeof(Contato),1,arq);
      }
     salvarRemocao2(p->apontador[i]);
    }     
    fclose(arq);
}

void InsereNaPagina2(Apontador Ap, Contato Reg, Apontador ApDir){

  int k;
  int NaoAchouPosicao;

  k = Ap->numChaves;
  NaoAchouPosicao = k > 0;
  while (NaoAchouPosicao)
  {
    if (strcmp(Reg.nome,Ap->contato[k - 1].nome) == 0 || strcmp(Reg.cpf,Ap->contato[k - 1].nome) > 0)//Reg.chave >= Ap->contato[k - 1].chave)
    {
      NaoAchouPosicao = 0;
      break;
    }
	
    Ap->contato[k] = Ap->contato[k - 1];

    Ap->apontador[k + 1] = Ap->apontador[k];

    k--;
    if (k < 1)
      NaoAchouPosicao = 0;
  }
  Ap->contato[k] = Reg;
  Ap->apontador[k + 1] = ApDir;
  Ap->numChaves++;
}

void Reconstitui2(Apontador ApPag, Apontador ApPai, int PosPai, int *Diminuiu){
  Apontador Aux;
  int DispAux, j;

  if (PosPai < ApPai->numChaves) {  /* Aux = Pagina a direita de ApPag */
    Aux = ApPai->apontador[PosPai + 1];
    DispAux = (Aux->numChaves - ORDEM + 1) / 2;
    ApPag->contato[ApPag->numChaves] = ApPai->contato[PosPai];
    ApPag->apontador[ApPag->numChaves + 1] = Aux->apontador[0];
    ApPag->numChaves++;
    if (DispAux > 0) {  /* Existe folga: transfere de Aux para ApPag */
      for (j = 1; j < DispAux; j++)
        InsereNaPagina2(ApPag, Aux->contato[j - 1], Aux->apontador[j]);
      ApPai->contato[PosPai] = Aux->contato[DispAux - 1];
      Aux->numChaves -= DispAux;
      for (j = 0; j < Aux->numChaves; j++)
        Aux->contato[j] = Aux->contato[j + DispAux];
      for (j = 0; j <= Aux->numChaves; j++)
        Aux->apontador[j] = Aux->apontador[j + DispAux];
      *Diminuiu = 0;
    }
    else
    { /* Fusao: intercala Aux em ApPag e libera Aux */
      for (j = 1; j <= ORDEM; j++)
        InsereNaPagina2(ApPag, Aux->contato[j - 1], Aux->apontador[j]);
      free(Aux);
      for (j = PosPai + 1; j < ApPai->numChaves; j++)
      {   /* Preenche vazio em ApPai */
        ApPai->contato[j - 1] = ApPai->contato[j];
        ApPai->apontador[j] = ApPai->apontador[j + 1];
      }
      ApPai->numChaves--;
      if (ApPai->numChaves >= ORDEM)
        *Diminuiu = 0;
    }
  }
  else
  { /* Aux = Pagina a esquerda de ApPag */
    Aux = ApPai->apontador[PosPai - 1];
    DispAux = (Aux->numChaves - ORDEM + 1) / 2;
    for (j = ApPag->numChaves; j >= 1; j--)
      ApPag->contato[j] = ApPag->contato[j - 1];
    ApPag->contato[0] = ApPai->contato[PosPai - 1];
    for (j = ApPag->numChaves; j >= 0; j--)
      ApPag->apontador[j + 1] = ApPag->apontador[j];
    ApPag->numChaves++;
    if (DispAux > 0) {  /* Existe folga: transfere de Aux para ApPag */
      for (j = 1; j < DispAux; j++)
        InsereNaPagina2(ApPag, Aux->contato[Aux->numChaves - j], Aux->apontador[Aux->numChaves - j + 1]);
      ApPag->apontador[0] = Aux->apontador[Aux->numChaves - DispAux + 1];
      ApPai->contato[PosPai - 1] = Aux->contato[Aux->numChaves - DispAux];
      Aux->numChaves -= DispAux;
      *Diminuiu = 0;
    }
    else
    {  /* Fusao: intercala ApPag em Aux e libera ApPag */
      for (j = 1; j <= ORDEM; j++)
        InsereNaPagina2(Aux, ApPag->contato[j - 1], ApPag->apontador[j]);
      free(ApPag);
      ApPai->numChaves--;
      if (ApPai->numChaves >= ORDEM)
        *Diminuiu = 0;
    }
  }
}  /* Reconstitui */

void Antecessor2(Apontador Ap, int Ind, Apontador ApPai, int *Diminuiu){
  if (ApPai->apontador[ApPai->numChaves] != NULL)
  {
    Antecessor2(Ap, Ind, ApPai->apontador[ApPai->numChaves], Diminuiu);
    if (*Diminuiu)
      Reconstitui2(ApPai->apontador[ApPai->numChaves], ApPai, ApPai->numChaves, Diminuiu);
    return;
  }
  Ap->contato[Ind - 1] = ApPai->contato[ApPai->numChaves - 1];
  ApPai->numChaves--;
  *Diminuiu = ApPai->numChaves < ORDEM;
}  /* Antecessor */

void Ret2(char Ch[], Apontador *Ap, int *Diminuiu, int *removerArquivo){
  int Ind, j;
  Apontador WITH;
  Contato Reg;

  if (*Ap == NULL)
  {
    printf("chave nao encontrada: %s\n", Ch);
    *removerArquivo = 0;
    *Diminuiu = 0;
    return;
  }
  WITH = *Ap;
  Ind = 1;
  while (Ind < WITH->numChaves && strcmp(Ch, WITH->contato[Ind - 1].telCelular) > 0)//Ch > WITH->contato[Ind - 1].chave) 
    Ind++;
  if (strcmp(Ch, WITH->contato[Ind - 1].telCelular) == 0)//Ch == WITH->contato[Ind - 1].chave)
  {
    strcpy(Reg.telCelular," ");
    WITH->contato[Ind -1] = Reg;
   
    if (WITH->apontador[Ind - 1] == NULL) {  /* Pagina folha */
      WITH->numChaves--;
      *Diminuiu = WITH->numChaves < ORDEM;
      for (j = Ind; j <= WITH->numChaves; j++)
      {
        WITH->contato[j - 1] = WITH->contato[j];
        WITH->apontador[j] = WITH->apontador[j + 1];
      }
      return;
    }
    Antecessor2(*Ap, Ind, WITH->apontador[Ind - 1], Diminuiu);
    if (*Diminuiu)
      Reconstitui2(WITH->apontador[Ind - 1], *Ap, Ind - 1, Diminuiu);
    return;
  }
  if (strcmp(Ch,WITH->contato[Ind - 1].nome)  > 0)//Ch > WITH->contato[Ind - 1].chave)
    Ind++;
  Ret2(Ch, &WITH->apontador[Ind - 1], Diminuiu, removerArquivo);
  if (*Diminuiu)
    Reconstitui2(WITH->apontador[Ind - 1], *Ap, Ind - 1, Diminuiu);
}  /* Ret */

void Retira2(char *Ch, Apontador *Ap){
  int Diminuiu, removerArquivo;
  Apontador Aux;
  removerArquivo = 1;

  Ret2(Ch, Ap, &Diminuiu, &removerArquivo);
  if (Diminuiu && (*Ap)->numChaves == 0) { /* Arvore diminui na altura */
    Aux = *Ap;
    *Ap = Aux->apontador[0];
    free(Aux);
  }
  
  if(removerArquivo)
  {
	 salvarRemocao2(*Ap);
  }
}  /* Retira */

#endif



