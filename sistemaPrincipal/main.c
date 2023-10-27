#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

#define INTEIRA 25
#define MEIA 12.5
#define MEIA_ESTUDANTE 10
#define ISENCAO 0

int ingressos_vendidos = 0;
int total_respostas_pesquisa = 0;

typedef struct Venda {
    int dia;
    int mes;
    int ano;
    int quantidade_ingressos;
    float valor_entrada;
    int tipo_ingresso;
    char* exposicao;
};

void pausar() {
    if (PAUSE == 1) {
        system("pause");
    } else {
        system("read -p \"\n\tPressione qualquer tecla para continuar\" continuando");
    }
}

void imprime(char* mensagem) {
    printf("\t%s\n", mensagem);
}

void imprimeMensagemBoasVindas() {
    imprime("\n");
    imprime("***********************************************");
    imprime("* Bem vindo ao sistema do Museu James Gosling *");
    imprime("***********************************************");
    imprime("\n");
}

void mostraOpcoes() {
    imprime("- Escolha uma das seguintes opções -");
    imprime("Digite 1 para cadastrar uma venda de ingresso(s)");
    imprime("Digite 2 para consultar os preços");
    imprime("Digite 3 para buscar ingresso pelo ID");
    imprime("Digite 4 para listar as vendas de um dia");
    imprime("Digite 5 para gerar um relatório de vendas de um mês");
    imprime("Digite 6 para responder a pesquisa de satisfação");
    imprime("Digite 7 para sair");
}

void abrirOuCriarArquivosCSV() {
    FILE *fcsv = fopen("vendas.csv", "r");
    FILE *pesquisaDeSatisfacao = fopen("pesquisaDeSatisfacao.csv", "r");
    
    if (fcsv == NULL) {
        fcsv = fopen("vendas.csv", "w");
        fprintf(fcsv, "ID,DIA,MES,ANO,VALOR,TIPO_INGRESSO,EXPOSICAO\n");
    }

    if (pesquisaDeSatisfacao == NULL) {
        pesquisaDeSatisfacao = fopen("pesquisaDeSatisfacao.csv", "w");
        fprintf(pesquisaDeSatisfacao, "ID,DIA,MES,ANO,ATENDIMENTO,EXPOSICAO,VALOR,SISTEMA\n");
    }

    fclose(pesquisaDeSatisfacao);
    fclose(fcsv);
}

void contaIngressosVendidos() {
    FILE* fcsv = fopen("vendas.csv", "r");
    if (fcsv == NULL) return;

    for (char c = fgetc(fcsv); c != EOF; c = fgetc(fcsv))
        if (c == '\n')
            ingressos_vendidos ++;

    // Uma linha é o cabecalho
    ingressos_vendidos--;
    fclose(fcsv);
}

void contaPesquisasRespondidas() {
    FILE* pesquisa = fopen("pesquisaDeSatisfacao.csv", "r");
    if (pesquisa == NULL) return;
    for (char c = fgetc(pesquisa); c != EOF; c = fgetc(pesquisa))
        if (c == '\n')
            total_respostas_pesquisa++;
    
    // Linha de cabecalhos
    total_respostas_pesquisa--;
    fclose(pesquisa);
}

void vendaDeIngresso(int dia, int mes, int ano) {
    int tipo_ingresso;
    struct Venda venda;
    venda.dia = dia; venda.mes = mes; venda.ano = ano;

    imprime("Venda de ingresso: ");
    imprime("Digite o tipo de ingresso: ");
    imprime("0 para ISENÇÃO, 1 para MEIA ESTUDANTE, 2 para MEIA e 3 para INTEIRA");
    printf("\t"); scanf("%d", &tipo_ingresso);

    venda.tipo_ingresso = tipo_ingresso;
    if (tipo_ingresso == 0) venda.valor_entrada = ISENCAO;
    else if (tipo_ingresso == 1) venda.valor_entrada = MEIA_ESTUDANTE;
    else if (tipo_ingresso == 2) venda.valor_entrada = MEIA;
    else venda.valor_entrada = INTEIRA;

    imprime("Digite a quantidade de ingressos (do mesmo tipo) a serem vendidos: ");
    printf("\t"); scanf("%d", &venda.quantidade_ingressos);

    char exposicao[36];
    gets(exposicao);
    imprime("Digite a exposição referente ao ingresso (no máximo 36 caracteres): ");
    printf("\t"); gets(exposicao);
    venda.exposicao = exposicao;

    FILE* fcsv = fopen("vendas.csv", "a");

    imprime("ID dos ingressos gerados: ");
    printf("\t");
    for (int i = ingressos_vendidos; i < ingressos_vendidos + venda.quantidade_ingressos; i++) {
        fprintf(
            fcsv, "%d,%d,%d,%d,%.2f,%d,%s\n", 
            i, venda.dia, venda.mes, venda.ano, venda.valor_entrada, venda.tipo_ingresso, venda.exposicao
        );
        printf("%d ", i);
    }

    ingressos_vendidos += venda.quantidade_ingressos;

    fclose(fcsv);
    imprime("\n");
    imprime("Venda cadastrada com sucesso!");
    imprime("O valor total fica em: ");
    printf("\tR$%.2f", venda.quantidade_ingressos * venda.valor_entrada);
    imprime("");
}

