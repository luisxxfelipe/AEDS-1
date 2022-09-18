#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definindo as variaveis globais para facilitar

char **tabuleiro;
int jogador_atual;
int jogador_oposto;
int jogador_selecionado_preto;
int jogador_selecionado_branco;

// Prototipos das funcoes

void dados_jogadores_e_selecao_de_cores();
void criar_tabuleiro();
void imprimir_jogador_atual();
void jogada_valida_tab();
void limpar_jogadas();
void imprimir_tabuleiro();
void fazer_novo_movimento();
void prox_jogador();
void vencedor();
void capturar_pecas();

// Adicionando uma struct para organização de dados

typedef struct
{
    char nome[50];
    float idade;
    char sexo[50];
    int cor;
    int pontos;

} jogo;

int main()
{
    jogo dados_jogo[2];
    int fim_de_jogo = 0;

    // Funcionamento do tabuleiro com os prototipos de cada função

    dados_jogadores_e_selecao_de_cores();
    criar_tabuleiro();

    do
    {
        jogada_valida_tab();
        imprimir_tabuleiro();
        imprimir_jogador_atual();
        fazer_novo_movimento();
        limpar_jogadas();
        prox_jogador();

    } while (!fim_de_jogo);

    vencedor();

    return 0;
}

// Função para inicializar o jogo

void criar_tabuleiro(jogo *dados_jogo)
{
    // Alocando memoria;

    tabuleiro = malloc(8 * sizeof(char *));
    tabuleiro[0] = malloc(8 * 8 * sizeof(char));

    for (int i = 1; i < 8; i++)
    {
        tabuleiro[i] = tabuleiro[0] + i * 8;
    }

    // Prenchendo tabuleiro com marcador vazio;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tabuleiro[i][j] = ' ';
        }
    }

    // Colocando peças iniciais no meio do tabuleiro;

    tabuleiro[3][3] = 'P';
    tabuleiro[4][4] = 'P';
    tabuleiro[3][4] = 'B';
    tabuleiro[4][3] = 'B';
    jogador_atual = 'P';
    jogador_oposto = 'B';

    dados_jogo[jogador_selecionado_branco].pontos = 0;
    dados_jogo[jogador_selecionado_preto].pontos = 0;
}

// Função que representa a base do tabuleiro 8 x 8

void imprimir_tabuleiro(int i, int j)
{
    printf("   A B C D E F G H \n");
    for (i = 0; i < 8; i++)
    {
        printf("\n%d  ", i);
        for (j = 0; j < 8; j++)
        {
            printf("%c ", tabuleiro[i][j]);
        }
    }
    printf("\n");
}

// Função para representar o menu ao usuario com entrada de dados

void dados_jogadores_e_selecao_de_cores(jogo *dados_jogo)
{

    printf("Created by Luis Felipe.\n(C) Ano: 2021");
    printf("\n\n\n-------- |SEJA BEM VINDO AO JOGO OTHELLO| --------\n---------------- |DIVIRTA-SE| --------------------");
    int i;

    for (i = 0; i < 2; i++)
    {
        printf("\n\nDigite o seu nome: ");
        setbuf(stdin, NULL);
        scanf("%s", dados_jogo[i].nome);
        printf("Digite a sua idade: ");
        scanf("%f", &dados_jogo[i].idade);
        printf("Digite o seu sexo: ");
        setbuf(stdin, NULL);
        scanf("%s", dados_jogo[i].sexo);
    }

    // Comando de repetição responsavel para escolher que cor sera cada jogador

    srand(time(NULL)); // Setar random

    int jogador_selecionado;

    jogador_selecionado = rand() % 2 + 1;
    if (jogador_selecionado == 1)
    {
        dados_jogo[0].cor = 'B';
        dados_jogo[1].cor = 'P';
        jogador_selecionado_preto = 1;
        jogador_selecionado_branco = 0;

        printf("\n\nO jogador 1 sera da cor branca.");
        printf("\nO jogador 2 sera da cor preta.");
    }

    else if (jogador_selecionado == 2)
    {

        dados_jogo[0].cor = 'B';
        dados_jogo[1].cor = 'P';
        jogador_selecionado_preto = 0;
        jogador_selecionado_branco = 1;

        printf("\n\nO jogador 1 sera da cor preta.");
        printf("\nO jogador 2 sera da cor branca.");
    }

    printf("\n\n");
}

// Função para retornar qual jogador fará a proxima jogada

void imprimir_jogador_atual()
{
    printf("\n\nFaca uma nova jogada jogador: ");
    if (jogador_atual == 'P')
    {
        printf("PRETO");
    }
    else
    {
        printf("BRANCO");
    }
    printf("\n");
}

// Função para representar, atraves do marcador, quais serao as posicoes validas para a realização da jogada

