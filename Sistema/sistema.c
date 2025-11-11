#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    int idade;
    char email[100];
    double saldoBancario;
} Cliente;

typedef struct {
    char nomeProduto[100];
    char descricao[100];
    int quantidade;
    double valor;
} Produto;

// Protótipos
void cadastrarCliente();
void cadastrarProduto();
int validaSaldoCliente(char *nomeCliente, float valorCompra);
int verificaDisponibilidadeProduto(char *nomeProduto, int quantidadeDesejada);
int validaCompra(char *nomeCliente, char *nomeProduto, int quantidade);
void realizarCompra();
void atualizaSaldoCliente(char *nomeCliente, float valorCompra);
void atualizaEstoque(char *nomeProduto, int quantidadeComprada);
void imprimeDescricaoProduto();
void imprimeDadosCliente();
void imprimeRelatorio();

int main() {
    int opcao = -1;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Cadastrar novo cliente\n");
        printf("2 - Cadastrar novo produto\n");
        printf("3 - Imprimir descricao de um produto\n");
        printf("4 - Imprimir dados de um cliente\n");
        printf("5 - Realizar uma compra\n");
        printf("6 - Imprimir relatório de compras\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarCliente(); break;
            case 2: cadastrarProduto(); break;
            case 3: imprimeDescricaoProduto(); break;
            case 4: imprimeDadosCliente(); break;
            case 5: realizarCompra(); break;
            case 6: imprimeRelatorio(); break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opção inválida.\n"); break;
        }
    } while (opcao != 0);

    return 0;
}

void cadastrarCliente() {
    FILE *arquivoCliente = fopen("clientes.csv", "a");
    if (!arquivoCliente) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente c;

    printf("\n=== Cadastro de Cliente ===\n");
    printf("Nome do cliente: ");
    scanf(" %[^\n]", c.nome); 
    printf("Idade: ");
    scanf("%d", &c.idade);
    printf("Email: ");
    scanf(" %99s", c.email);
    printf("Saldo: ");
    scanf("%lf", &c.saldoBancario);

    fprintf(arquivoCliente, "%s,%d,%s,%.2lf\n", c.nome, c.idade, c.email, c.saldoBancario);
    fclose(arquivoCliente);

    printf("\nCliente cadastrado com sucesso!\n");
}

void cadastrarProduto() {
    FILE *arquivoProduto = fopen("produtos.csv", "a");
    if (!arquivoProduto) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Produto p;

    printf("\n=== Cadastro de Produto ===\n");
    printf("Nome do produto: ");
    scanf(" %[^\n]", p.nomeProduto); 
    printf("Descrição do produto: ");
    scanf(" %[^\n]", p.descricao);
    printf("Quantidade em estoque: ");
    scanf("%d", &p.quantidade);
    printf("Valor do produto: ");
    scanf("%lf", &p.valor);

    fprintf(arquivoProduto, "%s,%s,%d,%.2lf\n", p.nomeProduto, p.descricao, p.quantidade, p.valor);
    fclose(arquivoProduto);

    printf("\nProduto cadastrado com sucesso!\n");
}

