# 🚗 Sistema de Locadora de Veículos — SENAI

Este repositório contém o código-fonte de um projeto em equipe desenvolvido como parte das atividades do curso Técnico em Desenvolvimento de Sistemas no **SENAI**. O objetivo é implementar, em linguagem **C**, um sistema funcional de **locação de veículos**, com foco no cadastro de clientes e gerenciamento de locações.

---

## 🧠 Objetivo do Projeto

Criar um sistema em C para simular o funcionamento básico de uma **empresa de aluguel de carros**, permitindo:

- Cadastro de clientes;
- Cadastro de veículos;
- Realização de locações;
- Encerramento de locações;
- Simulações e listagens de dados.

---

## 👨‍🏫 Proposta do Professor

Desenvolver um código em linguagem **C** que simule uma **empresa de aluguel de carros**, aplicando os principais conceitos de **programação estruturada**.  
A atividade foi proposta para praticar:

- 📦 Manipulação de dados
- 🔁 Estruturas condicionais e de repetição
- 🧱 Estruturas de dados (como `structs` e `arrays`)
- ⚙️ Funções em C

---

## 🧠 Funcionalidades Requeridas

O sistema deverá ser capaz de:

- 🚗 **Cadastrar veículos**
- ❌ **Remover veículos**
- 📋 **Listar veículos**
- 💼 **Simular locação de veículos**
- 🧍 **Cadastrar clientes**
- 📄 **Listar clientes**
- 🔐 **Realizar login**
- 🔁 **Cadastrar e finalizar locações**, utilizando os códigos dos veículos e dos clientes
- 🔎 **Buscar locações por cliente**
- 🚙 **Buscar locações por veículo**
- 📆 **Listar todas as locações por período**, com cálculo de faturamento total
- 📚 **Listar todas as locações registradas**

---

> 💡 *Este projeto foi desenvolvido como parte das atividades práticas do curso Técnico em Desenvolvimento de Sistemas.*

---

## 👥 Equipe de Desenvolvimento

1. Ediney Novaes
2. Gabriel Costa de Jesus
3. Gabriel Oliveira
4. Hiram Bahia
5. Ryan Cerqueira Brandão

---

## ✅ Funcionalidades Implementadas

- [x] Nova locação  
- [x] Cadastrar veículos  
- [x] Remover veículos  
- [x] Listar veículos disponíveis  
- [x] Cadastrar clientes  
- [x] Listar clientes  
- [x] Simular uma locação  
- [x] Encerrar locações  
- [x] Listar todas as locações ativas  
- [x] Buscar locações ativas por cliente  
- [x] Buscar locações ativas por veículo  
- [x] Listar locações por período com cálculo de faturamento  
- [x] Limpar dados  
- [x] Encerrar sistema  

> *(Conforme forem sendo concluídas novas funções ou melhorias, essa lista pode ser atualizada.)*


---

## 📂 Organização do Projeto

A organização da equipe, com as funções de cada integrante e divisão de tarefas, está detalhada na Issue abaixo:  
🔗 [Organização da Equipe e Divisão de Funções](https://github.com/Dhekki/SENAI-AluguelVeiculos/issues/1)

---

## 📘 Acesse a Wiki do Projeto

A Wiki reúne informações complementares e fundamentais para quem estiver trabalhando no projeto, incluindo:

- 📦 Como clonar o repositório  
- 🧪 Padrões de commit utilizados  
- ⚙️ Detalhes técnicos do código  
- 🧭 Navegação geral do repositório  

👉 [Clique aqui para acessar a Wiki](https://github.com/Dhekki/SENAI-AluguelVeiculos/wiki)

---

## 💡 Observações

- O projeto é totalmente feito em C, com foco em lógica e estruturação de dados.  
- Não utiliza banco de dados nem interface gráfica — apenas console.

---

## 🏁 Como Executar

1. Compile o projeto com um compilador C (como `gcc`);
2. Execute o binário gerado no terminal;
3. Siga o menu interativo para utilizar as funções do sistema.

Exemplo de compilação (Linux/macOS):

```bash
gcc main.c cliente.c veiculo.c locacao.c utils.c -o locadora
./locadora
