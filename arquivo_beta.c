#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#define MAXVEICULOS 100
#define MAXCLIENTES 100
#define MAXLOCACOES 200

int codigo=0;

struct veiculo {
    int codigo;
    int ano;
    char modelo[50];
    char placa[10];
    float precoPorDia;
};

struct cliente {
    int codigo;
    char nome[50];
    char cpf[15];
    char senha[20];
};

struct locacao {
	int codigoloc;
    int codigoCliente;
    int codigoVeiculo;
    char dataInicio[11];
    char dataFim[11];
    float valorTotal;
};

struct veiculo veiculos[MAXVEICULOS];
struct cliente clientes[MAXCLIENTES];
struct locacao locacoes[MAXLOCACOES];

void locar(){
}
void cadastrarVeiculo(){
	
}
void removerVeiculo(){
}
void listarVeiculo(){
}
void simular(){
}
void cadastrarCliente(){
}
void encerrarLocacao(){
}
void listarLocacoesAtivas(){
	if (codigo==0){
	printf("\nAinda Não há Locações !");
	sleep(3);
	system("cls");
	}
	else{
	printf("\n===== Locações =====\n");
	for(int i=0;i<codigo;i++){
		int idcliente,idveiculo;
		idcliente = locacoes[i].codigoCliente;
		idveiculo = locacoes[i].codigoVeiculo;
		printf("\n %i- cliente : %s \n Veículo: %s \n Data da locação: %s até %s \n Valor Total: R$ %f",i+1,clientes[idcliente].nome,veiculos[idveiculo].modelo,locacoes[i].dataInicio,locacoes[i].dataFim,locacoes[i].valorTotal);
		printf("\n__________________");}
	}
	
}
void buscarLocacoesAtivasPorCliente(){
}
void buscarLocacoesAtivasPorVeiculo(){
}
void listarLocacoesEFaturamentoPorPeriodo(){
}
void encerrar(){
}

int menu();

void login() {
    char email[50], senha[40];
    printf("Login\n");

    while (1) {
        printf("\nE-mail: ");
        fgets(email, (50), stdin);
        printf("\nSenha: ");
        fgets(senha, (40), stdin);

        if (strcmp(email, "login@gmail.com\n") == 0 && strcmp(senha, "12345\n") == 0) {
            menu();
            break;
        } else {
            printf("\nE-mail ou senha incorreta!\n");
        }
    }
}

int menu() {
    int opcao;
    system("cls");
	printf("Bem vindo ao sistema de aluguel de veículos!\n");
    sleep(3);
    system("cls");
	
	while (1) {

        printf("\\----------------------------------------//\n");
		printf("\nMenu:\n");
        printf("\n 1 - cadastrar veículos ");
        printf("\n 2 - remover veículos ");
        printf("\n 3 - listar veículos disponíveis ");
        printf("\n 4 - simular locação ");
        printf("\n 5 - cadastrar cliente ");
        printf("\n 6 - encerrar locações ");
        printf("\n 7 - listar todas as locações ativas ");
        printf("\n 8 - buscar locações ativas por cliente ");
        printf("\n 9 - buscar locações ativas por veículo ");
        printf("\n 10 - listar locações e faturamento por período ");
        printf("\n 11 - encerrar \n");
        printf("\\----------------------------------------//\n");
        printf("\nOpcao: ");
		scanf("%i", &opcao);
        

        switch (opcao) {
            case 1:
                locar();
                codigo++;
                break;
            case 2:
                cadastrarVeiculo();
                break;
            case 3:
                removerVeiculo();
                break;
            case 4:
                simular();
                break;
            case 5:
                cadastrarCliente();
                break;
            case 6:
                encerrarLocacao();
                break;
            case 7:
                listarLocacoesAtivas();
                break;
            case 8:
                buscarLocacoesAtivasPorCliente();
                break;
            case 9:
                buscarLocacoesAtivasPorVeiculo();
                break;
            case 10:
                listarLocacoesEFaturamentoPorPeriodo();
                break;
            case 11:
                listarVeiculo();
                break;
            case 12:
            	encerrar();
            	return 0;
			default:
                printf("Opção inválida!\n");
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    login();
    return (0);
}