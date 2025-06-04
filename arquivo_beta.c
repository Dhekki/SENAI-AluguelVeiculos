// Bibliotecas do Projeto
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

// Defini��es
#define MAXVEICULOS 100
#define MAXCLIENTES 100
#define MAXLOCACOES 200
#define ARQUIVO_VEICULOS "veiculos.dat"
#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_LOCACOES "locacoes.dat"

// Vari�veis Globais (Contadores)
int qntdLocacoes = 0, qntdClientes = 0, qntdVeiculos = 0;

// Struct para armazenamento de Dados
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

// Prot�tipo de Fun��o
void listarVeiculo();
int menu();

// Fun��es Auxili�res
void pressAnyKey() {
    printf("\n\n");
    system("pause");
}

void erro(){
    printf("Op��o inv�lida!\n");
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
    FILE *arquivo;

    // Limpar arquivo de ve�culos
    arquivo = fopen(ARQUIVO_VEICULOS, "wb");
    if (arquivo) {
        fclose(arquivo);
    }

    // Limpar arquivo de clientes
    arquivo = fopen(ARQUIVO_CLIENTES, "wb");
    if (arquivo) {
        fclose(arquivo);
    }

     // Limpar arquivo de loca��es
    arquivo = fopen(ARQUIVO_LOCACOES, "wb");
    if (arquivo) {
        fclose(arquivo);
    }

    // Limpar Vari�veis Globais
    qntdVeiculos = 0;
    qntdClientes = 0;
    qntdLocacoes = 0;
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
    printf("\\\\------------------ Clientes ------------------//\n");
    for (int i = 0; i < qntdClientes; i++) {
        printf("\n %d - Cliente: %s", i + 1, clientes[i].nome);
        printf("\n C�digo: %d", clientes[i].codigo);
        printf("\n CPF: %s", clientes[i].cpf);
        printf("\n-----------------------------------------------");
    }
    printf("\n");
    system("pause");
}

void locar() {
    if (qntdVeiculos == 0 || qntdClientes == 0) {
        printf("\nCadastre Ve�culos/Clientes Primeiro !\n");
        return;
    }

    char input[20];
    int op;

    while (1) {
        printf("\nEscolha uma op��o: ");
        printf("\n1 - Locar");
        printf("\n2 - Listar ve�culos dispon�veis");
        printf("\n3 - Listar clientes ");
        printf("\n4 - Voltar ao menu principal\n\nOp��o: ");
        
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &op) != 1) {
            printf("Entrada inv�lida! Tente novamente.\n");
            continue;
        }

        switch (op) {
            case 1: {
                int codigoVeiculo, codigoCliente;
                char dataInicio[20], dataFim[20]; // espa�o maior para evitar overflow

                printf("C�digo do Ve�culo: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &codigoVeiculo) != 1) {
                    printf("C�digo inv�lido!\n");
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
                    printf("Ve�culo n�o encontrado!\n");
                    break;
                }

                for (int i = 0; i < qntdLocacoes; i++) {
                    if (locacoes[i].codigoVeiculo == codigoVeiculo) {
                        printf("Este ve�culo j� est� locado!\n");
                        return;
                    }
                }

                printf("C�digo do Cliente: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%d", &codigoCliente) != 1) {
                    printf("C�digo inv�lido!\n");
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
                    printf("Cliente n�o encontrado!\n");
                    break;
                }

                printf("Data de in�cio da Loca��o (dd/mm/aaaa): ");
                if (fgets(dataInicio, sizeof(dataInicio), stdin) == NULL) {
                    printf("Erro ao ler data!\n");
                    break;
                }
                dataInicio[strcspn(dataInicio, "\n")] = '\0'; // remove \n

                printf("Data Final da Loca��o (dd/mm/aaaa): ");
                if (fgets(dataFim, sizeof(dataFim), stdin) == NULL) {
                    printf("Erro ao ler data!\n");
                    break;
                }
                dataFim[strcspn(dataFim, "\n")] = '\0'; // remove \n

                int d1, m1, a1, d2, m2, a2;

                if (sscanf(dataInicio, "%d/%d/%d", &d1, &m1, &a1) != 3) {
                    printf("Formato inv�lido da data de in�cio!\n");
                    break;
                }
                if (sscanf(dataFim, "%d/%d/%d", &d2, &m2, &a2) != 3) {
                    printf("Formato inv�lido da data final!\n");
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
                    printf("Erro ao converter datas!\n");
                    break;
                }

                double diff_secs = difftime(t_fim, t_inicio);
                int dias = (int)(diff_secs / (60 * 60 * 24));

                if (dias <= 0) {
                    printf("Per�odo inv�lido! A data final deve ser ap�s a data de in�cio.\n");
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

                printf("\nLoca��o registrada com sucesso!\n");
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
                printf("Op��o inv�lida!\n");
                break;
        }
    }
}

