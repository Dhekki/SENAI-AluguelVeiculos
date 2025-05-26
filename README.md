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

Desenvolver um código em linguagem C que simule uma **empresa de aluguel de carros**, aplicando os principais conceitos de programação estruturada. A atividade foi proposta para praticar:

- Modularização;
- Manipulação de dados;
- Estruturas condicionais e de repetição;
- Estruturas de dados (como structs e arrays);
- Funções em C.

---

## 👥 Equipe de Desenvolvimento

- Ryan Cerqueira Brandão
- Gabriel Costa de Jesus
- Edney Novais
- Hiram Bahia
- Gabriel Oliveira

---

## ✅ Funcionalidades Implementadas

- [x] Cadastro de clientes
- [x] Cadastro de veículos
- [x] Locação de veículos
- [x] Encerramento de locações
- [x] Listagem e busca de locações
- [x] Relatório por período
- [x] Simulação de valores

*(Conforme forem sendo concluídas novas funções, essa lista pode ser atualizada.)*

---

## 💡 Observações

- O projeto é totalmente feito em C, com foco em lógica e estruturação de dados.
- Não utiliza banco de dados nem interface gráfica — apenas console.

---

## 📌 Licença

Este projeto está licenciado sob a licença [MIT](./LICENSE).

---

## 🏁 Como Executar

1. Compile o projeto com um compilador C (como `gcc`);
2. Execute o binário gerado no terminal;
3. Siga o menu interativo para utilizar as funções do sistema.

Exemplo de compilação (Linux/macOS):

```bash
gcc main.c cliente.c veiculo.c locacao.c utils.c -o locadora
./locadora