void jogada_valida_tab(int i, int j)
{
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {

            // Condiçao para verificar a linha pela direita

            if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i][j + 1] == jogador_oposto))
            {

                for (int k = j; k < 8; k++)
                {
                    if (tabuleiro[i][k] == ' ')
                    {
                        tabuleiro[i][k] = '.';
                        k = 8;
                    }
                }
            }

            // Condição para verficar a linha pela esquerda

            else if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i][j - 1] == jogador_oposto))
            {
                for (int k = j; k > 0; k--)
                {
                    if (tabuleiro[i][k] == ' ')
                    {
                        tabuleiro[i][k] = '.';
                        k = 0;
                    }
                }
            }

            // Condição para verificar a coluna para baixo

            if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i + 1][j] == jogador_oposto))
            {

                // verificador se existe mais peças pretas para a realização da jogada ate a ultima coluna

                for (int k = i; k < 8; k++)
                {
                    if (tabuleiro[k][j] == ' ')
                    {
                        tabuleiro[k][j] = '.';
                        k = 8;
                    }
                }
            }

            // Condição para verificar a coluna para cima

            else if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i - 1][j] == jogador_oposto))
            {
                for (int k = i; k > 0; k--)
                {
                    if (tabuleiro[k][j] == ' ')
                    {
                        tabuleiro[k][j] = '.';
                        k = 0;
                    }
                }
            }

            // Movimento diagonal descendo

            if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i + 1][j + 1] == jogador_oposto))
            {
                tabuleiro[i + 2][j + 2] = '.';
            }

            // Movimento na diagonal subindo

            if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i - 1][j - 1] == jogador_oposto))
            {
                tabuleiro[i - 2][j - 2] = '.';
            }

            // Movimento para baixo e esquerda

            if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i + 1][j - 1] == jogador_oposto))
            {
                tabuleiro[i + 2][j - 2] = '.';
            }

            // Movimento subindo e para a direita

            if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i - 1][j + 1] == jogador_oposto))
            {
                tabuleiro[i - 2][j + 2] = '.';
            }
        }
    }
}

void capturar_pecas(int i, int j)
{
    int k, l;

    // Captura as peças no movimento para cima

    if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i - 1][j] == jogador_oposto))
    {
        k = i - 1, l = j;
        while (tabuleiro[k][l] == jogador_oposto)
        {
            tabuleiro[k][l] = jogador_atual;

            k -= 1;
        }
    }

    // Captura o movimento das peças para baixo

    if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i + 1][j] == jogador_oposto))
    {
        k = i + 1, l = j;
        while (tabuleiro[k][l] == jogador_oposto)
        {
            tabuleiro[k][l] = jogador_atual;

            k += 1;
        }
    }

    // Captura as peças pelo movimento da esquerda

    if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i][j - 1] == jogador_oposto))
    {
        k = i, l = j - 1;
        while (tabuleiro[k][l] == jogador_oposto)
        {
            tabuleiro[k][l] = jogador_atual;

            l -= 1;
        }
    }

    // Captura as peças pelo movimento da direita

    if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i][j + 1] == jogador_oposto))
    {
        k = i, l = j + 1;
        while (tabuleiro[k][l] == jogador_oposto)
        {
            tabuleiro[k][l] = jogador_atual;

            l += 1;
        }
    }

    // // Captura as peças pelo movimento diagonal descendo

    // if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i + 1][j + 1] == jogador_oposto))
    // {
    //     k = i + 1, l = j + 1;
    //     while (tabuleiro[k][l] == jogador_oposto)
    //     {
    //         tabuleiro[k][l] = jogador_atual;

    //         k += 1;
    //         l += 1;
    //     }
    // }

    // // Captura as peças pelo movimento na diagonal subindo

    // if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i - 1][j - 1] == jogador_oposto))
    // {
    //     k = i - 1, l = j - 1;
    //     while (tabuleiro[k][l] == jogador_oposto)
    //     {
    //         tabuleiro[k][l] = jogador_atual;

    //         k -= 1;
    //         l -= 1;
    //     }
    // }

    // // Captura as peças pelo movimento para baixo e esquerda

    // if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i + 1][j - 1] == jogador_oposto))
    // {
    //     k = i + 1, l = j - 1;
    //     while (tabuleiro[k][l] == jogador_oposto)
    //     {
    //         tabuleiro[k][l] = jogador_atual;

    //         k += 1;
    //         l -= 1;
    //     }
    // }

    // // Captura as peças pelo movimento subindo e para a direita

    // if ((tabuleiro[i][j] == jogador_atual) && (tabuleiro[i - 1][j + 1] == jogador_oposto))
    // {
    //     k = i - 1, l = j + 1;
    //     while (tabuleiro[k][l] == jogador_oposto)
    //     {
    //         tabuleiro[k][l] = jogador_atual;

    //         k -= 1;
    //         l += 1;
    //     }
    // }
}

// Funcao responsavel pelo novo movimento das peças

