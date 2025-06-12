#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MAXVEICULOS 100
#define MAXCLIENTES 100
#define MAXLOCACOES 200
#define ARQUIVO_VEICULOS "veiculos.dat"
#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_LOCACOES "locacoes.dat"

#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AMARELO "\x1b[33m"
#define AZUL "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO "\x1b[36m"
#define RESET "\x1b[0m"

int qntdLocacoes = 0, qntdClientes = 0, qntdVeiculos = 0;

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

void listarVeiculo();
int menu();

void pressAnyKey() {
    printf("\n\n");
    system("pause");
}

void erro(){
    printf(VERMELHO "Opção inválida! Digite Novamente\n" RESET);
}
void erroCadastro() {
    printf(VERMELHO "\nCadastre Veículos/Clientes Primeiro !\n" RESET);
}
void erroCodigo(){
    printf(VERMELHO "\nCódigo Inválido!" RESET);
}
void erroCliente(){
    printf(VERMELHO "\nCliente Não encontrado no Sistema!" RESET);
}
void erroVeiculo(){
    printf(VERMELHO "\nVeículo Não encontrado no Sistema!" RESET);
}
void erroLocar(){
    printf(VERMELHO "\nLocação Não encontrada no Sistema!" RESET);
}
void erroCadastrarVeiculo(){
    printf(VERMELHO"Cadastre Algum Veículo Primeiro!"RESET);
}
void erroCadastrarLocacao(){
    printf(VERMELHO"Cadastre Alguma Locação Primeiro!"RESET);
}
void erroCadastrarCliente(){
    printf(VERMELHO"Cadastre Algum Cliente Primeiro! "RESET);
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

    arquivo = fopen(ARQUIVO_LOCACOES, "wb");
    if (arquivo) {
        fwrite(&qntdLocacoes, sizeof(int), 1, arquivo);
        fwrite(locacoes, sizeof(struct Locacao), qntdLocacoes, arquivo);
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
    
    arquivo = fopen(ARQUIVO_LOCACOES, "rb");
    if (arquivo) {
        fread(&qntdLocacoes, sizeof(int), 1, arquivo);
        fread(locacoes, sizeof(struct Locacao), qntdLocacoes, arquivo);
        fclose(arquivo);
    }
}
void limparDados() {
    if (qntdVeiculos == 0 && qntdLocacoes == 0 && qntdClientes == 0) {
        printf(VERMELHO "\nNão Há Dados para ser Limpado!" RESET);
        return;
    }
    
    char confirmarApagar[50];
    bool apagar = false;
    printf(AMARELO"\nTem certeza que quer apagar todos os dados? (S/N): "RESET);
    scanf("%s", confirmarApagar);

    while(true){
        if (_stricmp(confirmarApagar, "S") ==0 || _stricmp(confirmarApagar, "SIM") ==0){
            apagar = true;
            break;
        }
        else if(_stricmp(confirmarApagar, "N") ==0 || _stricmp(confirmarApagar, "NÃO") ==0 || _stricmp(confirmarApagar, "NAO") ==0 || _stricmp(confirmarApagar, "Ñ") ==0){
            break;
        }
        else{
            erro();
        }
    }

    if(apagar){
        printf("\n\nApagando Dados do Sistema");
        for (int i = 0; i < 3; i++){
            printf(".");
            sleep(1);
        }
        printf("\nDados Apagados com Sucesso! ");
         FILE *arquivo;

    arquivo = fopen(ARQUIVO_VEICULOS, "wb");
    if (arquivo) {
        fclose(arquivo);
    }

    arquivo = fopen(ARQUIVO_CLIENTES, "wb");
    if (arquivo) {
        fclose(arquivo);
    }

    arquivo = fopen(ARQUIVO_LOCACOES, "wb");
    if (arquivo) {
        fclose(arquivo);
    }

    qntdVeiculos = 0;
    qntdClientes = 0;
    qntdLocacoes = 0;
    }
   
}

int validarPlaca(char placa[]) {
	if (strlen(placa) != 7) return 0;
    
    for (int i = 0; i < 3; i++) {
        if (!isalpha(placa[i])) return 0;
    }
    
    if (!isdigit(placa[3])) return 0;

    if(!isdigit(placa[4]) && !isalpha(placa[4])) return 0;
    
    if (!isdigit(placa[5]) || !isdigit(placa[6])) return 0;
    
    return 1;
}
void listarClientes() {
    if (qntdClientes == 0){
        erroCadastrarCliente();
        return;
    }
    printf("==== Clientes ====\n");
    for (int i = 0; i < qntdClientes; i++) {
        printf("\n %d - Cliente: %s", i + 1, clientes[i].nome);
        printf("\n Código: %d", clientes[i].codigo);
        printf("\n CPF: %s", clientes[i].cpf);
    }

    pressAnyKey();
}

void locar() {
    if (qntdVeiculos == 0 || qntdClientes == 0) {
        erroCadastro();
        return;
    }

    char input[20];
    int op;

    while (1) {
        printf("\nEscolha uma opção: ");
        printf("\n1 - Locar");
        printf("\n2 - Listar veículos disponíveis");
        printf("\n3 - Listar clientes ");
        printf("\n4 - Voltar ao menu principal\n\nOpção: ");
        
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &op) != 1) {
            printf(VERMELHO "\nEntrada inválida! Tente novamente.\n" RESET);
            continue;
        }

        switch (op) {
            case 1: {
                int codigoVeiculo, codigoCliente;
                char dataInicio[20], dataFim[20]; 

                printf("Código do Veículo: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &codigoVeiculo) != 1) {
                    erroCodigo();
                    break;
                }

                int indexVeiculo = -1;
                for (int i = 0; i < qntdVeiculos; i++) {
                    if (veiculos[i].codigo == codigoVeiculo) {
                        indexVeiculo = i;
                        break;
                    }
                }
                if (indexVeiculo == -1) {
                    erroVeiculo();
                    break;
                }

                for (int i = 0; i < qntdLocacoes; i++) {
                    if (locacoes[i].codigoVeiculo == codigoVeiculo) {
                        printf(VERMELHO "\nEste veículo já está locado!\n" RESET);
                        return;
                    }
                }

                printf("Código do Cliente: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &codigoCliente) != 1) {
                    erroCodigo();
                    break;
                }

                
                int indexCliente = -1;
                for (int i = 0; i < qntdClientes; i++) {
                    if (clientes[i].codigo == codigoCliente) {
                        indexCliente = i;
                        break;
                    }
                }
                if (indexCliente == -1) {
                    erroCliente();
                    break;
                }

                printf("Data de início da Locação (dd/mm/aaaa): ");
                if (fgets(dataInicio, sizeof(dataInicio), stdin) == NULL) {
                    printf(VERMELHO "Erro ao ler data!\n" RESET);
                    break;
                }
                dataInicio[strcspn(dataInicio, "\n")] = '\0'; 

                printf("Data Final da Locação (dd/mm/aaaa): ");
                if (fgets(dataFim, sizeof(dataFim), stdin) == NULL) {
                    printf(VERMELHO "Erro ao ler data!\n" RESET);
                    break;
                }
                dataFim[strcspn(dataFim, "\n")] = '\0'; 

                int d1, m1, a1, d2, m2, a2;

                if (sscanf(dataInicio, "%d/%d/%d", &d1, &m1, &a1) != 3) {
                    printf(VERMELHO"Formato inválido da data de início!\n" RESET);
                    break;
                }
                if (sscanf(dataFim, "%d/%d/%d", &d2, &m2, &a2) != 3) {
                    printf(VERMELHO"Formato inválido da data final!\n" RESET);
                    break;
                }

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
                    printf(VERMELHO "Erro ao converter datas!\n" RESET);
                    break;
                }

                double diff_secs = difftime(t_fim, t_inicio);
                int dias = (int)(diff_secs / (60 * 60 * 24));

                if (dias <= 0) {
                    printf(VERMELHO "Período inválido! A data final deve ser após a data de início.\n" RESET);
                    break;
                }

                struct Locacao novaLocacao;
                novaLocacao.codigoloc = qntdLocacoes + 1;
                novaLocacao.codigoVeiculo = codigoVeiculo;
                novaLocacao.codigoCliente = codigoCliente;
                strcpy(novaLocacao.dataInicio, dataInicio);
                strcpy(novaLocacao.dataFim, dataFim);
                novaLocacao.valorTotal = veiculos[indexVeiculo].precoPorDia * dias;

                locacoes[qntdLocacoes] = novaLocacao;
                qntdLocacoes++;
                salvarDados();

                printf("\nLocação registrada com sucesso!\n");
                printf("Quantidade de dias: %d\n", dias);
                printf("Valor total: R$ %.2f\n", novaLocacao.valorTotal);
                system("pause");

                salvarDados();
                return;
            }
            case 2:
                listarVeiculo();
                break;
            case 3:
                listarClientes();
                break;
            case 4:
                return;
            default:
                erro();
                break;
        }
    }
}

