#include <stdlib.h> 
#include <stdio.h> 
#include <locale.h> 
#include <string.h> 

int registro();
int consulta();
int deletar();

int main(void)
{
  int opcao = 0;
  int i = 1;
  char* senha = malloc(6);

  printf("Login de administrador!\n\nDigite a sua senha: ");
  scanf("%s", senha);

  if(strcmp (senha, "admin") == 0)
  {
    free(senha);
    system("cls");

    for(i = 1; i = 1;)
    {
      system("cls");

      setlocale(LC_ALL,"portuguese"); 

      printf("   Cartório\n\n"); 
      printf("Selecione um item do menu:\n\n"); //início do menu
      printf("\t1-Registrar nomes\n\t2-Consultar nomes\n\t3-Deletar nomes\n\t4-Sair do sistema\n\n\n"); 
      printf("Qual função você deseja acessar? "); //fim do menu

      scanf("%d", &opcao); 

      system("cls"); 

      switch(opcao) 
      {
        case 1:
        registro(); 
        break;

        case 2:
        consulta(); 
        break;

        case 3:
        deletar(); 
        break;

        case 4:
        printf("Obrigada por utilizar o sistema!\n");
        return 0;
        break;

        default:
        printf("Essa não é uma opção!\n");
        system("pause");
        break;
      }
    }

    printf("Esse software é de Emanuelle");
  }
  else
  {
    printf("Senha incorreta!");
    return 1;
  }
}

int registro(void) //função para registrar usuários no sistema
{
  setlocale(LC_ALL,"portuguese");

  printf("Você escolheu o registro de nomes!\n");

  //declarando variáveis e alocando espaço na memória
  char arquivo[40]; 
  char cpf[40];
  char nome[40];
  char sobrenome[40];
  char cargo[40];

  printf("Digite o cpf a ser cadastrado: "); 
  scanf("%s", cpf);

  strcpy (arquivo, cpf); 

  FILE *file = fopen(arquivo, "w"); 
  fprintf(file, "CPF: ");
  fprintf(file, cpf);  
  fclose(file);  

  file = fopen(arquivo, "a"); 
  fprintf(file, "\nNome: "); 
  fclose(file); 

  printf("Digite o nome a ser registrado: "); 
  scanf("%s", nome);

  file = fopen(arquivo, "a"); 
  fprintf(file, nome); 
  fclose(file); 

  file = fopen(arquivo, "a"); 
  fprintf(file, "\nSobrenome: "); 
  fclose(file); 

  printf("Digite o sobrenome a ser cadastrado: "); 
  scanf("%s", sobrenome);

  file = fopen(arquivo, "a"); 
  fprintf(file, sobrenome); 
  fclose(file); 

  file = fopen(arquivo, "a"); 
  fprintf(file, "\nCargo: "); 
  fclose(file); 

  printf("Digite o cargo do usuário a ser cadastrado: ");
  scanf("%s", cargo);

  file = fopen(arquivo, "a"); 
  fprintf(file, cargo); 
  fclose(file); 
  system("pause");
}

int consulta(void) //função para consultar usuários no sistema
{
  setlocale(LC_ALL,"portuguese");

  printf("Você escolheu a consulta de nomes!\n");

  char cpf[40];
  char conteudo[200];

  printf("Digite o cpf a ser consultado: "); 
  scanf("%s", cpf);

  FILE *file = fopen(cpf, "r"); 

  if(file == NULL)
  {
    printf("Não foi possível localizar o arquivo.\n");
  }

  while(fgets(conteudo, 200, file) != NULL)
  {
    printf("Essas são as informações do usuário: %s\n", conteudo);
  }

  fclose(file); 
  system("pause");
}

int deletar(void) //função para deletar usuários do sistema
{
  setlocale(LC_ALL,"portuguese");

  printf("Você escolheu deletar nomes!\n");

  char cpf[40];
  char resposta[4];

  printf("Digite o cpf a ser deletado: "); 
  scanf("%s", cpf);

  printf("Você tem certeza que deseja deletar o usuário %s? ", cpf); 
  scanf("%s", resposta); 
  int i = 0;
  for (i = 0; i < 4; i++) 
  {
        resposta[i] = toupper(resposta[i]); 
  }

  const char confirmacao[4] = "SIM"; // declarando respostas positivas
  const char confirmacao_curta[4] = "S";

  if(strcmp(resposta,confirmacao) == 0 || strcmp(resposta,confirmacao_curta) == 0) //comparando se a resposta fornecida pelo usuário é positiva
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
    return 0;
  }
  else //recomeçar função
  {
    system("cls");
    deletar();
  }
}