void cadastrarVeiculo(){
    limparBuffer();
    int placaValida = 0;

    if (qntdVeiculos >= MAXVEICULOS - 1) {
        printf("Quantidade de ve�culos cadastrados atingiu o limite aceito!\nRemova algum ve�culo para conseguir adicionar mais!");
        return;
    }
    
    int veiculoIndex = qntdVeiculos;
    printf("\\\\----------------------------------------//\n");
    printf("\nCadastrar Novo Ve�culo:\n");
    
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

    printf("Valor da di�ria: ");
    scanf("%f", &veiculos[veiculoIndex].precoPorDia);

	salvarDados();

    printf("\nVe�culo Cadastrado com Sucesso!\n");
    qntdVeiculos++;
    printf("\\----------------------------------------//\n");
}
void removerVeiculo(){
    listarVeiculo();

    char buscaRemove[50];
    int buscaRemoveCodigo;
    printf("\nDigite o c�digo ou modelo do ve�culo para ser removido: ");
    fgets(buscaRemove, 50, stdin);
    buscaRemove[strcspn(buscaRemove, "\n")] = '\0'; 
    
    buscaRemoveCodigo = atoi(buscaRemove);
    
    for (int i =0; i < qntdVeiculos; i++){ 
        if(_stricmp(buscaRemove, veiculos[i].modelo) == 0 || buscaRemoveCodigo == veiculos[i].codigo){
            printf("\nVe�culo %s: Removido com Sucesso!", veiculos[i].modelo);
            veiculos[i] = veiculos[qntdVeiculos -1];
            qntdVeiculos--;
            salvarDados();
            return;
        }
    } printf("\nVe�culo n�o encontrado no Sistema! ");
}