void cadastrarVeiculo(){
    limparBuffer();
    int placaValida = 0;

    if (qntdVeiculos >= MAXVEICULOS - 1) {
        printf(VERMELHO "Quantidade de veículos cadastrados atingiu o limite aceito!\nRemova algum veículo para conseguir adicionar mais!" RESET);
        return;
    }
    
    int veiculoIndex = qntdVeiculos;
    printf("\\\\----------------------------------------//\n");
    printf(CIANO"\nCadastrar Novo Veículo\n"RESET);
    
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

        if (!placaValida) printf(AMARELO"Placa invalida! Use o formato ABC1D23 ou ABC1234\n"RESET);
    } while (!placaValida);

    printf("Valor da diária: ");
    scanf("%f", &veiculos[veiculoIndex].precoPorDia);
    qntdVeiculos++;

	salvarDados();
    system("cls");
    printf(VERDE"\nVeículo Cadastrado com Sucesso!\n"RESET);
}
void removerVeiculo(){
    if (qntdVeiculos == 0){
        erroCadastrarVeiculo();
        return;
    }
    listarVeiculo();

    int buscaRemoveCodigo;
    printf("\nDigite o código do Veículo para ser removido: ");
    scanf("%d", &buscaRemoveCodigo);
    
    for (int i =0; i < qntdVeiculos; i++){ 
        if(buscaRemoveCodigo == veiculos[i].codigo){
            printf(VERDE"\nVeículo Removido com Sucesso!"RESET);
            veiculos[i] = veiculos[qntdVeiculos -1];
            qntdVeiculos--;
            salvarDados();
            return;
        }
    } erroVeiculo();
}

