#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Adicionando uma struct para organização de dados

typedef struct matricula
{
    char nome[50];
    int matricula1;
    float notas[3];
    float media;
} matricula;

float media(float n1, float n2, float n3);
int buscando_matricula(matricula *dados_alunos, int buscar);
void ordenar(matricula *dados_alunos);

int main()
{
    // incluindo as variaveis

    int i, j, opcao, buscar, opcao_alterar;
    int maior, menor, indice_maior, indice_menor;
    matricula dados_aluno[116];

    dados_aluno[0].matricula1 = 003;
    strcpy(dados_aluno[0].nome, "Spencer");
    dados_aluno[0].notas[0] = 10.0;
    dados_aluno[0].notas[1] = 9.9;
    dados_aluno[0].notas[2] = 10.0;

    dados_aluno[1].matricula1 = 402;
    strcpy(dados_aluno[1].nome, "Derek");
    dados_aluno[1].notas[0] = 5.5;
    dados_aluno[1].notas[1] = 9.1;
    dados_aluno[1].notas[2] = 6.2;

    dados_aluno[2].matricula1 = 801;
    strcpy(dados_aluno[2].nome, "Aaron");
    dados_aluno[2].notas[0] = 6.9;
    dados_aluno[2].notas[1] = 8.5;
    dados_aluno[2].notas[2] = 7.0;

    // Realização das medias dos alunos

    for (i = 0; i < 3; i++)
    {
        dados_aluno[i].media = media(dados_aluno[i].notas[0], dados_aluno[i].notas[1], dados_aluno[i].notas[2]);
    }

    // Aluno que obteve maior nota

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (dados_aluno[i].notas[j] > maior)
            {
                maior = dados_aluno[i].notas[j];
                indice_maior = i;
            }
        }
    }

    // Aluno que obteve menor nota

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (dados_aluno[i].notas[j] < menor)
            {
                menor = dados_aluno[i].notas[j];
                indice_menor = i;
            }
        }
    }

    // Entrando com o menu que sera apresentado ao usuário

    do
    {
        printf("[1]Imprimir todos os elementos do arranjo.\n[2]Imprimir apenas os nomes dos alunos.\n[3]Imprimir o nome dos alunos e sua respectiva nota final.\n[4]Buscar os dados de um aluno usando a busca sequencial.\n[5]Imprimir os alunos ordenados de acordo com sua matricula.\n[6]Editar as notas de um aluno, para isso e necessario que se busque os dados do aluno.\n[7]Imprimir a matricula, nome e nota final do aluno que obteve a maior nota de todas.\n[8]Imprimir a matricula, nome e nota final do aluno que obteve a menor nota de todas.\n[9]Imprimir quantos alunos foram aprovados e quantos alunos foram reprovados, imprima ainda a media geral.\n[0] Sair do programa.");
        printf("\n\nEscolha alguma opcao acima: ");
        scanf("%d", &opcao);

        //Imprimir todos os elementos do arranjo

        if (opcao == 1)
        {
            for (i = 0; i < 3; i++)
            {
                printf("\nMatricula: %03d\nNome: %s\nNota 1: %.2f\nNota 2: %.2f\nNota 3: %.2f\nNota final: %.2f\n", dados_aluno[i].matricula1, dados_aluno[i].nome, dados_aluno[i].notas[0], dados_aluno[i].notas[1], dados_aluno[i].notas[2], dados_aluno[i].media);
            }

            system("pause");
            system("cls");
        }

        //Imprimir apenas os nomes dos alunos

        if (opcao == 2)
        {
            for (i = 0; i < 3; i++)
            {
                printf("%s \n", dados_aluno[i].nome);
            }

            system("pause");
            system("cls");
        }

        // Imprimir o nome dos alunos e sua respectiva nota final

        if (opcao == 3)
        {
            for (i = 0; i < 3; i++)
            {
                printf("%s %.2f\n", dados_aluno[i].nome, dados_aluno[i].media);
            }

            system("pause");
            system("cls");
        }

        // Buscar os dados de um aluno usando a busca sequencial

        if (opcao == 4)
        {

            printf("Digite a matricula do aluno que deseja procurar: ");
            scanf("%d", &buscar);
            int indice_matricula = -1;

            indice_matricula = buscando_matricula(dados_aluno, buscar);

            if (indice_matricula == -1)
            {
                printf("\nAluno nao encontrado!!");

                printf("\n");
            }
            else
            {
                printf("\nMatricula: %03d\n", dados_aluno[indice_matricula].matricula1);
                printf("\nNome: %s", dados_aluno[indice_matricula].nome);
                printf("\nNota 1: %.2f\n", dados_aluno[indice_matricula].notas[0]);
                printf("Nota 2: %.2f\n", dados_aluno[indice_matricula].notas[1]);
                printf("Nota 3: %.2f\n", dados_aluno[indice_matricula].notas[2]);
                printf("Media: %.2f", dados_aluno[indice_matricula].media);
            }

            printf("\n");

            system("pause");
            system("cls");
        }

        // Imprimir os alunos ordenados de acordo com sua matricula

        if (opcao == 5)
        {
            printf("\n\nNumeros de matricula em ordem crescente:\n");

            ordenar(dados_aluno);

            for (i = 0; i < 3; i++)
            {
                printf("\n%03d %s %.2f %.2f %.2f", dados_aluno[i].matricula1, dados_aluno[i].nome, dados_aluno[i].notas[0], dados_aluno[i].notas[1], dados_aluno[i].notas[2]);
            }

            printf("\n");

            system("pause");
            system("cls");
        }

        // Editar as notas de um aluno, para isso e necessario que se busque os dados do aluno

        if (opcao == 6)
        {
            printf("Digite a matricula do aluno que deseja procurar: ");
            scanf("%d", &buscar);
            int indice_matricula = -1;

            indice_matricula = buscando_matricula(dados_aluno, buscar);

            if (indice_matricula == -1)
            {
                printf("Aluno nao encontrado!!");
            }
            else
            {
                printf("\n[1]Nota 1\n[2]Nota 2\n[3]Nota 3");
                printf("\n\nDigite o numero da opcao que representa a nota que deseja alterar: ");
                scanf("%d", &opcao_alterar);

                printf("\nDigite a nova nota: ");
                scanf("%f", &dados_aluno[indice_matricula].notas[opcao_alterar - 1]);

                dados_aluno[indice_matricula].media = media(dados_aluno[indice_matricula].notas[0], dados_aluno[indice_matricula].notas[1], dados_aluno[indice_matricula].notas[2]);

                printf("\nAtualizacao das notas: \n");
                printf("\nMatricula: %03d\nNome: %s\nNota 1: %.2f\nNota 2: %.2f\nNota 3: %.2f\nMedia: %.2f", dados_aluno[indice_matricula].matricula1, dados_aluno[indice_matricula].nome, dados_aluno[indice_matricula].notas[0], dados_aluno[indice_matricula].notas[1], dados_aluno[indice_matricula].notas[2], dados_aluno[indice_matricula].media);
            }

            printf("\n");

            system("pause");
            system("cls");
        }

        // Imprimir a matricula, nome e nota final do aluno que obteve a maior nota de todas

        if (opcao == 7)
        {

            maior = dados_aluno[0].notas[0];
            indice_maior = 0;

            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    if (dados_aluno[i].notas[j] > maior)
                    {
                        maior = dados_aluno[i].notas[j];
                        indice_maior = i;
                    }
                }
            }

            printf("%03d %s %.2f", dados_aluno[indice_maior].matricula1, dados_aluno[indice_maior].nome, dados_aluno[indice_maior].media);

            printf("\n");

            system("pause");
            system("cls");
        }

        //Imprimir a matricula, nome e nota final do aluno que obteve a menor nota de todas

        if (opcao == 8)
        {
            menor = dados_aluno[0].notas[0];
            indice_maior = 0;

            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    if (dados_aluno[i].notas[j] < menor)
                    {
                        menor = dados_aluno[i].notas[j];
                        indice_menor = i;
                    }
                }
            }
            printf("%03d %s %.2f", dados_aluno[indice_menor].matricula1, dados_aluno[indice_menor].nome, dados_aluno[indice_menor].media);

            printf("\n");

            system("pause");
            system("cls");
        }

        // Imprimir quantos alunos foram aprovados e quantos alunos foram reprovados, imprima ainda a media geral

        if (opcao == 9)
        {
            int aprovados = 0, reprovados = 0;
            float media_geral = 0;

            for (i = 0; i < 3; i++)
            {
                if (dados_aluno[i].media >= 6)
                    aprovados++;

                else if (dados_aluno[i].media < 5)
                    reprovados++;

                media_geral += dados_aluno[i].media;
            }

            media_geral = media_geral / 3.0;

            printf("Alunos aprovados: %d\nAlunos reprovados: %d\nMedia geral: %.2f", aprovados, reprovados, media_geral);

            printf("\n");

            system("pause");
            system("cls");
        }

        // Sair do programa
    } while (!(opcao == 0));

    // Finalização do programa

    return 0;
}

// Função para calcular a media de cada aluno

float media(float n1, float n2, float n3)
{
    return ((n1 + n2 + n3) / 3.0);
}

// Função de ordenação da matricula pelo Bubblesort

void ordenar(matricula *dados_aluno)
{
    int contador;
    int aux;

    for (contador = 0; contador < 3; contador++)
    {
        for (int i = 0; i < 3 - 1 - contador; i++)
        {
            if (dados_aluno[i].matricula1 > dados_aluno[i + 1].matricula1)
            {
                aux = dados_aluno[i].matricula1;
                dados_aluno[i].matricula1 = dados_aluno[i + 1].matricula1;
                dados_aluno[i + 1].matricula1 = aux;
            }
        }
    }
}

// Função para buscar de matricula pelo Bubblesort

int buscando_matricula(matricula *dados_alunos, int buscar)
{
    for (int i = 0; i < 3; i++)
    {
        if (dados_alunos[i].matricula1 == buscar)
        {
            return i;
        }
    }
    return -1;
}
