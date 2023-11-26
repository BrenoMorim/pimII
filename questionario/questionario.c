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

void insereLinhaCSV(char numeroQuestao, char respostaUsuario, int acertou, char questionarioEscolhido) {
	FILE* respostas = fopen("respostas.csv", "r");
	if (respostas == NULL) {
		respostas = fopen("respostas.csv", "w");
		fprintf(respostas, "QUESTAO,RESPOSTA,ACERTOU,QUESTIONARIO\n");
		fclose(respostas);
	}
	respostas = fopen("respostas.csv", "a");
	fprintf(respostas, "%c,%c,%d,%c\n", numeroQuestao, respostaUsuario, acertou, questionarioEscolhido);
	fclose(respostas);
}

int validaQuestionarioEscolhido(char questionario) {
	char validos[] = "AaOoJjSsXx";
	for (int i = 0; i < strlen(validos); i++) {
		if (validos[i] == questionario) return 1;
	}
	return 0;
}

int validaRespostaUsuario(char resposta) {
	if (resposta == 'A' || resposta == 'a') return 'a';
	if (resposta == 'B' || resposta == 'b') return 'b';
	if (resposta == 'C' || resposta == 'c') return 'c';

	return 'x';
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	while (1) {
		int acertos = 0;
		char questionarioEscolhido = '0';
		int valido = 0;
		do {
			printf("\n\tQual questionário você deseja responder?\n");
			printf("\n\tDigite S para Santos Dumont, O para Olimpíadas, A para Semana de Arte Moderna, J para Java ou X para sair\n\t");
			questionarioEscolhido = getchar();
			valido = validaQuestionarioEscolhido(questionarioEscolhido);
			if (valido == 0) {
				printf("\n\tDigite uma opção válida!\n");
				getchar();
			}
		} while (valido == 0);

		char* nomeArquivo;

		if (questionarioEscolhido == 'a' || questionarioEscolhido == 'A') {
			nomeArquivo = "questionarioSemana.txt";
		} else if (questionarioEscolhido == 'j' || questionarioEscolhido == 'J') {
			nomeArquivo = "questionarioJava.txt";
		} else if (questionarioEscolhido == 'O' || questionarioEscolhido == 'o') {
			nomeArquivo = "questionarioOlimpiadas.txt";
		} else if (questionarioEscolhido == 's' || questionarioEscolhido == 'S') {
			nomeArquivo = "questionarioSantosDumont.txt";
		} else if (questionarioEscolhido == 'x' || questionarioEscolhido == 'X') {
			break;
		}

		FILE* questoes = fopen(nomeArquivo, "r");

		int numeroLinhas = getLinhas(nomeArquivo);
		if (questoes == NULL) {
			printf("\n\tArquivo \"%s\" com as questões não foi encontrado!\n\n", nomeArquivo);
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

			char respostaUsuario = '0';
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
			getchar();
			do {
				printf("\n\tDigite sua resposta (a, b ou c): ");
				respostaUsuario = validaRespostaUsuario(getchar());

				if (respostaUsuario == 'x') {
					printf("\n\tDigite uma opção válida (a, b ou c)\n");
					pausar();
					getchar();
				}
			} while(respostaUsuario == 'x');

			int acertou = 0;
			if (respostaUsuario == alternativaCorreta) {
				printf("\n\tVocê acertou =)\n");	
				acertou = 1;
				acertos++;
			} else {
				printf("\n\tVocê errou =(\n");
			}
			insereLinhaCSV(numeroQuestao, respostaUsuario, acertou, questionarioEscolhido);
			pausar();
		}
		printf("\n\tQuestionário respondido com sucesso!");
		printf("\n\tTotal de acertos: %d\n", acertos);
		
		fclose(questoes);
		pausar();
		getchar();
	}
	printf("\n\n\tDesligando, obrigado por jogar!\n\n");
	return 0;
}