void listarVeiculo(){
    if (qntdVeiculos == 0) {
        erroCadastrarVeiculo(); 
        return;
    }
        printf(CIANO"\n==== Veículos Cadastrados no Sistema ====\n"RESET);
        for (int i =0; i < qntdVeiculos; i++){
            printf("\nVeículo: %s", veiculos[i].modelo);
            printf("\nAno: %d", veiculos[i].ano);
            printf("\nPlaca: %s", veiculos[i].placa);
            printf("\nCódigo: %d", veiculos[i].codigo);
            printf("\nPreço por dia: %.2f\n", veiculos[i].precoPorDia);
            printf("\n--------------------------\n");
    }
}
void simular(){
     if (qntdVeiculos == 0) {
        erroCadastro();
        return;
    }

    listarVeiculo();

    printf(CIANO"\n==== Simulação ===="RESET);
    int codigoVeiculo, dias;
    printf("\n\nCódigo do veículo: ");
    scanf("%d", &codigoVeiculo);
    limparBufferDentro();

    int indexVeiculo = -1;
    for (int i = 0; i < qntdVeiculos; i++) {
        if (veiculos[i].codigo == codigoVeiculo) {
            indexVeiculo = i;
            printf(CIANO"\nVeículo Selecionado\n"RESET);
            printf("\nVeículo: %s", veiculos[i].modelo);
            printf("\nAno: %d", veiculos[i].ano);
            printf("\nPlaca: %s", veiculos[i].placa);
            printf("\nCódigo: %d", veiculos[i].codigo);
            printf("\nPreço por dia: %.2f\n", veiculos[i].precoPorDia);
            printf("\n--------------------------\n");
            break;
        }
    }

    if (indexVeiculo == -1) {
        erroVeiculo();
        return;
    }

    printf("\nQuantidade de dias: ");
    scanf("%d", &dias);
    limparBufferDentro();

    if (dias <= 0) {
        printf(VERMELHO"\nQuantidade de dias inválida!\n" RESET);
        return;
    }

    float total = veiculos[indexVeiculo].precoPorDia * dias;
    char confirmarLocacao[50];

    printf("\nValor estimado da locação por %d dias: R$ %.2f\n", dias, total);
    printf(AMARELO"\nDeseja Continuar para a Locação? (S/N): "RESET);
    fgets(confirmarLocacao, sizeof(confirmarLocacao), stdin);
    confirmarLocacao[strcspn(confirmarLocacao, "\n")] = '\0';

    while(true){
        if (_stricmp(confirmarLocacao, "S") ==0 || _stricmp(confirmarLocacao, "SIM") ==0){
            locar();
        }
        else if(_stricmp(confirmarLocacao, "N") ==0 || _stricmp(confirmarLocacao, "NÃO") ==0 || _stricmp(confirmarLocacao, "NAO") ==0 || _stricmp(confirmarLocacao, "Ñ") ==0){
            break;
        }
        else{
            erro();
        }
    }
    
    
    pressAnyKey();

    
}
void cadastrarCliente(){
    limparBuffer();

    if (qntdClientes >= MAXCLIENTES - 1) {
        printf("Quantidade de clientes cadastrados atingiu o limite aceito!\nRemova algum cliente para conseguir adicionar mais!");
        return;
    }
    
    int clienteIndex = qntdClientes;
    printf("\\\\----------------------------------------//\n");
    printf("\nCadastrar Novo Cliente\n");
    
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
    printf(VERDE"\nCliente Cadastrado com Sucesso!\n"RESET);
    sleep(1);

    printf("\\----------------------------------------//\n");
}