void mostraOsPrecos() {
    imprime("Os valores das entradas são: ");
    printf("\tIsenção: R$%.2f\n", (float) ISENCAO);
    printf("\tMeia estudante: R$%.2f\n", (float) MEIA_ESTUDANTE);
    printf("\tMeia: R$%.2f\n", (float) MEIA);
    printf("\tInteira: R$%.2f\n", (float) INTEIRA);
}

void buscaIngressoPorId() {
    int idBusca = -1;
    int encontrado = 0;

    imprime("Digite o id do ingresso: ");
    printf("\t"); scanf("%d", &idBusca);

    FILE* vendas = fopen("vendas.csv", "r");
    if (vendas == NULL) {
        imprime("Não foi possível abrir o arquivo!");
        fclose(vendas);
        return;
    }

    // Pula primeira linha contendo os cabecalhos
    for (char c = getc(vendas); c != EOF; c = getc(vendas))
        if (c == '\n') break;

    int id = -1; int dia, mes, ano; float valor; int tipoIngresso; char exposicao[36];
    int lastId = -2;
    do {
        fscanf(vendas, "%d,%d,%d,%d,%f,%d,%[^\n]s\n", &id, &dia, &mes, &ano, &valor, &tipoIngresso, &exposicao);
        if (lastId == id) break;
        
        if (id == idBusca) {
            imprime("Ingresso encontrado: ");
            printf(
                "\tID: %d, Data: %d/%d/%d, Valor: %.2f, Tipo de Ingresso: %d, Exposição: %s\n", 
                id, dia, mes, ano, valor, tipoIngresso, exposicao
            );
            encontrado = 1;
            break;
        }
        lastId = id;
    } while(1);
    fclose(vendas);
    if (!encontrado) {
        imprime("Não existe ingresso com este id");
    }
}

void listarVendasDoDia() {
    int diaBusca, mesBusca, anoBusca;

    imprime("Digite a data para listar as vendas, no formato dd/MM/YYYY (20/11/2023 por exemplo): ");
    printf("\t"); scanf("%d/%d/%d", &diaBusca, &mesBusca, &anoBusca);

    FILE* vendas = fopen("vendas.csv", "r");
    if (vendas == NULL) {
        imprime("Não foi possível abrir o arquivo!");
        fclose(vendas);
        return;
    }

    // Pula primeira linha
    for (char c = getc(vendas); c != EOF; c = getc(vendas))
        if (c == '\n') break;

    imprime("Vendas: ");

    int id = -1; int dia, mes, ano; float valor; int tipoIngresso; char exposicao[36];
    int lastId = -2;
    do {

        fscanf(vendas, "%d,%d,%d,%d,%f,%d,%[^\n]s\n", &id, &dia, &mes, &ano, &valor, &tipoIngresso, &exposicao);
        if (lastId == id) break;
        
        if (dia == diaBusca && mes == mesBusca && ano == anoBusca) {
            char* tipoIngressoLabel;
            if (tipoIngresso == 0) tipoIngressoLabel = "Isenta";
            if (tipoIngresso == 1) tipoIngressoLabel = "Meia de Estudante";
            if (tipoIngresso == 2) tipoIngressoLabel = "Meia";
            if (tipoIngresso == 3) tipoIngressoLabel = "Inteira";
            printf(
                "\tID: %d, Data: %d/%d/%d, Valor: R$%.2f, Tipo de Entrada: %s, Exposição: %s\n",
                id, dia, mes, ano, valor, tipoIngressoLabel, exposicao
            );
        }
        lastId = id;
    } while(1);
    fclose(vendas);
    printf("\n\tVendas do dia %d/%d/%d foram listadas!\n", diaBusca, mesBusca, anoBusca);
}

