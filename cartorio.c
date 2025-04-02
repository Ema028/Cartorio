#include <stdio.h>
#include <stdlib.h> 
#include <locale.h> 
#include <string.h>
#include "input.h" // biblioteca local

void registrar(void);
void consultar(void);
void deletar(void);
int login(char* string);

int main()
{
    printf("Digite a senha do administrador para acessar o painel");
    char* senha = get_string();
    
    if(login(senha) == 1)
    {
        return 1;
    }
    
    while(1)
    {
      system("clear");

      setlocale(LC_ALL,"portuguese"); 

      printf("Selecione um item do menu:\n\n");
      printf("\t1-Registrar nomes\n\t2-Consultar nomes\n\t3-Deletar nomes\n\t4-Sair do sistema\n\n\n"); 
      printf("Qual função você deseja acessar? ");
      int opcao = get_int();

      system("clear"); 

      switch(opcao) 
      {
        case 1:
        registrar(); 
        break;

        case 2:
        consultar(); 
        break;

        case 3:
        deletar(); 
        break;

        default:
        printf("Saindo do sistema!\n");
        return 0;
        break;
      }
    }
}

void registrar(void)
{
  setlocale(LC_ALL,"portuguese");

  printf("Digite o cpf a ser cadastrado: "); 
  char* cpf = get_string();

  char arquivo[64];
  sprintf(arquivo, "%s.txt", cpf); // formatar cpf e armazenar em arquivo

  FILE *file = fopen(arquivo, "w");
  if(file == NULL)
  {
      printf("Erro!\n");
      return;
  }
  fprintf(file, "CPF: ");
  fprintf(file, cpf);  
  fclose(file);  

  file = fopen(arquivo, "a"); 
  fprintf(file, "\nNome: "); 
  fclose(file); 

  printf("Digite o nome a ser registrado: "); 
  char* nome = get_string();

  file = fopen(arquivo, "a"); 
  fprintf(file, nome); 
  fclose(file); 

  file = fopen(arquivo, "a"); 
  fprintf(file, "\nSobrenome: "); 
  fclose(file); 

  printf("Digite o sobrenome a ser cadastrado: "); 
  char* sobrenome = get_string();

  file = fopen(arquivo, "a"); 
  fprintf(file, sobrenome); 
  fclose(file); 

  file = fopen(arquivo, "a"); 
  fprintf(file, "\nCargo: "); 
  fclose(file); 

  printf("Digite o cargo do usuário a ser cadastrado: ");
  char* cargo = get_string();

  file = fopen(arquivo, "a"); 
  fprintf(file, cargo); 
  fclose(file); 
  system("pause");
}

void consultar(void)
{
  setlocale(LC_ALL,"portuguese");

  char buffer[512];

  printf("Digite o cpf a ser consultado: "); 
  char* cpf = get_string();

  FILE *file = fopen(cpf, "r"); 

  if(file == NULL)
  {
    printf("Não foi possível localizar o arquivo.\n");
  }

  while(fgets(buffer, sizeof(buffer), file) != NULL)
  {
    printf("Essas são as informações do usuário: %s\n", buffer);
  }

  fclose(file); 
  system("pause");
}

void deletar(void)
{
  setlocale(LC_ALL,"portuguese");
  printf("Digite o cpf a ser deletado: "); 
  char* cpf = get_string();

  printf("Você tem certeza que deseja deletar o usuário %s? (S/N)", cpf); 
  char resposta[10];
  strcpy(resposta, get_string());
  int i = 0;
  for (i = 0; resposta[i] != '\0'; i++) 
  {
        resposta[i] = toupper(resposta[i]); 
  }

  const char confirmacao[4] = "SIM";
  const char confirmacao_curta[4] = "S";

  if(strcmp(resposta,confirmacao) == 0 || strcmp(resposta,confirmacao_curta) == 0) 
  {
    if(remove(cpf) == 0) //deletar arquivo
    {
      printf("usuário deletado com sucesso!.\n");
      system("pause");
    }
    else
    {
      printf("o usuário não encontrado no sistema!.\n");
      system("pause");
    }
    return;
  }
  else //recomeçar função
  {
    system("clear");
    deletar();
  }
}

int login(char* string)
{
    return (strcmp (string, "admin") == 0) ? 0 : 1; // 0 se admin, 1 para outra coisa
}