void encerrarLocacao(){
    if (qntdLocacoes == 0) {
        erroCadastrarLocacao();
        return;
    }

    int codigoLoc;
    printf("\nDigite o código da locação que deseja encerrar: ");
    scanf("%d", &codigoLoc);
    limparBufferDentro();

    int indexLocacao = -1;
    for (int i = 0; i < qntdLocacoes; i++) {
        if (locacoes[i].codigoloc == codigoLoc) {
            indexLocacao = i;
            break;
        }
    }

    if (indexLocacao == -1) {
        erroLocar();
        return;
    }

    printf("\nLocação encerrada com sucesso!");
    printf("\nCliente: %d", locacoes[indexLocacao].codigoCliente);
    printf("\nVeículo: %d", locacoes[indexLocacao].codigoVeiculo);
    printf("\nData início: %s", locacoes[indexLocacao].dataInicio);
    printf("\nData fim: %s", locacoes[indexLocacao].dataFim);
    printf("\nValor total: R$ %.2f", locacoes[indexLocacao].valorTotal);

    // Remove a locação encerrada do array
    locacoes[indexLocacao] = locacoes[qntdLocacoes - 1];  // sobrescreve com a última
    qntdLocacoes--;
    salvarDados();

    printf("\n\nLocação removida do sistema com sucesso.\n");
    system("pause");
}
void listarLocacoesAtivas() {
    if (qntdLocacoes == 0) {
        erroCadastrarLocacao();
        return;
    }

    for (int i = 0; i < qntdClientes; i++) {
        int clienteTemLocacao = 0;

        for (int l = 0; l < qntdLocacoes; l++) {
            if (locacoes[l].codigoCliente == clientes[i].codigo) {
                if (!clienteTemLocacao) {
                    printf(CIANO"\n\n===== Informações do Cliente ====="RESET);
                    printf("\n Nome: %s", clientes[i].nome);
                    printf("\n Senha: %s", clientes[i].senha);
                    printf("\n CPF: %s", clientes[i].cpf);
                    printf("\n Código: %d", clientes[i].codigo);
                    clienteTemLocacao = 1;
                }

                for (int v = 0; v < qntdVeiculos; v++) {
                    if (veiculos[v].codigo == locacoes[l].codigoVeiculo) {
                        printf(CIANO"\n\n--- Veículo Alugado ---"RESET);
                        printf("\n Modelo: %s", veiculos[v].modelo);
                        printf("\n Ano: %d", veiculos[v].ano);
                        printf("\n Código: %d", veiculos[v].codigo);
                        printf("\n Placa: %s", veiculos[v].placa);
                        printf("\n Preço por Dia: R$ %.2f", veiculos[v].precoPorDia);
                        break;
                    }
                }

                printf(CIANO"\n\n--- Dados da Locação ---"RESET);
                printf("\n Código do Cliente: %d", locacoes[l].codigoCliente);
                printf("\n Código da Locação: %d", locacoes[l].codigoloc);
                printf("\n Código do Veículo: %d", locacoes[l].codigoVeiculo);
                printf("\n Data Inicial: %s", locacoes[l].dataInicio);
                printf("\n Data Final: %s", locacoes[l].dataFim);
                printf("\n Valor Total: R$ %.2f", locacoes[l].valorTotal);
            }
        }
    }
            pressAnyKey();
}