void listarVeiculo(){
    if (qntdVeiculos == 0) {printf("\nCadastre Algum Carro Primeiro! "); return;}
        printf("\nVe�culos Cadastrados no Sistema: ");
        for (int i =0; i < qntdVeiculos; i++){
            printf("\nVe�culos: %s", veiculos[i].modelo);
            printf("\nAno: %d", veiculos[i].ano);
            printf("\nPlaca: %s", veiculos[i].placa);
            printf("\nC�digo: %d", veiculos[i].codigo);
            printf("\nPre�o por dia: %.2f\n", veiculos[i].precoPorDia);
    }
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

        if (strlen(clientes[clienteIndex].cpf) != 11) printf("CPF Inv�lido!\n");
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
void listarLocacoesAtivas() {
    if (qntdLocacoes == 0) {
        printf("\nAinda n�o h� loca��es!\n");
        return;
    }

    for (int i = 0; i < qntdClientes; i++) {
        int clienteTemLocacao = 0;

        // Verifica se o cliente tem alguma loca��o
        for (int l = 0; l < qntdLocacoes; l++) {
            if (locacoes[l].codigoCliente == clientes[i].codigo) {
                // S� imprime dados do cliente uma vez
                if (!clienteTemLocacao) {
                    printf("\n\n===== Informa��es do Cliente =====");
                    printf("\n Nome: %s", clientes[i].nome);
                    printf("\n Senha: %s", clientes[i].senha);
                    printf("\n CPF: %s", clientes[i].cpf);
                    printf("\n C�digo: %d", clientes[i].codigo);
                    clienteTemLocacao = 1;
                }

                // Buscar o ve�culo correspondente
                for (int v = 0; v < qntdVeiculos; v++) {
                    if (veiculos[v].codigo == locacoes[l].codigoVeiculo) {
                        printf("\n\n--- Ve�culo Alugado ---");
                        printf("\n Modelo: %s", veiculos[v].modelo);
                        printf("\n Ano: %d", veiculos[v].ano);
                        printf("\n C�digo: %d", veiculos[v].codigo);
                        printf("\n Placa: %s", veiculos[v].placa);
                        printf("\n Pre�o por Dia: R$ %.2f", veiculos[v].precoPorDia);
                        break;
                    }
                }

                // Dados da loca��o
                printf("\n\n--- Dados da Loca��o ---");
                printf("\n C�digo do Cliente: %d", locacoes[l].codigoCliente);
                printf("\n C�digo da Loca��o: %d", locacoes[l].codigoloc);
                printf("\n C�digo do Ve�culo: %d", locacoes[l].codigoVeiculo);
                printf("\n Data Inicial: %s", locacoes[l].dataInicio);
                printf("\n Data Final: %s", locacoes[l].dataFim);
                printf("\n Valor Total: R$ %.2f", locacoes[l].valorTotal);
            }
        }

        if (clienteTemLocacao) {
            pressAnyKey();
        }
    }
}


void buscarLocacoesAtivasPorCliente() {
    if (qntdLocacoes == 0){
        printf("\nAinda N�o h� Loca��es !");
        return;
    }

    listarLocacoesAtivas();

    char buscarCliente[50];
    int buscarClienteCodigo;
    bool clienteEncontrado = false;

    printf("\nDigite o nome do Cliente ou o c�digo: ");
    fgets(buscarCliente, sizeof(buscarCliente), stdin);
    buscarCliente[strcspn(buscarCliente, "\n")] = 0;

    buscarClienteCodigo = atoi(buscarCliente);

    for (int i = 0; i < qntdClientes; i++) {
        if (_stricmp(buscarCliente, clientes[i].nome) == 0 || buscarClienteCodigo == clientes[i].codigo) {
            clienteEncontrado = true;
            printf("\nCliente: %s Encontrado Com Sucesso!", clientes[i].nome);

            printf("\nInforma��es do Cliente:");

            printf("\n\nDados do cliente:");
            printf("\n Nome do cliente: %s", clientes[i].nome);
            printf("\n Senha: %s", clientes[i].senha);
            printf("\n CPF: %s", clientes[i].cpf);
            printf("\n C�digo: %d", clientes[i].codigo);

            // Buscar loca��es do cliente
            bool locacaoEncontrada = false;
            for (int l = 0; l < qntdLocacoes; l++) {
                if (locacoes[l].codigoCliente == clientes[i].codigo) {
                    locacaoEncontrada = true;

                    // Buscar ve�culo da loca��o
                    for (int v = 0; v < qntdVeiculos; v++) {
                        if (veiculos[v].codigo == locacoes[l].codigoVeiculo) {
                            printf("\n\nDados do Ve�culo Alugado:");
                            printf("\n Modelo do Ve�culo: %s", veiculos[v].modelo);
                            printf("\n Ano do Ve�culo: %d", veiculos[v].ano);
                            printf("\n C�digo do Ve�culo: %d", veiculos[v].codigo);
                            printf("\n Placa do Ve�culo: %s", veiculos[v].placa);
                            printf("\n Pre�o por Dia: %.2f", veiculos[v].precoPorDia);
                            break;
                        }
                    }

                    printf("\n\nDados da Loca��o:");
                    printf("\n C�digo do Cliente: %d", locacoes[l].codigoCliente);
                    printf("\n C�digo da Loca��o: %d", locacoes[l].codigoloc);
                    printf("\n C�digo do Ve�culo: %d", locacoes[l].codigoVeiculo);
                    printf("\n Data Inicial: %s", locacoes[l].dataInicio);
                    printf("\n Data Final: %s", locacoes[l].dataFim);
                    printf("\n Valor Total da Loca��o: %.2f", locacoes[l].valorTotal);
                }
            }

            if (!locacaoEncontrada) {
                printf("\n\nO cliente n�o possui loca��es registradas.");
            }

            pressAnyKey();
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("\nCliente n�o encontrado no sistema!");
    }
}


void buscarLocacoesAtivasPorVeiculo(){
    if (qntdLocacoes==0){
        printf("\nAinda N�o h� Loca��es !");
        }
    else{
    limparBuffer();
    char carro[50],nomecliente[60];
    int codecar;

    limparBuffer();
    printf("\nDigite o Nome do Ve�culo: ");
    fgets(carro, sizeof(carro), stdin);
    carro[strcspn(carro, "\n")] = 0;

    for(int i=0;i<qntdLocacoes;i++){
        if(_stricmp(veiculos[i].modelo , carro)==0){
            codecar = veiculos[i].codigo;
        }
    }

    printf("\nLoca��es encontradas: ");
    for(int i=0;i<qntdLocacoes;i++){
        for(int j=0;j<qntdLocacoes;j++){
        if(locacoes[i].codigoCliente == clientes[j].codigo){
            strcpy(nomecliente,clientes[j].nome);
            break;
        }}
        if(locacoes[i].codigoVeiculo == codecar){
            printf("\n\n %i- cliente: %s \n Data de inicio: %s\n T�rmino da Loca��o: %s",locacoes[i].codigoloc,nomecliente,locacoes[i].dataInicio,locacoes[i].dataFim);
            printf("\\\\__________________________//");
        }
    }
}
}
void listarLocacoesEFaturamentoPorPeriodo() {
    if (qntdLocacoes == 0) {
        printf("\nN�o h� loca��es cadastradas!\n");
        system("pause");
        return;
    }

    char dataInicioStr[15], dataFimStr[15];
    int d1, m1, a1, d2, m2, a2;

    // Solicitar datas do per�odo
    printf("\nInforme o per�odo para consulta:");
    
    printf("\nData inicial (dd/mm/aaaa): ");
    fgets(dataInicioStr, sizeof(dataInicioStr), stdin);
    dataInicioStr[strcspn(dataInicioStr, "\n")] = '\0';
    
    if (sscanf(dataInicioStr, "%d/%d/%d", &d1, &m1, &a1) != 3) {
        printf("Formato de data inv�lido!\n");
        system("pause");
        return;
    }

    printf("Data final (dd/mm/aaaa): ");
    fgets(dataFimStr, sizeof(dataFimStr), stdin);
    dataFimStr[strcspn(dataFimStr, "\n")] = '\0';
    
    if (sscanf(dataFimStr, "%d/%d/%d", &d2, &m2, &a2) != 3) {
        printf("Formato de data inv�lido!\n");
        system("pause");
        return;
    }
    system("cls");

    // Converter para time_t para compara��o
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
        printf("Erro ao converter datas!\n");
        system("pause");
        return;
    }

    if (difftime(fim, inicio) < 0) {
        printf("Data final deve ser ap�s data inicial!\n");
        system("pause");
        return;
    }

    // Listar loca��es no per�odo e calcular faturamento
    printf("\n==== Loca��es no per�odo %s a %s ====\n", dataInicioStr, dataFimStr);
    
    float faturamentoTotal = 0;
    int locacoesEncontradas = 0;

    for (int i = 0; i < qntdLocacoes; i++) {
        // Converter data da loca��o para time_t
        int dl, ml, al;
        if (sscanf(locacoes[i].dataInicio, "%d/%d/%d", &dl, &ml, &al) != 3) {
            continue; // Se data inv�lida, pula
        }

        struct tm tm_loc = {0};
        tm_loc.tm_mday = dl;
        tm_loc.tm_mon = ml - 1;
        tm_loc.tm_year = al - 1900;
        time_t dataLoc = mktime(&tm_loc);

        // Verificar se est� no per�odo
        if (dataLoc >= inicio && dataLoc <= fim) {
            // Encontrar cliente e ve�culo
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

            // Exibir informa��es
            printf("\nLoca��o %d", locacoes[i].codigoloc);
            printf("\n\nCliente: %s", (clienteIdx != -1) ? clientes[clienteIdx].nome : "N/A");
            printf("\nVe�culo: %s", (veiculoIdx != -1) ? veiculos[veiculoIdx].modelo : "N/A");
            printf("\nPer�odo: %s a %s", locacoes[i].dataInicio, locacoes[i].dataFim);
            printf("\nValor: R$ %.2f", locacoes[i].valorTotal);
            printf("\n----------------------------------\n");

            faturamentoTotal += locacoes[i].valorTotal;
            locacoesEncontradas++;
        }
    }

    if (locacoesEncontradas == 0) {
        printf("\nNenhuma loca��o encontrada neste per�odo.\n");
    } else {
        printf("\nFaturamento total no per�odo: R$ %.2f\n\n", faturamentoTotal);
    }

    system("pause");
}

void encerrar(){
    printf("\nSaindo do Sistema");
    for (int i = 0; i < 3; i++) {
        printf(".");
        sleep(1);
   }
   printf("\n\nAgradecemos Por Utilizar nosso Sistema!");
}

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
    printf("Bem-vindo ao sistema de aluguel de ve�culos!\n");
    sleep(1);

    while (1) {
        limparBuffer();
        printf("\\\\----------------------------------------//\n");
        printf("\nMenu:\n");

        printf("\n 1 - Nova loca��o");                       
        printf("\n 2 - Cadastrar ve�culos");
        printf("\n 3 - Remover ve�culos");
        printf("\n 4 - Listar ve�culos dispon�veis");
        printf("\n 5 - Cadastrar cliente");
        printf("\n 6 - Listar clientes");
        printf("\n 7 - Simular uma loca��o");
        printf("\n 8 - Encerrar loca��es");
        printf("\n 9 - Listar todas as loca��es ativas");
        printf("\n10 - Buscar loca��es ativas por cliente");
        printf("\n11 - Buscar loca��es ativas por ve�culo");
        printf("\n12 - Listar loca��es e faturamento por per�odo");
        printf("\n13 - Limpar Dados");
        printf("\n14 - Encerrar\n\n");
        printf("\\\\----------------------------------------//\n");

        printf("\nOp��o: ");
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
