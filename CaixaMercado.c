#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int Id;
   char NomeProduto[50];
   float Preco;
} Produto;

void cadastrarProdutos(FILE *arquivo) {
   Produto P;

   printf("Nome do produto: ");
   fgets(P.NomeProduto, 50, stdin);  // Usando fgets para capturar o nome do produto com espaços
   P.NomeProduto[strcspn(P.NomeProduto, "\n")] = '\0';  // Remove a nova linha (\n) adicionada pelo fgets

   printf("Código ID do produto: ");
   scanf("%d", &P.Id);
   
   printf("Valor do produto: ");
   scanf("%f", &P.Preco);

   fwrite(&P, sizeof(Produto), 1, arquivo);
   printf("Produto cadastrado com sucesso!\n");

   // Limpar o buffer de entrada após scanf
   while (getchar() != '\n');
}

void listarProdutos(FILE *arquivo) {
   Produto P;
   rewind(arquivo);  // Volta ao início do arquivo para ler desde o começo
   printf("\nProdutos disponíveis:\n");
   while (fread(&P, sizeof(Produto), 1, arquivo)) {
      printf("ID: %d\nProduto: %s\nPreço: R$%.2f\n", P.Id, P.NomeProduto, P.Preco);
      printf("---------------------------\n");
   }
}

int main() {
   FILE *arquivo = fopen("produtos.dat", "a+b");  // Abrir arquivo em modo de leitura/escrita

   if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo!\n");
      return 1;
   }

   int opcao;
   do {
      printf("\n1. Cadastrar produto\n2. Listar produtos\n3. Sair\n");
      printf("Escolha uma opção: ");
      scanf("%d", &opcao);

      // Limpar o buffer de entrada após scanf
      while (getchar() != '\n');

      switch (opcao) {
         case 1:
            cadastrarProdutos(arquivo);
            break;
         case 2:
            listarProdutos(arquivo);
            break;
         case 3:
            printf("Saindo...\n");
            break;
         default:
            printf("Opção inválida!\n");
      }
   } while (opcao != 3);

   fclose(arquivo);  // Fechar arquivo ao finalizar o programa
   return 0;
}