void buscarLocacoesAtivasPorCliente() {
    if (qntdLocacoes == 0){
        erroCadastrarLocacao();
        return;
    }

    listarLocacoesAtivas();

    char buscarCliente[50];
    int buscarClienteCodigo;
    bool clienteEncontrado = false;

    printf("\nDigite o nome do Cliente ou o código: ");
    fgets(buscarCliente, sizeof(buscarCliente), stdin);
    buscarCliente[strcspn(buscarCliente, "\n")] = 0;

    buscarClienteCodigo = atoi(buscarCliente);

    for (int i = 0; i < qntdClientes; i++) {
        if (_stricmp(buscarCliente, clientes[i].nome) == 0 || buscarClienteCodigo == clientes[i].codigo) {
            clienteEncontrado = true;
            printf("\nCliente: %s Encontrado Com Sucesso!", clientes[i].nome);

            printf(CIANO"\n==== Informações do Cliente ===="RESET);

            printf("\n\nDados do cliente:");
            printf("\n Nome do cliente: %s", clientes[i].nome);
            printf("\n Senha: %s", clientes[i].senha);
            printf("\n CPF: %s", clientes[i].cpf);
            printf("\n Código: %d", clientes[i].codigo);

            bool locacaoEncontrada = false;
            for (int l = 0; l < qntdLocacoes; l++) {
                if (locacoes[l].codigoCliente == clientes[i].codigo) {
                    locacaoEncontrada = true;

                    for (int v = 0; v < qntdVeiculos; v++) {
                        if (veiculos[v].codigo == locacoes[l].codigoVeiculo) {
                            printf("\n\nDados do Veículo Alugado:");
                            printf("\n Modelo do Veículo: %s", veiculos[v].modelo);
                            printf("\n Ano do Veículo: %d", veiculos[v].ano);
                            printf("\n Código do Veículo: %d", veiculos[v].codigo);
                            printf("\n Placa do Veículo: %s", veiculos[v].placa);
                            printf("\n Preço por Dia: %.2f", veiculos[v].precoPorDia);
                            break;
                        }
                    }

                    printf("\n\nDados da Locação:");
                    printf("\n Código do Cliente: %d", locacoes[l].codigoCliente);
                    printf("\n Código da Locação: %d", locacoes[l].codigoloc);
                    printf("\n Código do Veículo: %d", locacoes[l].codigoVeiculo);
                    printf("\n Data Inicial: %s", locacoes[l].dataInicio);
                    printf("\n Data Final: %s", locacoes[l].dataFim);
                    printf("\n Valor Total da Locação: %.2f", locacoes[l].valorTotal);
                }
            }

            if (!locacaoEncontrada) {
                erroLocar();
            }

            pressAnyKey();
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("\nCliente não encontrado no sistema!");
    }
}


void buscarLocacoesAtivasPorVeiculo(){
    if (qntdLocacoes==0){
        erroCadastrarLocacao();
        }
    else{
    limparBuffer();
    char carro[50],nomecliente[60];
    int codecar;

    limparBuffer();
    printf("\nDigite o Nome do Veículo: ");
    fgets(carro, sizeof(carro), stdin);
    carro[strcspn(carro, "\n")] = 0;

    for(int i=0;i<qntdLocacoes;i++){
        if(_stricmp(veiculos[i].modelo , carro)==0){
            codecar = veiculos[i].codigo;
        }
    }

    printf("\nLocações encontradas: ");
    for(int i=0;i<qntdLocacoes;i++){
        for(int j=0;j<qntdLocacoes;j++){
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
void listarLocacoesEFaturamentoPorPeriodo() {
    if (qntdLocacoes == 0) {
        erroCadastrarLocacao();
        return;
    }

    char dataInicioStr[15], dataFimStr[15];
    int d1, m1, a1, d2, m2, a2;

    printf("\nInforme o período para consulta:");
    
    printf("\nData inicial (dd/mm/aaaa): ");
    fgets(dataInicioStr, sizeof(dataInicioStr), stdin);
    dataInicioStr[strcspn(dataInicioStr, "\n")] = '\0';
    
    if (sscanf(dataInicioStr, "%d/%d/%d", &d1, &m1, &a1) != 3) {
        printf("Formato de data inválido!\n");
        system("pause");
        return;
    }

    printf("Data final (dd/mm/aaaa): ");
    fgets(dataFimStr, sizeof(dataFimStr), stdin);
    dataFimStr[strcspn(dataFimStr, "\n")] = '\0';
    
    if (sscanf(dataFimStr, "%d/%d/%d", &d2, &m2, &a2) != 3) {
        printf("Formato de data inválido!\n");
        system("pause");
        return;
    }
    system("cls");

    struct tm tm_inicio = {0}, tm_fim = {0};
    tm_inicio.tm_mday = d1;
    tm_inicio.tm_mon = m1 - 1;
    tm_inicio.tm_year = a1 - 1900;
    
    tm_fim.tm_mday = d2;
    tm_fim.tm_mon = m2 - 1;
    tm_fim.tm_year = a2 - 1900;
    
    time_t inicio = mktime(&tm_inicio);
    time_t fim = mktime(&tm_fim);

    if (inicio == -1 || fim == -1) {
        printf(VERMELHO"Erro ao converter datas!\n"RESET);
        system("pause");
        return;
    }

    if (difftime(fim, inicio) < 0) {
        printf(AMARELO"Data final deve ser após data inicial!\n"RESET);
        system("pause");
        return;
    }

    printf("\n==== Locações no período %s a %s ====\n", dataInicioStr, dataFimStr);
    
    float faturamentoTotal = 0;
    int locacoesEncontradas = 0;

    for (int i = 0; i < qntdLocacoes; i++) {
        int dl, ml, al;
        if (sscanf(locacoes[i].dataInicio, "%d/%d/%d", &dl, &ml, &al) != 3) {
            continue; 
        }

        struct tm tm_loc = {0};
        tm_loc.tm_mday = dl;
        tm_loc.tm_mon = ml - 1;
        tm_loc.tm_year = al - 1900;
        time_t dataLoc = mktime(&tm_loc);

        if (dataLoc >= inicio && dataLoc <= fim) {
            int clienteIdx = -1, veiculoIdx = -1;
            
            for (int j = 0; j < qntdClientes; j++) {
                if (clientes[j].codigo == locacoes[i].codigoCliente) {
                    clienteIdx = j;
                    break;
                }
            }
            
            for (int j = 0; j < qntdVeiculos; j++) {
                if (veiculos[j].codigo == locacoes[i].codigoVeiculo) {
                    veiculoIdx = j;
                    break;
                }
            }

            printf("\nLocação %d", locacoes[i].codigoloc);
            printf("\n\nCliente: %s", (clienteIdx != -1) ? clientes[clienteIdx].nome : "N/A");
            printf("\nVeículo: %s", (veiculoIdx != -1) ? veiculos[veiculoIdx].modelo : "N/A");
            printf("\nPeríodo: %s a %s", locacoes[i].dataInicio, locacoes[i].dataFim);
            printf("\nValor: R$ %.2f", locacoes[i].valorTotal);
            printf("\n----------------------------------\n");

            faturamentoTotal += locacoes[i].valorTotal;
            locacoesEncontradas++;
        }
    }

    if (locacoesEncontradas == 0) {
        printf("\nNenhuma locação encontrada neste período.\n");
    } else {
        printf("\nFaturamento total no período: R$ %.2f\n\n", faturamentoTotal);
    }

    system("pause");
}

void encerrar(){
    const char *cores[] = {VERMELHO, VERDE, AMARELO, AZUL, MAGENTA};
    
    printf(CIANO"\nSaindo do Sistema"RESET);

    for (int i = 0; i < 5; i++) {
        printf("%s.%s", cores[i], RESET);
        sleep(1);
    }
   printf(CIANO"\n\nAgradecemos Por Utilizar nosso Sistema!" RESET);
}

void login() {
	carregarDados();

    printf(AZUL"\n==========================="RESET);
    printf("\n         LOCAFAST       ");
    printf(AZUL"\n==========================="RESET);
    char email[50], senha[40];
    printf("\nLogin");

    while (1) {
        printf("\nE-mail: ");
        fgets(email, (50), stdin);
        printf("Senha: ");
        fgets(senha, (40), stdin);

        email[strcspn(email, "\n")] = '\0';
        senha[strcspn(senha, "\n")] = '\0';

        if (strcmp(email, "login@gmail.com") == 0 && strcmp(senha, "12345") == 0) {
            menu();
            break;
        } else {
            printf(AMARELO"\nE-mail ou senha incorreta!\n"RESET);
        }
    }
}

int menu() {
    system("cls");
    int opcao;
    printf(VERDE"Bem-vindo ao sistema de aluguel de veículos!\n"RESET);
    sleep(2);

    while (1) {
        limparBuffer();
        printf("\\\\----------------------------------------//\n");
        printf(CIANO"\nMenu:\n"RESET);

        printf("\n 1 - Nova locação");                       
        printf("\n 2 - Cadastrar veículos");
        printf("\n 3 - Remover veículos");
        printf("\n 4 - Listar veículos disponíveis");
        printf("\n 5 - Cadastrar cliente");
        printf("\n 6 - Listar clientes");
        printf("\n 7 - Simular uma locação");
        printf("\n 8 - Encerrar locações");
        printf("\n 9 - Listar todas as locações ativas");
        printf("\n10 - Buscar locações ativas por cliente");
        printf("\n11 - Buscar locações ativas por veículo");
        printf("\n12 - Listar locações e faturamento por período");
        printf("\n13 - Limpar Dados");
        printf("\n14 - Encerrar\n\n");
        printf("\\\\----------------------------------------//\n");

        printf("\nOpção: ");
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
                pressAnyKey();
                break;
            case 5:
                cadastrarCliente();
                break;
            case 6:
                listarClientes();
                break;
            case 7:
                simular();
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
                limparDados();
                break;
            case 14:
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
    setlocale(LC_ALL, "portuguese");
    login();
    return (0);
}
