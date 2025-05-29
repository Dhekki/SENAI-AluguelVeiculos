#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXVEICULOS 100
#define MAXCLIENTES 100
#define MAXLOCACOES 200
#define ARQUIVO_VEICULOS "veiculos.dat"
#define ARQUIVO_CLIENTES "clientes.dat"

int qntdlocacoes = 0, qntdClientes = 0, qntdVeiculos = 0;

struct Veiculo {
    int codigo;
    int ano;
    char modelo[50];
    char placa[8];
    float precoPorDia;
};

struct Cliente {
    int codigo;
    char nome[50];
    char cpf[15];
    char senha[20];
};

struct Locacao {
	int codigoloc;
    int codigoCliente;
    int codigoVeiculo;
    char dataInicio[11];
    char dataFim[11];
    float valorTotal;
};

struct Veiculo veiculos[MAXVEICULOS];
struct Cliente clientes[MAXCLIENTES];
struct Locacao locacoes[MAXLOCACOES];

void erro(){
    printf("Opção inválida!\n");
}

void clearDelay(){
    sleep(2);
    system("cls");
}

void limparBuffer() {
	fflush(stdout);
	printf("\n");
	system("cls");
}

void limparBufferDentro() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void salvarDados() {
    FILE *arquivo;
    
    arquivo = fopen(ARQUIVO_VEICULOS, "wb");
    if (arquivo) {
        fwrite(&qntdVeiculos, sizeof(int), 1, arquivo);
        fwrite(veiculos, sizeof(struct Veiculo), qntdVeiculos, arquivo);
        fclose(arquivo);
    }
    
    arquivo = fopen(ARQUIVO_CLIENTES, "wb");
    if (arquivo) {
        fwrite(&qntdClientes, sizeof(int), 1, arquivo);
        fwrite(clientes, sizeof(struct Cliente), qntdClientes, arquivo);
        fclose(arquivo);
    }
}

void carregarDados() {
    FILE *arquivo;
    
    arquivo = fopen(ARQUIVO_VEICULOS, "rb");
    if (arquivo) {
        fread(&qntdVeiculos, sizeof(int), 1, arquivo);
        fread(veiculos, sizeof(struct Veiculo), qntdVeiculos, arquivo);
        fclose(arquivo);
    }
    
    arquivo = fopen(ARQUIVO_CLIENTES, "rb");
    if (arquivo) {
        fread(&qntdClientes, sizeof(int), 1, arquivo);
        fread(clientes, sizeof(struct Cliente), qntdClientes, arquivo);
        fclose(arquivo);
    }
}

int validarPlaca(char placa[]) {
	if (strlen(placa) != 7) return 0;
    
    // ABC1D23 ou ABC1234
    for (int i = 0; i < 3; i++) {
        if (!isalpha(placa[i])) return 0;
    }
    
    if (!isdigit(placa[3])) return 0;

    if(!isdigit(placa[4]) && !isalpha(placa[4])) return 0;
    
    if (!isdigit(placa[5]) || !isdigit(placa[6])) return 0;
    
    return 1;
}
void listarClientes() {
    printf("\\------------------ Clientes ------------------//\n");
    for (int i = 0; i < qntdClientes; i++) {
        printf("\n %d - Cliente: %s", i + 1, clientes[i].nome);
        printf("\n Código: %d", clientes[i].codigo);
        printf("\n CPF: %s", clientes[i].cpf);
        printf("\n-----------------------------------------------");
    }
    printf("\n");
    system("pause");
}

