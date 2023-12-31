// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br -

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "JoaoNascimento-20231160040.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}


DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

// Declaração de funções \\

int bissexto(int ano);

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  DataQuebrada date;
  
  //quebrar a string data em strings sDia, sMes, sAno
  //DataQuebrada dataQuebrada = quebraData(data);
  date=quebraData(data);

  if(date.valido!=0)
  {
    if(date.iAno<100 && date.iAno>=0)
    {
      date.iAno+=2000;
    } 
    
    if(date.iAno<=2024 && date.iAno>=1900)
    {
      if(date.iMes>=1 && date.iMes<=12)
      {
        if(date.iDia<=meses[date.iMes-1] && date.iDia>0 || (date.iDia<=meses[date.iMes-1]+1 && date.iMes==2 && bissexto(date.iAno) && date.iDia>0))
        {
          return 1;
        }  
      }    
    }
  }
  
  //if (dataQuebrada.valido == 0) return 0;
  //printf("%s\n", data);
  return 0;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
  
    DataQuebrada inicial,final;
    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
      inicial = quebraData(datainicial);
      final = quebraData(datafinal);

      if(final.iAno<inicial.iAno || final.iAno==inicial.iAno && final.iMes<inicial.iMes || final.iAno==inicial.iAno && final.iMes==inicial.iMes && final.iDia<inicial.iDia)
      {
        dma.retorno=4;
        return dma;
      }
        //calcule a distancia entre as datas
      dma.qtdAnos=0;
      dma.qtdDias=0;
      dma.qtdMeses=0;
      int meses[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
      int j;
      int tdia,tmes=inicial.iMes,tano=inicial.iAno;

        //calculo de meses
      for(j=0;tmes<=final.iMes && tano==final.iAno ||tano<final.iAno;j++,tmes++)
      {
        if(bissexto(tano)==1)
          meses[1]=29;
        else
          meses[1]=28;

        dma.qtdDias+=meses[tmes-1];
        
        if(tmes==12)
        {
          tmes=0;
          tano++;
        }
        
      }
        
        
        dma.qtdDias=dma.qtdDias-inicial.iDia;
        dma.qtdDias=dma.qtdDias-(meses[final.iMes-1]-final.iDia);

//printf("%d\n",dma.qtdDias);
        //printf("%d\n",dma.qtdMeses);
        
        tmes=inicial.iMes;
        tano=inicial.iAno;
        
      for(j=0;(tmes<final.iMes && tano==final.iAno) ||tano<final.iAno;j++,tmes++)
      {
        if(bissexto(tano)==1)
          meses[1]=29;
        else
          meses[1]=28;

        if(dma.qtdDias-meses[tmes-1]>=0)
        {
          dma.qtdDias-=meses[tmes-1];
          dma.qtdMeses++;
        }
        if(dma.qtdMeses==12)
        {
          dma.qtdAnos++;
          dma.qtdMeses=0;
        }
        
        if(tmes==12)
        {
          tmes=0;
          tano++;
        }
      }
        
      //printf("%d\n",dma.qtdDias);
      //printf("%d\n",dma.qtdMeses);
        
      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int i=0;
  
    if(isCaseSensitive==0)
    {
      char auxtext;
      
      while(texto[i]!='\0')
      {
        auxtext=texto[i];
        
        if(auxtext>='a' && auxtext<='z' && c>='A' && c<='Z')
          auxtext=(auxtext-32);
        else if(auxtext>='A' && auxtext<='Z' && c>='a' && c<='z')
          auxtext=(auxtext+32);

        if(c==auxtext)
          qtdOcorrencias++;
        
        i++;
      }
    } else if(isCaseSensitive==1)
    {
      while(texto[i]!='\0')
      {

        if(c==texto[i])
          qtdOcorrencias++;
        
        i++;
      }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i=0;
    int j=0;
    int k=0,l=0,m=0;;
    int tam=0;
    int iposicoes=0;

    while(strBusca[tam]!='\0')
    {
      tam+=1;
    }
    
    while(strTexto[i]!='\0')
    {
      j=0;
      if(strTexto[i]<0)
      {
        k++;
      }
      
      for(j=0;strTexto[i+j]==strBusca[j] && strTexto[i+j]!='\0';j++){
        if(strTexto[i+j]<0)
        {
          l++;
        }
      }
      if(strTexto[i+j-1]=='\0')
        j-=2;
      
      k=k+l;
      
      m=k/2;
      
      l=0;
      if(j==tam)
      {
        posicoes[iposicoes]=i+1-m;
        posicoes[iposicoes+1]=i+j-m;
        iposicoes+=2;
        qtdOcorrencias++;
        i=i+j-1;
      }
      
      i++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int auxnum;
  
  int i;
  for(i=1;num/(i*10)>0;i=i*10);

  auxnum=num/i;
  num=num-((num/i)*i);
  i=i/10;
  
  for(int j=10;i>0;j=j*10)
  {
    auxnum+= (num/i)*j;
    num=num-(num/i)*i;
    i=i/10;
  }

  num=auxnum;
  
  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
  int qtdOcorrencias=0;
  int i;
  int num=numerobase;
  int num2=numerobusca;

  for(i=0;numerobusca>0;i++,numerobusca=numerobusca/10);
  int vetor1[i+1];
  for(i=0;numerobase>0;i++,numerobase=numerobase/10);
  int vetor2[i+1];

  numerobase=num;
  numerobusca=num2;
  for(i=0;numerobase>0;i++,numerobase=numerobase/10)
  {    
    vetor2[i]=numerobase%10;
    //printf("%d",vetor2[i]);
  }

  for(i=0;numerobusca>0;i++,numerobusca=numerobusca/10)
  {  
    
    vetor1[i]=numerobusca%10;
    //printf("%d",vetor1[i]);
  }
  int j=0;
        
  for(i=0;num>0;i++,num=num/10)
  {
    
    for(j=0;vetor2[i+j]==vetor1[j] && j!=(sizeof(vetor1)/sizeof(vetor1[0]))-1;j++);

    if(j==(sizeof(vetor1)/sizeof(vetor1[0]))-1)
    {
      qtdOcorrencias++;
      i=i+j-1;
    }  
  }

  return qtdOcorrencias;
}

// Funções \\

int bissexto(int ano) {
    if (ano % 4 != 0) {
        return 0;
    } else if (ano % 100 != 0) {
        return 1;
    } else if (ano % 400 != 0) {
        return 0;
    } else {
        return 1;
    }
}