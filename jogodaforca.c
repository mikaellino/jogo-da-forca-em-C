// Mikael Henrique Lino Rodrigues
// Victor Benatti Alves dos Santos


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
 
#define MAX_TENTATIVAS 6
#define MAX_PALAVRA 20
 
const char *animais[] = {
    "GATO",
    "CACHORRO",
    "PREGUI�A",
    "ELEFANTE",
    "GIRAFA",
    "LE�O"
};
 
const char *objetos[] = {
    "CADEIRA",
    "MESA",
    "CANETA",
    "COMPUTADOR",
    "TELEFONE",
    "LIVRO",
    "OCULOS",
    "CARRO"
};
 
const char *frutas[] = {
    "MA�A",
    "BANANA",
    "UVA",
    "ABACAXI",
    "MORANGO",
    "LARANJA",
    "PERA",
    "MELANCIA",
    "MANGA",
    "KIWI"
};
 
const char *cores[] = {
    "VERMELHO",
    "AZUL",
    "VERDE",
    "AMARELO",
    "ROSA",
    "LARANJA",
    "ROXO"
};
 
int num_animais = sizeof(animais) / sizeof(animais[0]);
int num_objetos = sizeof(objetos) / sizeof(objetos[0]);
int num_frutas = sizeof(frutas) / sizeof(frutas[0]);
int num_cores = sizeof(cores) / sizeof(cores[0]);
 
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
void mostrarForca(int erros) {
    printf("  ____\n");
    printf(" |    |\n");
    printf(" |    %c\n", (erros >= 1) ? 'O' : ' ');
    printf(" |   %c%c%c\n", (erros >= 3) ? '/' : ' ', (erros >= 2) ? '|' : ' ', (erros >= 4) ? '\\' : ' ');
    printf(" |   %c %c\n", (erros >= 5) ? '/' : ' ', (erros >= 6) ? '\\' : ' ');
    printf("_|_\n\n");
}
 
void mostrarPalavraEscondida(const char *palavra, char *letras_descobertas) {
    int i;
    for (i = 0; i < strlen(palavra); i++) {
        if (letras_descobertas[i] == 1) {
            printf("%c ", palavra[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n\n");
}
 
const char* escolherPalavra(const char **palavras, int num_palavras) {
    srand(time(NULL));
    return palavras[rand() % num_palavras];
}
 
int main() {
    setlocale(LC_ALL, "Portuguese");
    const char *tema;
    const char **palavras;
    int num_palavras;
 
    printf("Bem-vindo ao Jogo da Forca!\n");
    printf("Escolha o tema:\n");
    printf("1. Animais\n");
    printf("2. Objetos\n");
    printf("3. Frutas\n");
    printf("4. Cores\n");
 
    int opcao;
    printf("Escolha uma op��o: ");
    scanf("%d", &opcao);
    limparBuffer();
 
    if (opcao == 1) {
        tema = "Animais";
        palavras = animais;
        num_palavras = num_animais;
    } else if (opcao == 2) {
        tema = "Objetos";
        palavras = objetos;
        num_palavras = num_objetos;
    } else if (opcao == 3) {
        tema = "Frutas";
        palavras = frutas;
        num_palavras = num_frutas;
    } else if (opcao == 4) {
        tema = "Cores";
        palavras = cores;
        num_palavras = num_cores;
    } else {
        printf("Op��o inv�lida. Encerrando o programa.\n");
        return 1;
    }
 
    char palavra[MAX_PALAVRA];
    char letras_descobertas[MAX_PALAVRA];
    char letras_erradas[MAX_TENTATIVAS];
    char letra;
    char tentativa[MAX_PALAVRA];
    int i, erros = 0, acertos = 0;
 
    strcpy(palavra, escolherPalavra(palavras, num_palavras));
    memset(letras_descobertas, 0, sizeof(letras_descobertas));
    memset(letras_erradas, 0, sizeof(letras_erradas));
 
    printf("Adivinhe a palavra secreta relacionada a %s.\n", tema);
    mostrarPalavraEscondida(palavra, letras_descobertas);
 
    while (erros < MAX_TENTATIVAS && acertos < strlen(palavra)) {
        printf("Digite uma letra ou tente adivinhar a palavra inteira: ");
        fgets(tentativa, sizeof(tentativa), stdin);
        tentativa[strcspn(tentativa, "\n")] = '\0';
 
        if (strlen(tentativa) == 1) {
            letra = toupper(tentativa[0]);
 
            if (strchr(palavra, letra) != NULL) {
                for (i = 0; i < strlen(palavra); i++) {
                    if (palavra[i] == letra) {
                        letras_descobertas[i] = 1;
                        acertos++;
                    }
                }
            } else {
                letras_erradas[erros] = letra;
                erros++;
                printf("Letra incorreta! Tente novamente.\n");
                mostrarForca(erros);
            }
        } else {
            for (i = 0; tentativa[i] != '\0'; i++) {
                tentativa[i] = toupper(tentativa[i]);
            }
            if (strcmp(palavra, tentativa) == 0) {
                acertos = strlen(palavra);
            } else {
                erros++;
                printf("Palavra incorreta! Tente novamente.\n");
                mostrarForca(erros);
            }
        }
 
        printf("\nPalavra: ");
        mostrarPalavraEscondida(palavra, letras_descobertas);
        printf("Letras erradas:");
        for (i = 0; i < erros; i++) {
            printf(" %c", letras_erradas[i]);
        }
        printf("\n");
    }
 
    if (acertos == strlen(palavra)) {
        printf("Parab�ns! Voc� adivinhou a palavra \"%s\".\n", palavra);
    } else {
        printf("Voc� perdeu! O n�mero m�ximo de tentativas foi atingido.\n");
        printf("A palavra correta era \"%s\".\n", palavra);
        mostrarForca(MAX_TENTATIVAS);
    }
 
    printf("Esse trabalho foi desenvolvido por Mikael Lino e Victor Benatti do Segundo Semestre de ADS da Fatec Campinas.");
 
    return 0;
}