void locar() {
    if (qntdVeiculos == 0 || qntdClientes == 0) {
        printf("\nCadastre Veículos/Clientes Primeiro !\n");
        return;
    }

    char input[20];
    int op;

    while (1) {
        printf("\nEscolha uma opção: ");
        printf("\n1 - Locar");
        printf("\n2 - Listar Veículos Disponíveis");
        printf("\n3 - Listar Clientes\nOpção: ");
        
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &op) != 1) {
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        switch (op) {
            case 1: {
                int codigoVeiculo, codigoCliente;
                char dataInicio[20], dataFim[20]; // espaço maior para evitar overflow

                printf("Código do Veículo: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &codigoVeiculo) != 1) {
                    printf("Código inválido!\n");
                    break;
                }

                // Verifica se veículo existe
                int indexVeiculo = -1;
                for (int i = 0; i < qntdVeiculos; i++) {
                    if (veiculos[i].codigo == codigoVeiculo) {
                        indexVeiculo = i;
                        break;
                    }
                }
                if (indexVeiculo == -1) {
                    printf("Veículo não encontrado!\n");
                    break;
                }

                // Verifica se veículo já está locado
                for (int i = 0; i < qntdlocacoes; i++) {
                    if (locacoes[i].codigoVeiculo == codigoVeiculo) {
                        printf("Este veículo já está locado!\n");
                        return;
                    }
                }

                printf("Código do Cliente: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &codigoCliente) != 1) {
                    printf("Código inválido!\n");
                    break;
                }

                // Verifica se cliente existe
                int indexCliente = -1;
                for (int i = 0; i < qntdClientes; i++) {
                    if (clientes[i].codigo == codigoCliente) {
                        indexCliente = i;
                        break;
                    }
                }
                if (indexCliente == -1) {
                    printf("Cliente não encontrado!\n");
                    break;
                }

                printf("Data de início da Locação (dd/mm/aaaa): ");
                if (fgets(dataInicio, sizeof(dataInicio), stdin) == NULL) {
                    printf("Erro ao ler data!\n");
                    break;
                }
                dataInicio[strcspn(dataInicio, "\n")] = '\0'; // remove \n

                printf("Data Final da Locação (dd/mm/aaaa): ");
                if (fgets(dataFim, sizeof(dataFim), stdin) == NULL) {
                    printf("Erro ao ler data!\n");
                    break;
                }
                dataFim[strcspn(dataFim, "\n")] = '\0'; // remove \n

                int d1, m1, a1, d2, m2, a2;

                // Usar sscanf direto em variáveis inteiras para validação mais simples
                if (sscanf(dataInicio, "%d/%d/%d", &d1, &m1, &a1) != 3) {
                    printf("Formato inválido da data de início!\n");
                    break;
                }
                if (sscanf(dataFim, "%d/%d/%d", &d2, &m2, &a2) != 3) {
                    printf("Formato inválido da data final!\n");
                    break;
                }

                // Ajuste para tm struct (meses 0-11, anos desde 1900)
                struct tm inicio = {0}, fim = {0};
                inicio.tm_mday = d1;
                inicio.tm_mon = m1 - 1;
                inicio.tm_year = a1 - 1900;
                fim.tm_mday = d2;
                fim.tm_mon = m2 - 1;
                fim.tm_year = a2 - 1900;

                time_t t_inicio = mktime(&inicio);
                time_t t_fim = mktime(&fim);

                if (t_inicio == -1 || t_fim == -1) {
                    printf("Erro ao converter datas!\n");
                    break;
                }

                double diff_secs = difftime(t_fim, t_inicio);
                int dias = (int)(diff_secs / (60 * 60 * 24));

                if (dias <= 0) {
                    printf("Período inválido! A data final deve ser após a data de início.\n");
                    break;
                }

                // Preenche a locação
                struct Locacao novaLocacao;
                novaLocacao.codigoloc = qntdlocacoes + 1;
                novaLocacao.codigoVeiculo = codigoVeiculo;
                novaLocacao.codigoCliente = codigoCliente;
                strcpy(novaLocacao.dataInicio, dataInicio);
                strcpy(novaLocacao.dataFim, dataFim);
                novaLocacao.valorTotal = veiculos[indexVeiculo].precoPorDia * dias;

                locacoes[qntdlocacoes] = novaLocacao;
                qntdlocacoes++;

                printf("\nLocação registrada com sucesso!\n");
                printf("Quantidade de dias: %d\n", dias);
                printf("Valor total: R$ %.2f\n", novaLocacao.valorTotal);
                system("pause");
                return;
            }
            case 2:
                listarVeiculo();
                break;
            case 3:
                listarClientes();
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}




void cadastrarVeiculo(){
    limparBuffer();
    int placaValida = 0;

    if (qntdVeiculos >= MAXVEICULOS - 1) {
        printf("Quantidade de veículos cadastrados atingiu o limite aceito!\nRemova algum veículo para conseguir adicionar mais!");
        return;
    }
    
    int veiculoIndex = qntdVeiculos;
    printf("\\----------------------------------------//\n");
    printf("\nCadastrar Novo Veículo:\n");
    
    veiculos[veiculoIndex].codigo = veiculoIndex + 1;

    printf("Modelo: ");
    fgets(veiculos[veiculoIndex].modelo, sizeof(veiculos[veiculoIndex].modelo), stdin);
    veiculos[veiculoIndex].modelo[strcspn(veiculos[veiculoIndex].modelo, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &veiculos[veiculoIndex].ano);
    limparBufferDentro();
    
	do {
        printf("Placa: ");
        fgets(veiculos[veiculoIndex].placa, sizeof(veiculos[veiculoIndex].placa), stdin);
        veiculos[veiculoIndex].placa[strcspn(veiculos[veiculoIndex].placa, "\n")] = '\0';

        placaValida = validarPlaca(veiculos[veiculoIndex].placa);

        if (!placaValida) printf("Placa invalida! Use o formato ABC1D23 ou ABC1234\n");
    } while (!placaValida);

    printf("Valor da diária: ");
    scanf("%f", &veiculos[veiculoIndex].precoPorDia);

	salvarDados();

    printf("\nVeículo Cadastrado com Sucesso!\n");
    qntdVeiculos++;
    printf("\\----------------------------------------//\n");
}
void removerVeiculo(){
    if (qntdVeiculos == 0) {printf("\nCadastre Algum Carro Primeiro! "); return;}

    printf("\nVeículos Cadastrados no Sistema: ");
    for (int i =0; i < qntdVeiculos; i++){
        printf("\nVeículos: %s", veiculos[i].modelo);
        printf("\nAno: %d", veiculos[i].ano);
        printf("\nPlaca: %s", veiculos[i].placa);
        printf("\nCódigo: %d", veiculos[i].codigo);
        printf("\nPreço por dia: %f\n", veiculos[i].precoPorDia);
    }

    char buscaRemove[50];
    int buscaRemoveCodigo;
    printf("\nDigite o código ou modelo do veículo para ser removido: ");
    fgets(buscaRemove, 50, stdin);
    
    buscaRemoveCodigo = atoi(buscaRemove);
    
    buscaRemove[strcspn(buscaRemove, "\n")] = '\0'; // Tou removendo a quebra de linha adicionada ao usar Fgets

    for (int i =0; i < qntdVeiculos; i++){ 
        if(_stricmp(buscaRemove, veiculos[i].modelo) == 0 || buscaRemoveCodigo == veiculos[i].codigo){
            printf("\nVeículo %s: Removido com Sucesso!", buscaRemove);
            veiculos[i] = veiculos[qntdVeiculos -1];
            qntdVeiculos--;
            return;
        }
    } printf("\nVeículo não encontrado no Sistema! ");
}
void listarVeiculo(){
}
void simular(){
}
void cadastrarCliente(){
    limparBuffer();

    if (qntdClientes >= MAXCLIENTES - 1) {
        printf("Quantidade de clientes cadastrados atingiu o limite aceito!\nRemova algum cliente para conseguir adicionar mais!");
        return;
    }
    
    int clienteIndex = qntdClientes;
    printf("\\\\----------------------------------------//\n");
    printf("\nCadastrar Novo Cliente:\n");
    
    clientes[clienteIndex].codigo = clienteIndex + 1;

    printf("Nome: ");
    fgets(clientes[clienteIndex].nome, sizeof(clientes[clienteIndex].nome), stdin);
    clientes[clienteIndex].nome[strcspn(clientes[clienteIndex].nome, "\n")] = '\0';

    do {
        printf("CPF: ");
        fgets(clientes[clienteIndex].cpf, sizeof(clientes[clienteIndex].cpf), stdin);
        clientes[clienteIndex].cpf[strcspn(clientes[clienteIndex].cpf, "\n")] = '\0';

        if (strlen(clientes[clienteIndex].cpf) != 11) printf("CPF Inválido!\n");
    } while (strlen(clientes[clienteIndex].cpf) != 11);

    printf("Senha: ");
    fgets(clientes[clienteIndex].senha, sizeof(clientes[clienteIndex].senha), stdin);
    clientes[clienteIndex].senha[strcspn(clientes[clienteIndex].senha, "\n")] = '\0';
    
    qntdClientes++;  
    salvarDados();
    printf("\nCliente Cadastrado com Sucesso!\n");
    sleep(1);

    printf("\\----------------------------------------//\n");
}

void encerrarLocacao(){
}
void listarLocacoesAtivas(){
    if (qntdlocacoes == 0){
        printf("\nAinda Não há Locações !");
        sleep(3);
        system("cls");
    }
    else{
        printf("\n===== Locações =====\n");
        for(int i = 0; i < qntdlocacoes; i++){
            int idcliente = locacoes[i-1].codigoCliente;
            int idveiculo = locacoes[i-1].codigoVeiculo;
            printf("\n %i- cliente : %s \n Veículo: %s \n Data da locação: %s até %s \n Valor Total: R$ %.2f",
                i + 1,
                clientes[idcliente].nome,
                veiculos[idveiculo].modelo,
                locacoes[i].dataInicio,
                locacoes[i].dataFim,
                locacoes[i].valorTotal);
            printf("\n__________________");
        }
    }
    system("pause");
}

void buscarLocacoesAtivasPorCliente(){

}
void buscarLocacoesAtivasPorVeiculo(){
    if (qntdlocacoes==0){
        printf("\nAinda Não há Locações !");
        sleep(3);
        system("cls");
        }
    else{
    limparBuffer();
    char carro[50],nomecliente[60];
    int codecar;

    limparBuffer();
    printf("\nDigite o Nome do Veículo: ");
    fgets(carro, sizeof(carro), stdin);
    carro[strcspn(carro, "\n")] = 0;

    for(int i=0;i<qntdlocacoes;i++){
        if(_stricmp(veiculos[i].modelo , carro)==0){
            codecar = veiculos[i].codigo;
        }
    }
    printf("\nLocações encontradas: ");
    for(int i=0;i<qntdlocacoes;i++){
        for(int j=0;j<qntdlocacoes;j++){
        if(locacoes[i].codigoCliente == clientes[j].codigo){
            strcpy(nomecliente,clientes[j].nome);
            break;
        }}
        if(locacoes[i].codigoVeiculo == codecar){
            printf("\n\n %i- cliente: %s \n Data de inicio: %s\n Término da Locação: %s",locacoes[i].codigoloc,nomecliente,locacoes[i].dataInicio,locacoes[i].dataFim);
            printf("\\\\__________________________//");
        }
    }
}
}
void listarLocacoesEFaturamentoPorPeriodo(){
}
void encerrar(){
    printf("\n\nSaindo do Sistema");
   for (int i =0; i < 5; i++) {
    printf(".");
    sleep(2);
   }
}

int menu();

void login() {
	carregarDados();
    char email[50], senha[40];
    printf("Login\n");

    while (1) {
        printf("\nE-mail: ");
        fgets(email, (50), stdin);
        printf("\nSenha: ");
        fgets(senha, (40), stdin);

        email[strcspn(email, "\n")] = '\0';
        senha[strcspn(senha, "\n")] = '\0';

        if (strcmp(email, "login@gmail.com") == 0 && strcmp(senha, "12345") == 0) {
            menu();
            break;
        } else {
            printf("\nE-mail ou senha incorreta!\n");
        }
    }
}

int menu() {
    system("cls");
    int opcao;
    printf("Bem-vindo ao sistema de aluguel de veículos!\n");
    sleep(2);

    while (1) {
        limparBuffer();
        printf("\\----------------------------------------//\n");
        printf("\nMenu:\n");

        printf("\n 1 - Fazer uma locação");                       
        printf("\n 2 - Cadastrar veículos");
        printf("\n 3 - Remover veículos");
        printf("\n 4 - Listar veículos disponíveis");
        printf("\n 5 - Listar clientes");
        printf("\n 6 - Simular uma locação");
        printf("\n 7 - Cadastrar cliente");
        printf("\n 8 - Encerrar locações");
        printf("\n 9 - Listar todas as locações ativas");
        printf("\n10 - Buscar locações ativas por cliente");
        printf("\n11 - Buscar locações ativas por veículo");
        printf("\n12 - Listar locações e faturamento por período");
        printf("\n13 - Encerrar\n");
        printf("\\\\----------------------------------------//\n");

        printf("\nOpcao: ");
        scanf("%i", &opcao);
        limparBufferDentro();

        switch (opcao) {
            case 1:
                locar();
                break;
            case 2:
                cadastrarVeiculo();
                break;
            case 3:
                removerVeiculo();
                break;
            case 4:
                listarVeiculo();
                break;
            case 5:
                listarClientes();
                break;
            case 6:
                simular();
                break;
            case 7:
                cadastrarCliente();
                break;
            case 8:
                encerrarLocacao();
                break;
            case 9:
                listarLocacoesAtivas();
                break;
            case 10:
                buscarLocacoesAtivasPorCliente();
                break;
            case 11:
                buscarLocacoesAtivasPorVeiculo();
                break;
            case 12:
                listarLocacoesEFaturamentoPorPeriodo();
                break;
            case 13:
                encerrar();
                return 0;
            default:
                erro();
                break;
        }
        clearDelay();
    }
}




int main() {
    setlocale(LC_ALL, "");
    login();
    return (0);
}