void fazer_novo_movimento()
{
    int p_linha, p_coluna;
    printf("\nEntre com uma linha e uma coluna de 0 a 7 seguida de espaco: ");
    scanf("%d %d", &p_linha, &p_coluna);

    if (p_linha >= 0 && p_linha <= 8 && p_coluna >= 0 && p_coluna <= 8)
    {
        if (tabuleiro[p_linha][p_coluna] == '.')
        {
            tabuleiro[p_linha][p_coluna] = jogador_atual;
        }

        capturar_pecas(p_linha, p_coluna);
    }

    else
    {
        printf("\nPosicao invalida, tente novamente!\n\n");
    }
}

// Funcao para trocar o jogador para a relizaçao da proxima jogada

void prox_jogador()
{

    int aux = jogador_atual;
    jogador_atual = jogador_oposto;
    jogador_oposto = aux;
}

// Função responsavel para limpar as jogadas para o proximo jogador fazer um novo movimento

void limpar_jogadas()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tabuleiro[i][j] == '.')
            {
                tabuleiro[i][j] = ' ';
            }
        }
    }
}

// Função que passara pelo vetor inteiro e calculara a pontuação de cada jogador

void vencedor(jogo *dados_jogo)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tabuleiro[i][j] == jogador_atual)
            {
                dados_jogo[jogador_selecionado_preto].pontos += 1;
            }
            if (tabuleiro[i][j] == jogador_oposto)
            {
                dados_jogo[jogador_selecionado_branco].pontos += 1;
            }
        }
    }

    // Final do codigo que ira imprimir todo o ranking de pontuação

    printf("\n------- |PONTUACAO FINAL DOS JOGADORES| --------\n");

    if (dados_jogo[jogador_selecionado_branco].pontos > dados_jogo[jogador_selecionado_preto].pontos)
    {
        printf("\nO Vencedor foi o jogador branco.\n");
        printf("Nome do jogador: %s\nIdade: %.0f anos\nSexo: %s\nPontuacao: %d pontos.", dados_jogo[jogador_selecionado_branco].nome, dados_jogo[jogador_selecionado_branco].idade, dados_jogo[jogador_selecionado_branco].sexo, dados_jogo[jogador_selecionado_branco].pontos);
        printf("\n\nO jogador perdedor foi o preto.\n");
        printf("Nome do jogador: %s\nIdade: %.0f anos\nSexo: %s\nPontuacao: %d pontos.", dados_jogo[jogador_selecionado_preto].nome, dados_jogo[jogador_selecionado_preto].idade, dados_jogo[jogador_selecionado_preto].sexo, dados_jogo[jogador_selecionado_preto].pontos);
        printf("\n\n---------- |PARABENS PELA VITORIA JOGADOR JOGADOR BRANCO| ----------\n");
    }

    else if (dados_jogo[jogador_selecionado_branco].pontos < dados_jogo[jogador_selecionado_preto].pontos)
    {
        printf("\nO Vencedor foi o jogador preto.\n");
        printf("Nome do jogador: %s\nIdade: %.0f anos\nSexo: %s\nPontuacao: %d pontos.", dados_jogo[jogador_selecionado_preto].nome, dados_jogo[jogador_selecionado_preto].idade, dados_jogo[jogador_selecionado_preto].sexo, dados_jogo[jogador_selecionado_preto].pontos);
        printf("\n\nO jogador perdedor foi o branco.\n");
        printf("Nome do jogador: %s\nIdade: %.0f anos\nSexo: %s\nPontuacao: %d pontos.", dados_jogo[jogador_selecionado_branco].nome, dados_jogo[jogador_selecionado_branco].idade, dados_jogo[jogador_selecionado_branco].sexo, dados_jogo[jogador_selecionado_branco].pontos);
        printf("\n\n---------- |PARABENS PELA VITORIA JOGADOR JOGADOR PRETO| ----------\n");
    }

    else if ((dados_jogo[jogador_selecionado_branco].pontos = dados_jogo[jogador_selecionado_preto].pontos))
    {
        printf("\nO jogo terminou com empate.\n");
        printf("Nome do jogador 1: %s\nIdade: %.0f anos\nSexo: %s\nPontuacao: %d pontos.", dados_jogo[jogador_selecionado_preto].nome, dados_jogo[jogador_selecionado_preto].idade, dados_jogo[jogador_selecionado_preto].sexo, dados_jogo[jogador_selecionado_preto].pontos);
        printf("Nome do jogador 2: %s\nIdade: %.0f anos\nSexo: %s\nPontuacao: %d pontos.", dados_jogo[jogador_selecionado_branco].nome, dados_jogo[jogador_selecionado_branco].idade, dados_jogo[jogador_selecionado_branco].sexo, dados_jogo[jogador_selecionado_branco].pontos);
        printf("\n\n---------- |JOGO EMPATADO| ----------\n");
    }

    printf("\nDigite enter para finalizar o jogo...\n\n");
}