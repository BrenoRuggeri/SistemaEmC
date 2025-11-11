# 🛒 Sistema de Gerenciamento de Compras em C

Este projeto implementa um **sistema de gerenciamento de clientes, produtos e compras** em linguagem C.  
Ele simula uma pequena loja, permitindo o **cadastro de clientes e produtos**, a **realização de compras**, e a **geração de relatórios** de forma simples e totalmente baseada em arquivos CSV.

---

## 🚀 Funcionalidades

O sistema oferece as seguintes operações:

### 👥 Clientes
- Cadastrar novos clientes (`clientes.csv`);
- Exibir a lista completa de clientes com seus dados;
- Verificar automaticamente se o cliente possui **saldo suficiente** para realizar uma compra.

### 📦 Produtos
- Cadastrar novos produtos (`produtos.csv`);
- Exibir a lista completa de produtos com **descrição, quantidade em estoque e preço**;
- Atualizar o estoque após cada compra realizada.

### 💰 Compras
- Validar uma compra verificando **saldo do cliente** e **disponibilidade do produto**;
- Atualizar o saldo do cliente e o estoque do produto;
- Registrar todas as transações em `relatorioDeCompras.csv`.

### 📄 Relatórios
- Gerar e visualizar o **relatório completo de compras realizadas**.

---

## 🧩 Estrutura dos Arquivos

O sistema utiliza três arquivos CSV para armazenar os dados:

| Arquivo | Descrição | Campos |
|----------|------------|--------|
| `clientes.csv` | Armazena os dados dos clientes | `nome, idade, email, saldoBancario` |
| `produtos.csv` | Armazena os produtos cadastrados | `nomeProduto, descricao, quantidade, valor` |
| `relatorioDeCompras.csv` | Registra as compras realizadas | `nomeCliente, quantidade, nomeProduto, valorTotal` |

Exemplo de conteúdo de `clientes.csv`:
```
João Silva,25,joao@email.com,500.00
Maria Souza,30,maria@email.com,750.50
```

Exemplo de conteúdo de `produtos.csv`:
```
Camiseta,Algodão branca,20,49.90
Calça Jeans,Azul escuro,15,99.90
```

---

## 🧠 Estrutura do Código

O código é dividido em funções que mantêm o sistema organizado e modularizado:

| Função | Descrição |
|--------|------------|
| `cadastrarCliente()` | Cadastra um novo cliente no arquivo `clientes.csv`. |
| `cadastrarProduto()` | Cadastra um novo produto no arquivo `produtos.csv`. |
| `validaSaldoCliente()` | Verifica se o cliente possui saldo suficiente. |
| `verificaDisponibilidadeProduto()` | Verifica se há estoque disponível para o produto. |
| `validaCompra()` | Valida a compra com base no saldo e estoque. |
| `realizarCompra()` | Efetua a compra e atualiza os arquivos correspondentes. |
| `atualizaSaldoCliente()` | Atualiza o saldo do cliente após a compra. |
| `atualizaEstoque()` | Atualiza o estoque do produto após a compra. |
| `imprimeDescricaoProduto()` | Mostra todos os produtos cadastrados. |
| `imprimeDadosCliente()` | Mostra todos os clientes cadastrados. |
| `imprimeRelatorio()` | Exibe o relatório de compras. |

---

## 💻 Como Executar

### 🔧 Pré-requisitos
- Compilador C (GCC, Clang, ou similar);
- Sistema operacional Linux, macOS ou Windows com terminal habilitado.

### ▶️ Passos para execução

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/usuario/sistema-compras-c.git
   cd sistema-compras-c
   ```

2. **Compile o código:**
   ```bash
   gcc sistema_compras.c -o sistema
   ```

3. **Execute o programa:**
   ```bash
   ./sistema
   ```

---

## 🧭 Menu Principal

```
=== MENU PRINCIPAL ===
1 - Cadastrar novo cliente
2 - Cadastrar novo produto
3 - Imprimir descricao de um produto
4 - Imprimir dados de um cliente
5 - Realizar uma compra
6 - Imprimir relatório de compras
0 - Sair
```

---

## 🧪 Exemplo de Uso

### 1️⃣ Cadastro de Cliente
```
Nome do cliente: João Silva
Idade: 25
Email: joao@email.com
Saldo: 500.00
```

### 2️⃣ Cadastro de Produto
```
Nome do produto: Camiseta
Descrição do produto: Algodão branca
Quantidade em estoque: 20
Valor do produto: 49.90
```

### 3️⃣ Compra
```
Nome do cliente: João Silva
Nome do produto: Camiseta
Quantidade desejada: 2
Compra realizada com sucesso!
```

---

## ⚙️ Tecnologias Utilizadas

- Linguagem C (padrão C99)
- Manipulação de arquivos com `stdio.h`
- Estruturas com `typedef struct`
- Lógica de controle, validação e persistência de dados

---

## 🧑‍💻 Autores

- [**Breno Ruggeri**](https://github.com/BrenoRuggeri)
- [**Miguel Bueno**](https://github.com/miguelito368)
- [**Pedro Teles**](https://github.com/PezTeles)
- [**Rhuan Jhonnatan**](https://github.com/RhuanJhonnatan)

Estudantes de Ciência da Computação — USCS  
Trabalho desenvolvido para disciplina Algoritimos e Estruturas de Dados II   

---

## 📜 Licença

Este projeto é de uso **educacional e livre**, podendo ser modificado e redistribuído sob os termos da licença MIT.
