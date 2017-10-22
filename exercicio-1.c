#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
//----------------------------------
typedef struct {
  int dia, mes, ano;
} data;  
typedef struct {
  int numero;
  char nome[30];
  float saldo;
  data d;
} conta;
//----------------------------------
void menu (char *opcao) {
  printf ("\n\n--------------------------------------------------------");   
  printf ("\n M E N U");     
  printf ("\n[1] - Cadastra cliente");
  printf ("\n[2] - Mostra todos clientes");
  printf ("\n[3] - Procura determinado cliente pelo numero da conta");
  printf ("\n[4] - Sair");
  printf ("\nopcao --> ");
  do {
    *opcao = getch();
  } while (*opcao < '1' || *opcao > '4'); 
  printf ("%c",*opcao);   
  printf ("\n--------------------------------------------------------\n");   
}  
//----------------------------------
void cadastra (char nomearq[]) {
  conta reg;
  char resp;
  FILE *arquivo;
  if ((arquivo = fopen(nomearq, "r+b")) == NULL)
    if ((arquivo = fopen(nomearq, "wb")) == NULL) {               
      printf("\n Erro de abertura de arquivo");
      return;
    }
  fseek (arquivo,0,SEEK_END);  
  do {
    printf("\n\n Numero da conta: ");
    scanf ("%d",&reg.numero);
    printf(" Nome do cliente: ");
    fflush (stdin);
    gets(reg.nome);
    printf(" Saldo da conta: ");
    scanf ("%f",&reg.saldo);
    printf(" Data da ultima operacao: ");
    scanf ("%d %d %d",&reg.d.dia,&reg.d.mes,&reg.d.ano);
    fwrite(&reg, sizeof(reg), 1, arquivo);
    printf("\n Adicionar outro cliente (s/n)?: ");
    do {
      resp = toupper(getch());
    } while (resp != 'S' && resp != 'N');
  } while (resp == 'S');
  fclose (arquivo);
}
//----------------------------------
void mostra (char nomearq[]) {
  conta reg;
  FILE *arquivo;
  if ((arquivo = fopen(nomearq, "rb")) == NULL) {
    printf("\n Erro de abertura de arquivo");
    return;
  }
  while (fread(&reg, sizeof(reg), 1, arquivo) == 1) {
    printf("\n\n Numero da conta: %d",reg.numero);
    printf("\n Nome do cliente: %s",reg.nome);
    printf("\n Saldo da conta: R$%8.2f     ",reg.saldo);
    printf("Data da ultima operacao: %d/%d/%d",reg.d.dia,reg.d.mes,reg.d.ano);
  } 
  getch();
}
//----------------------------------
void procura (char nomearq[]) {
  conta reg;
  FILE *arquivo;
  int num_conta, achou = 0;
  if ((arquivo = fopen(nomearq, "rb")) == NULL) {
    printf("\n Erro de abertura de arquivo");
    return;
  }      
  printf ("\nNumero da conta a ser consultada: ");
  scanf ("%d",&num_conta);
  while (fread(&reg, sizeof(reg), 1, arquivo) == 1) 
    if (reg.numero == num_conta) {
      printf("\n\n Numero da conta: %d",reg.numero);
      printf("\n Nome do cliente: %s",reg.nome);
      printf("\n Saldo da conta: R$%8.2f     ",reg.saldo);
      printf("Data da ultima operacao: %d/%d/%d",reg.d.dia,reg.d.mes,reg.d.ano);
      achou = 1;
    }
  if (!achou) 
    printf ("Conta %d nao cadastrada.",num_conta); 
  getch();
}
//----------------------------------
int main() {
  char opcao, nome_arquivo[15];
  printf ("Nome do arquivo a ser manipulado: ");
  gets (nome_arquivo);
  do {
    menu(&opcao);
    switch (opcao) {
      case '1': cadastra(nome_arquivo);
                break;
      case '2': mostra (nome_arquivo);
                break;
      case '3': procura (nome_arquivo);
    }
  } while (opcao != '4');       
}