int validaSaldoCliente(char *nomeCliente, float valorCompra) {
    FILE *arquivoCliente = fopen("clientes.csv", "r");
    if (!arquivoCliente){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[256], nome[100], email[100];
    int idade;
    double saldo;

    while (fgets(linha, sizeof(linha), arquivoCliente)) {
        sscanf(linha, "%99[^,],%d,%99[^,],%lf", nome, &idade, email, &saldo);
        if (strcmp(nome, nomeCliente) == 0) {
            fclose(arquivoCliente);
            return saldo >= valorCompra;
        }
    }

    fclose(arquivoCliente);
    return 0;
}

int verificaDisponibilidadeProduto(char *nomeProduto, int quantidadeDesejada) {
    FILE *arquivoProduto = fopen("produtos.csv", "r");
    if (!arquivoProduto){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char linha[256], nome[100], desc[100];
    int quantidade;
    double valor;

    while (fgets(linha, sizeof(linha), arquivoProduto)){
        sscanf(linha, "%99[^,],%99[^,],%d,%lf", nome, desc, &quantidade, &valor);
        if(strcmp(nome,nomeProduto) == 0){
            fclose(arquivoProduto);
            return quantidade >= quantidadeDesejada;
        }
    }

    fclose(arquivoProduto);
    return 0;
}

int validaCompra(char *nomeCliente, char *nomeProduto, int quantidade) {
    FILE *arquivo = fopen("produtos.csv", "r");
    if (!arquivo) return 0;

    char linha[256], nome[100], desc[100];
    int qtd;
    float valor;

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%99[^,],%99[^,],%d,%f", nome, desc, &qtd, &valor);
        if (strcmp(nome, nomeProduto) == 0) {
            fclose(arquivo);
            return validaSaldoCliente(nomeCliente, valor * quantidade) &&
                   verificaDisponibilidadeProduto(nomeProduto, quantidade);
        }
    }

    fclose(arquivo);
    return 0;
}

// ======== VERSÕES SIMPLIFICADAS ========

void atualizaSaldoCliente(char *nomeCliente, float valorCompra) {
    FILE *origem = fopen("clientes.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!origem || !temp) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    char linha[256], nome[100], email[100];
    int idade;
    double saldo;

    while (fgets(linha, sizeof(linha), origem)) {
        sscanf(linha, "%99[^,],%d,%99[^,],%lf", nome, &idade, email, &saldo);
        if (strcmp(nome, nomeCliente) == 0)
            saldo -= valorCompra;
        fprintf(temp, "%s,%d,%s,%.2lf\n", nome, idade, email, saldo);
    }

    fclose(origem);
    fclose(temp);
    remove("clientes.csv");
    rename("temp.csv", "clientes.csv");
}

void atualizaEstoque(char *nomeProduto, int quantidadeComprada) {
    FILE *origem = fopen("produtos.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!origem || !temp) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    char linha[256], nome[100], desc[100];
    int qtd;
    float valor;

    while (fgets(linha, sizeof(linha), origem)) {
        sscanf(linha, "%99[^,],%99[^,],%d,%f", nome, desc, &qtd, &valor);
        if (strcmp(nome, nomeProduto) == 0)
            qtd -= quantidadeComprada;
        fprintf(temp, "%s,%s,%d,%.2f\n", nome, desc, qtd, valor);
    }

    fclose(origem);
    fclose(temp);
    remove("produtos.csv");
    rename("temp.csv", "produtos.csv");
}

// =======================================

void realizarCompra() {
    char nomeCliente[100], nomeProduto[100];
    int quantidade;
    float valorUnitario = 0;
    FILE *arquivo, *relatorio;

    printf("\n=== Realizar Compra ===\n");
    printf("Nome do cliente: ");
    fgets(nomeCliente, 100, stdin);
    nomeCliente[strcspn(nomeCliente, "\n")] = 0;

    printf("Nome do produto: ");
    fgets(nomeProduto, 100, stdin);
    nomeProduto[strcspn(nomeProduto, "\n")] = 0;

    printf("Quantidade desejada: ");
    scanf("%d", &quantidade);
    getchar();

    arquivo = fopen("produtos.csv", "r");
    char linha[256], nome[100], desc[100];
    int qtd;
    float valor;
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%99[^,],%99[^,],%d,%f", nome, desc, &qtd, &valor);
        if (strcmp(nome, nomeProduto) == 0) {
            valorUnitario = valor;
            break;
        }
    }
    fclose(arquivo);

    if (!validaCompra(nomeCliente, nomeProduto, quantidade)) {
        printf("Compra não pode ser realizada (saldo insuficiente ou falta de estoque).\n");
        return;
    }

    atualizaSaldoCliente(nomeCliente, valorUnitario * quantidade);
    atualizaEstoque(nomeProduto, quantidade);

    relatorio = fopen("relatorioDeCompras.csv", "a");
    fprintf(relatorio, "%s comprou %d x %s por R$ %.2f\n",
            nomeCliente, quantidade, nomeProduto, valorUnitario * quantidade);
    fclose(relatorio);

    printf("Compra realizada com sucesso!\n");
}

void imprimeDescricaoProduto() {
    FILE *arquivo = fopen("produtos.csv", "r");
    char linha[256];
    int i = 1;
    if (!arquivo) return;

    printf("\n=== Produtos ===\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome[100], desc[100];
        int qtd;
        float valor;
        sscanf(linha, "%99[^,],%99[^,],%d,%f", nome, desc, &qtd, &valor);
        printf("\nProduto %d:\nNome: %s\nDesc: %s\nQtd: %d\nValor: R$ %.2f\n",
               i++, nome, desc, qtd, valor);
    }
    fclose(arquivo);
}

void imprimeDadosCliente() {
    FILE *arquivo = fopen("clientes.csv", "r");
    char linha[256];
    int i = 1;
    if (!arquivo) return;

    printf("\n=== Clientes ===\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome[100], email[100];
        int idade;
        double saldo;
        sscanf(linha, "%99[^,],%d,%99[^,],%lf", nome, &idade, email, &saldo);
        printf("\nCliente %d:\nNome: %s\nEmail: %s\nIdade: %d\nSaldo: R$ %.2lf\n",
               i++, nome, email, idade, saldo);
    }
    fclose(arquivo);
}

void imprimeRelatorio() {
    FILE *arquivo = fopen("relatorioDeCompras.csv", "r");
    if (!arquivo) {
        printf("Nenhum relatório encontrado.\n");
        return;
    }

    char linha[256];
    int i = 1;

    printf("\n=== RELATÓRIO DE COMPRAS ===\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%d. %s", i++, linha);
    }
    fclose(arquivo);
}
