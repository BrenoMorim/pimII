#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

void pausar() {
	if (PAUSE == 1) {
			system("pause");
	} else {
			system("read -p \"\n\tPressione qualquer tecla para continuar\" continuando");
	}
}

int getLinhas(char* nomeArquivo) {
	FILE* arq = fopen(nomeArquivo, "r");
	int linhas = 0;

	for (char c = getc(arq); c != EOF; c = getc(arq))
		if (c == '\n')
				linhas ++;

	fclose(arq);
	return linhas;
}

void insereLinhaCSV(char numeroQuestao, char respostaUsuario, int acertou) {
	FILE* respostas = fopen("respostas.csv", "r");
	if (respostas == NULL) {
		respostas = fopen("respostas.csv", "w");
		fprintf(respostas, "QUESTAO,RESPOSTA,ACERTOU\n");
		fclose(respostas);
	}
	respostas = fopen("respostas.csv", "a");
	fprintf(respostas, "%c,%c,%d\n", numeroQuestao, respostaUsuario, acertou);
	fclose(respostas);
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	int numeroLinhas = getLinhas("questionario.txt");
	int acertos = 0;
	FILE* questoes = fopen("questionario.txt", "r");

	if (questoes == NULL) {
		printf("\n\tArquivo \"questionario.txt\" com as questões não foi encontrado!\n\n");
		exit(1);
	}
	
	char titulo[100];
	fgets(titulo, 100, questoes);

	printf("\n\t"); 
	for(int i = 0; i < strlen(titulo) - 2; i++) printf("-"); 
	printf("\n\t%s", titulo);
	printf("\t"); 
	for(int i = 0; i < strlen(titulo) - 2; i++) printf("-"); 
	printf("\n");

	char numeroQuestao;
	for (int i = 1; i < numeroLinhas / 4; i++) {
		char pergunta[200];
		fgets(pergunta, 200, questoes);
		printf("\n\t%s", pergunta);
		numeroQuestao = pergunta[0];

		char respostaUsuario[1];
		int usuarioAcertou = 0;
		char alternativaCorreta;

		for (int j = 0; j < 3; j++) {
			char alternativa[100];
			fgets(alternativa, 100, questoes);
			int inicio = 0;
			if (alternativa[0] == '*') {
				alternativaCorreta = alternativa[1];
				inicio = 1;
			}
			printf("\n\t");
			for (int c = inicio; c < strlen(alternativa); c++) printf("%c", alternativa[c]);
		}
		printf("\n\tDigite sua resposta (em letras minúsculas): ");
		gets(respostaUsuario);

		int acertou = 0;
		if (respostaUsuario[0] == alternativaCorreta) {
			printf("\n\tVocê acertou =)\n");	
			acertou = 1;
			acertos++;
		} else {
			printf("\n\tVocê errou =(\n");
		}
		insereLinhaCSV(numeroQuestao, respostaUsuario[0], acertou);
		pausar();
	}
	printf("\n\tQuestionário respondido com sucesso!");
	printf("\n\tTotal de acertos: %d\n", acertos);
	
	fclose(questoes);
	pausar();
	return 0;
}