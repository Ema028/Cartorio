#include <stdio.h>
#include <stdlib.h> 
#include <locale.h> 
#include <string.h>
#include <ctype.h>

void registrar(void);
void consultar(void);
void deletar(void);
int login(char* string);
void salvar(void);
void load(void);
void editar(void);
void to_upper(char* str);

typedef struct user{
  char cpf[15];
  char name[50];
  char surname[50];
  char job[50];
  struct user* prev;
  struct user* next;
} user;

user* head = NULL;

int main()
{
  char senha[15];
  printf("Digite a senha do administrador para acessar o painel");
  scanf("%s", senha);
    
  if(login(senha) == 1)
  {
    return 1;
  }

  load();
    
  while(1)
  {
    system("cls");
    int opcao = 0;

    setlocale(LC_ALL,"portuguese"); 

    printf("Selecione um item do menu:\n\n");
    printf("\t1-Registrar nomes\n\t2-Consultar nomes\n\t3-Deletar nomes\n\t4-Sair do sistema\n\n\n"); 
    printf("Qual função você deseja acessar? ");
    scanf("%i", &opcao);

    system("cls"); 

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
      salvar();
      user* temp = head;
      while (temp != NULL) //liberar memoria
      {
        user* temp2 = temp;
        temp = temp->next;
        free(temp2);
      }
      return 0;
      break;
    }
  }
}

void registrar(void) // cria uma double linked list com o struct usuario para acesso rápido enquanto o programa está ativo
{
  setlocale(LC_ALL,"portuguese");

  user* new_user = malloc(sizeof(user));
  if(new_user == NULL)
  {
    return;
  }

  printf("Digite o CPF: ");
  scanf("%s", new_user->cpf);

  printf("Digite o Nome: ");
  scanf("%s", new_user->name);
  to_upper(new_user->name);

  printf("Digite o Sobrenome: ");
  scanf("%s", new_user->surname);
  to_upper(new_user->surname);

  printf("Digite o Cargo: ");
  scanf("%s", new_user->job);
  to_upper(new_user->job);

  new_user->prev = NULL;
  new_user->next = NULL;

  if(head == NULL)
  {
    head = new_user;
  }
  else
  {
    new_user->next = head;
    head->prev = new_user;
    new_user->prev = NULL;
    head = new_user;
  }

  printf("usuário registrado com sucesso!\n");
  system("pause");
}

void consultar(void)
{
  setlocale(LC_ALL,"portuguese");
  
  char cpf[15];

  printf("Digite o CPF a ser consultado: ");
  scanf("%s", cpf);

  user* temp = head;
  while (temp != NULL)
  {
    if (strcmp(temp->cpf, cpf) == 0) 
    {
      printf("informações do usuário:\n");
      printf("CPF: %s\nNome: %s\nSobrenome: %s\nCargo: %s\n", temp->cpf, temp->name, temp->surname, temp->job);
      system("pause");
      return;
    }
    else
    {
      temp = temp->next;
    }
  }
  printf("Usuário não encontrado!\n");
  system("pause");
}

void deletar(void)
{
  setlocale(LC_ALL,"portuguese");

  char cpf[15];
  printf("Digite o cpf a ser deletado: ");
  scanf("%s", cpf);

  char resposta[4];
  printf("Você tem certeza que deseja deletar o usuário %s? (S/N)", cpf); 
  scanf("%s", resposta);
  to_upper(resposta);

  const char confirmacao[4] = "SIM";
  const char confirmacao_curta[4] = "S";

  if(strcmp(resposta,confirmacao) == 0 || strcmp(resposta,confirmacao_curta) == 0) 
  {
    user* temp = head;
    while (temp != NULL)
    {
      if (strcmp(temp->cpf, cpf) == 0) 
      {
        if (temp->prev != NULL) 
        {
          temp->prev->next = temp->next; // node anterior pula temp
        } 
        else
        {
          head = temp->next;
        }
        if (temp->next != NULL)
        {
          temp->next->prev = temp->prev; // próximo node pula temp
        }
        free(temp);
        printf("Usuário deletado com sucesso!\n");
        system("pause");
        return;
      }
      else
      {
        temp = temp->next;
      }
    }
  }
  else
  {
    printf("Operação cancelada!\n");
    system("pause");
    return;
  }
}

int login(char* string)
{
  if (strcmp (string, "admin") == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void salvar(void) // salva as informações dos usuários em um arquivo
{
  FILE* file = fopen("usuarios.txt", "w");
  if (file == NULL) 
  {
    printf("Erro ao salvar!\n");
    return;
  }

  user* temp = head;
  while (temp != NULL)
  {
    fprintf(file, "%s %s %s %s\n", temp->cpf, temp->name, temp->surname, temp->job);
    temp = temp->next;
  }

  fclose(file);
  printf("Dados salvos com sucesso!\n");
}

void load(void) // carrega as informações dos usuários do arquivo no programa
{
  FILE* file = fopen("usuarios.txt", "r");
  if (file == NULL)
  {
    return;
  }

  while(!feof(file)) // até o final do arquivo
  {
    user* new_user = malloc(sizeof(user));
    if(new_user == NULL)
    {
      fclose(file);
      return;
    }

    fscanf(file, "%s %s %s %s", new_user->cpf, new_user->name, new_user->surname, new_user->job);

    new_user->prev = NULL;
    new_user->next = NULL;

    if(head == NULL)
    {
      head = new_user;
    }
    else
    {
      new_user->next = head;
      head->prev = new_user;
      new_user->prev = NULL;
      head = new_user;
    }
  }
}

void editar(void)
{
  setlocale(LC_ALL,"portuguese");

  char nome[50];
  printf("Qual o nome do usuário que deseja editar?\n");
  scanf("%s", nome);
  to_upper(nome);

  user* temp = head;
  while (temp != NULL)
  {
    if (strcmp(temp->name, nome) == 0) 
    {
      int resposta;
      char buffer[40];
      printf("Usuário encontrado!\n");
      printf("Digite 1 para editar o CPF, 2-Nome, 3-Sobrenome ou 4-Cargo?\n");
      scanf("%i", &resposta);
      printf("Qual o novo registro?\n");
      scanf("%s", buffer);
      to_upper(buffer);
      
      switch(resposta) 
      {
        case 1:
          strcpy(temp->cpf, buffer);
          break;

        case 2:
          strcpy(temp->cpf, buffer);
          break;

        case 3:
          strcpy(temp->surname, buffer); 
          break;

        case 4:
          strcpy(temp->job, buffer);
          break;

        default:
          printf("Não é uma opção válida!\n");
          system("pause");
          return;
      }
      printf("Registro atualizado com sucesso!\n");
      system("pause");
      return;
    }
    else
    {
      temp = temp->next;
    }
  }
  printf("Usuário não encontrado!\n");
  system("pause");
}

void to_upper(char* str) 
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    str[i] = toupper(str[i]);
  } 
}