void relatorioVendasDoMes() {
    int mesBusca, anoBusca;

    imprime("Digite a data para listar as vendas no formato MM/YYYY (11/2023 para novembro de 2023, por exemplo): ");
    printf("\t"); scanf("%d/%d", &mesBusca, &anoBusca);
    
    char formatoNomeArquivo[] = "RelatorioVendas-%d_%d.md";
    char nomeArquivo[32];
    sprintf(nomeArquivo, formatoNomeArquivo, mesBusca, anoBusca);

    int totalIngressos = 0, inteiras = 0, meias = 0, isencoes = 0, meiasDeEstudante = 0; 
    float lucroTotal = 0, lucroComInteiras = 0, lucroComMeias = 0, lucroComMeiasDeEstudante = 0;

    FILE* vendas = fopen("vendas.csv", "r");
    if (vendas == NULL) {
        imprime("Não foi possível abrir o arquivo!");
        fclose(vendas);
        return;
    }

    // Pula primeira linha
    for (char c = getc(vendas); c != EOF; c = getc(vendas))
        if (c == '\n') break;

    int id = -1; int dia, mes, ano; float valor; int tipoIngresso; char exposicao[36];
    int lastId = -2;
    do {
        fscanf(vendas, "%d,%d,%d,%d,%f,%d,%[^\n]s\n", &id, &dia, &mes, &ano, &valor, &tipoIngresso, &exposicao);
        if (lastId == id) break;
        
        if (mes == mesBusca && ano == anoBusca) {
            if (tipoIngresso == 0) isencoes++;
            else if (tipoIngresso == 1) meiasDeEstudante ++;
            else if (tipoIngresso == 2) meias++;
            else if (tipoIngresso == 3) inteiras++;
            totalIngressos++;
            lucroTotal += valor;
        }
        lastId = id;
    } while(1);
    fclose(vendas);

    lucroComInteiras = INTEIRA * inteiras;
    lucroComMeias = MEIA * meias;
    lucroComMeiasDeEstudante = MEIA_ESTUDANTE * meiasDeEstudante;

    FILE* relatorio = fopen(nomeArquivo, "w");
    if (relatorio == NULL) {
        printf("%s\n", nomeArquivo);
        imprime("Erro ao criar relatório");
        return;
    }

    fprintf(relatorio, "# Relatório do mês %d/%d\n\n", mesBusca, anoBusca);
    fprintf(relatorio, "> Sobre a quantidade de ingressos:\n");
    fprintf(relatorio, "\n## Total de ingressos vendidos: %d\n", totalIngressos);
    if (totalIngressos > 0) {
        fprintf(relatorio, "\n- Total de isenções: %d, %.2f%% do total\n", 
            isencoes, ((float) isencoes * 100) / totalIngressos);
        fprintf(relatorio, "- Total de meias de estudante: %d, %.2f%% do total\n", 
            meiasDeEstudante, ((float) meiasDeEstudante * 100) / totalIngressos);
        fprintf(relatorio, "- Total de meias: %d, %.2f%% do total\n", 
            meias, ((float) meias * 100) / totalIngressos);
        fprintf(relatorio, "- Total de inteiras: %d, %.2f%% do total\n", 
            inteiras, ((float) inteiras * 100) / totalIngressos);
    }

    fprintf(relatorio, "\n> Sobre o lucro obtido:\n");
    fprintf(relatorio, "\n## Lucro bruto total: R$%.2f\n", lucroTotal);
    if (lucroTotal > 0) {
        fprintf(relatorio, "\n- Lucro bruto com meias de estudante: R$%.2f, %.2f%% do total\n", 
            lucroComMeiasDeEstudante, (lucroComMeiasDeEstudante * 100) / lucroTotal);
        fprintf(relatorio, "- Lucro bruto com meias: R$%.2f, %.2f%% do total\n", 
            lucroComMeias, (lucroComMeias * 100) / lucroTotal);
        fprintf(relatorio, "- Lucro bruto com inteiras: R$%.2f, %.2f%% do total\n",
            lucroComInteiras, (lucroComInteiras * 100) / lucroTotal);
    }

    fprintf(relatorio, "\n> Sobre a pesquisa de satisfação:\n");

    // Pesquisa de satisfacao
    FILE* pesquisa = fopen("pesquisaDeSatisfacao.csv", "r");
    
    // Pula primeira linha
    for (char c = getc(pesquisa); c != EOF; c = getc(pesquisa))
        if (c == '\n') break;
    
    float somaAtendimento = 0, somaExposicao = 0, somaValor = 0, somaSistema = 0; int totalRespostas = 0;
    float atendimento, pesquisaExposicao, pesquisaValor, sistema;
    int pesquisaId = 0, lastPesquisaId = -1;
    do {
        fscanf(pesquisa, "%d,%d,%d,%d,%f,%f,%f,%f\n", 
            &pesquisaId, &dia, &mes, &ano, &atendimento, &pesquisaExposicao, &pesquisaValor, &sistema);

        if (lastPesquisaId == pesquisaId) break;

        if (mes == mesBusca && ano == anoBusca) {
            somaAtendimento += atendimento;
            somaExposicao += pesquisaExposicao;
            somaValor += pesquisaValor;
            somaSistema += sistema;
            totalRespostas++;
        }
        lastPesquisaId = pesquisaId;
    } while(1);

    fclose(pesquisa);
    fprintf(relatorio, "\n## Total de %d respostas no mês\n\n", totalRespostas);
    if (totalRespostas > 0) {
        fprintf(relatorio, "- Avaliação média do Atendimento: %.2f/5\n", somaAtendimento / totalRespostas);
        fprintf(relatorio, "- Avaliação média da Exposição: %.2f/5\n", somaExposicao / totalRespostas);
        fprintf(relatorio, "- Avaliação média do Valor cobrado: %.2f/5\n", somaValor / totalRespostas);
        fprintf(relatorio, "- Avaliação média do Sistema: %.2f/5\n", somaSistema / totalRespostas);
    }

    fclose(relatorio);
    printf("\n\tRelatório de vendas gerado com sucesso no arquivo %s\n", nomeArquivo);
}

float pegaNumeroReal(char* mensagem, int minimo, int maximo) {
    float num = minimo - 1;
    do {
        imprime(mensagem);
        printf("\t"); scanf("%f", &num);
        if (num < minimo || num > maximo) imprime("Digite um número válido!");
    } while(num < minimo || num > maximo);
    return num;
}

void pesquisaDeSatisfacao(int dia, int mes, int ano) {
    imprime("Iniciando a pesquisa de satisfação do museu James Gosling: ");

    FILE* pesquisa = fopen("pesquisaDeSatisfacao.csv", "a");
    float atendimento, exposicao, valor, sistema;
    atendimento = pegaNumeroReal("De 0 a 5, o quão satisfatório foi o atendimento? ", 0, 5);
    exposicao = pegaNumeroReal("De 0 a 5, o quão interessante foi a exposição e o material preparado? ", 0, 5);
    valor = pegaNumeroReal("De 0 a 5, o quão justo foi o valor cobrado? ", 0, 5);
    sistema = pegaNumeroReal("De 0 a 5, o quão bom foi o sistema (cadastro, venda de ingresso, terminais)? ", 0, 5);

    fprintf(pesquisa, "%d,%d,%d,%d,%.2f,%.2f,%.2f,%.2f\n", 
        total_respostas_pesquisa++, dia, mes, ano, atendimento, exposicao, valor, sistema);
        
    imprime("Obrigado por responder a pesquisa de satisfação!");
    fclose(pesquisa);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int dia = tm.tm_mday;
    int mes = tm.tm_mon + 1;
    int ano = tm.tm_year + 1900;

    abrirOuCriarArquivosCSV();
    contaIngressosVendidos();
    contaPesquisasRespondidas();

    imprimeMensagemBoasVindas();

    while (1) {
        mostraOpcoes();
        imprime("\n\tQual ação deseja fazer? ");
        printf("\t"); scanf("%d", &opcao);

        imprime("\n");
        if (opcao == 1) {
            vendaDeIngresso(dia, mes, ano);
        } else if (opcao == 2) {
            mostraOsPrecos();
        } else if (opcao == 3) {
            buscaIngressoPorId();
        } else if (opcao == 4) {
            listarVendasDoDia();
        } else if (opcao == 5) {
            relatorioVendasDoMes();
        } else if (opcao == 6) {
            pesquisaDeSatisfacao(dia, mes, ano);
        } else if (opcao == 7) {
            imprime("Desligando o sistema!");
            break;
        } else {
            imprime("Escolha uma opção válida!");
        }
        pausar();
    }

    imprime("\n - Fim - \n");
}
