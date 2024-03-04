#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define QTD_TORRE 3

// Define o Tipo Disco, que contém a posição na Torre e o ID, este último necessário para o tamanho do disco
typedef struct disk
{
    int id;
} Disk;

// Define o Tipo Torre, contendo um ponteiro para o vetor de discos, o tamanho (quantidade de discos) e o tamanho atual
typedef struct tower
{
    Disk *discos;
    int tam;
    int currentTAM;
} Tower;

typedef struct Tower_Node
{
    Tower t;
    struct Tower_Node *left;
    struct Tower_Node *right;
} TowerNode;

// Cria a Torre com a Quantidade de Discos escolhida

Tower createTower(int size)
{
    Tower t;
    t.discos = (Disk *)malloc(size * sizeof(Disk));
    t.tam = size;
    t.currentTAM = 0;
    return t;
}

// Enche uma Torre com Todos os Discos
void fullfillDisk(Tower *t)
{
    for (int i = 0; i < t->tam; i++)
    {
        Disk d = {t->tam - i};
        t->discos[i] = d;
    }
    t->currentTAM = t->tam;
}

// Esvazia Todas as Torres
void clean_towers(Tower *towers)
{
    for (int j = 0; j < QTD_TORRE; j++)
    {
        for (int i = 0; i < towers[0].tam; i++)
        {
            towers[j].discos[i].id = 0;
            towers[j].currentTAM = 0;
        }
    }
}

// Remove um Disco de uma Torre
void removeDisk(Tower *t)
{
    Disk O = {0};
    t->discos[t->currentTAM - 1] = O;
    t->currentTAM--;
}

// Adiciona um disco à uma Torre
void addDisk(Tower *t, Disk *newD)
{
    t->currentTAM++;
    t->discos[t->currentTAM - 1] = *newD;
}

// Move um Disco de uma Torre para a Outra
int moveDisk(Tower *Out, Tower *In)
{
    if (Out->currentTAM == 0)
    {
        return FALSE;
    }

    Disk lastDisk_out = Out->discos[Out->currentTAM - 1];
    Disk lastDisk_in;

    if (In->currentTAM != 0)
    {
        lastDisk_in = In->discos[In->currentTAM - 1];
    }
    else
    {
        lastDisk_in = In->discos[In->currentTAM];
    }

    if (lastDisk_out.id > lastDisk_in.id && lastDisk_in.id != 0)
    {
        return FALSE;
    }
    removeDisk(Out);
    addDisk(In, &lastDisk_out);
    return TRUE;
}

void drawLine(int disco, int QTD_SPC)
{
    if (disco == 0)
    {
        for (int a = 0; a <= QTD_SPC - disco - 1; a++)
        {
            printf(" ");
        }
        printf("|");
    }
    else
    {
        for (int a = 0; a <= QTD_SPC - disco; a++)
        {
            printf(" ");
        }
        for (int b = 0; b < 2 * disco - 1; b++)
        {
            printf("=");
        }
    }
    for (int c = 0; c < QTD_SPC - disco; c++)
    {
        printf(" ");
    }
}

void printGame(Tower *tower_vec)
{
    printf("\n");
    for (int i = tower_vec[0].tam - 1; i > -1; i--)
    {
        for (int j = 0; j < QTD_TORRE; j++)
        {
            int id_disco = tower_vec[j].discos[i].id;
            drawLine(id_disco, tower_vec[0].tam - 1);
            printf("\t\t");
        }
        printf("\n");
    }
    printf("\n");
    return;
}

int verifica_win(Tower t)
{
    if (t.currentTAM == t.tam)
    {
        return TRUE;
    }
    return FALSE;
}

int resolve_recursivo(Tower *t, int act_tower, int next_tower, int movemnts)
{
    if (verifica_win(t[2]) == TRUE)
    {
        return movemnts;
    }

    int can_move = moveDisk(&t[act_tower], &t[next_tower]);

    if (can_move == TRUE)
    {
        system("cls");
        printGame(t);
        Sleep(50);
        movemnts++;
        if (act_tower == 0 && next_tower == 1)
        {
            next_tower++;
            return resolve_recursivo(t, act_tower, next_tower, movemnts);
        }
        if (act_tower == 0 && next_tower == 2)
        {
            next_tower--;
            return resolve_recursivo(t, act_tower, next_tower, movemnts);
        }
        if (act_tower == 1 && next_tower == 2)
        {
            next_tower -= 2;
            return resolve_recursivo(t, act_tower, next_tower, movemnts);
        }
        if (act_tower == 1 && next_tower == 0)
        {
            next_tower += 2;
            return resolve_recursivo(t, act_tower, next_tower, movemnts);
        }
        if (act_tower == 2 && next_tower == 0)
        {
            next_tower++;
            return resolve_recursivo(t, act_tower, next_tower, movemnts);
        }
        if (act_tower == 2 && next_tower == 1)
        {
            next_tower--;
            return resolve_recursivo(t, act_tower, next_tower, movemnts);
        }
    }
    else
    {
        if (t[0].tam % 2 == 0)
        {
            if (act_tower == 0 && next_tower == 1)
            {
                act_tower += 2;
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 0 && next_tower == 2)
            {
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 1 && next_tower == 2)
            {
                act_tower--;
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 1 && next_tower == 0)
            {
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 2 && next_tower == 0)
            {
                act_tower--;
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 2 && next_tower == 1)
            {
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
        }
        else
        {
            if (act_tower == 0 && next_tower == 1)
            {
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 0 && next_tower == 2)
            {
                act_tower++;
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 1 && next_tower == 2)
            {
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 1 && next_tower == 0)
            {
                act_tower++;
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 2 && next_tower == 0)
            {
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
            if (act_tower == 2 && next_tower == 1)
            {
                act_tower -= 2;
                return resolve_recursivo(t, next_tower, act_tower, movemnts);
            }
        }
    }
}

void resolver_sozinho(Tower *towers, int quantidade_movimentos)
{   
    system("cls");
    quantidade_movimentos=0;
    int towerOut, towerIn;
    int qtd_discos = towers[0].tam;
    while (TRUE)
    {
        printGame(towers);
        printf("Coeh, meu mano, move os discos da torre aih!\n");
        printf("Escolha a Torre de Saihda: ");
        scanf("%d", &towerOut);
        printf("Escolha a Torre de Entrada: ");
        scanf("%d", &towerIn);
        system("cls");
        int movement_validation = moveDisk(&towers[towerOut], &towers[towerIn]);

        int win_ = verifica_win(towers[QTD_TORRE - 1]);

        if (movement_validation == FALSE)
        {
            printf("Movimento Invalido\n");
        }
        else
        {
            quantidade_movimentos++;
        }

        if (win_ == TRUE)
        {
            if (quantidade_movimentos == (int)pow(2, qtd_discos) - 1)
            {
                printf("Parabens, vc resolveu a torre de hanoi de %d Discos com %d movimentos! Quantidade de movimentos PERFEITA!\n", qtd_discos, quantidade_movimentos);
            }
            else
            {
                printf("Parabens, vc resolveu a torre de hanoi de %d Discos com %d movimentos! Mas ainda da pra resolver com menos movimentos, vc consegue?\n", qtd_discos, quantidade_movimentos);
            }
            break;
        }
    }
}

void transforma_tempo(int segundos, int *tempo){
    int hora = segundos/3600;
    int minutos = (segundos%3600)/60;
    int seconds = ((segundos%3600)%60);
    tempo[0] = hora;
    tempo[1] = minutos;
    tempo[2] = seconds;

    return;
}

void gamePlay(void)
{
    // Let's play
    // Função que inicia o jogo

    int qtd_discos;
    int forma_de_resolver;

    printf("Hello, quer tentar a torre de Hanoi com quantos discos? ");
    scanf("%d", &qtd_discos);

    Tower towers[QTD_TORRE];
    for (int i = 0; i < QTD_TORRE; i++)
    {
        towers[i] = createTower(qtd_discos);
    }
    clean_towers(towers);
    fullfillDisk(&towers[0]);
    int tempo[3] = {};
    int quant_movements = 0;
    int run = TRUE;
    clock_t time;
    while (run == TRUE)
    {   
        //Zera o vetor de tempo
        for(int i=0; i<3; i++){
            tempo[i] = 0;
        }
        clean_towers(towers);
        fullfillDisk(&towers[0]);
        quant_movements = 0;
        printf("----------- MENU ----------------\n");
        printf("[0] - Resolver Sozinho\n");
        printf("[1] - Observar o Algoritmo Resolvendo\n");
        printf("[2] - Sair\n");

        scanf("%d", &forma_de_resolver);


        switch (forma_de_resolver)
        {
        case 0:
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
            time = clock();
            resolver_sozinho(towers, quant_movements);
            time = clock() - time;
            int int_segundos = ((int)time)/(CLOCKS_PER_SEC);
            float frac_segundos = ((float)time)/(CLOCKS_PER_SEC)-((int)time)/(CLOCKS_PER_SEC);
            transforma_tempo(int_segundos, &tempo[0]);
            printf("Vc resolveu em: %d Horas, %d Minutos, %d Segundos e %.3f Milesimos de segundos\n",tempo[0], tempo[1], tempo[2], frac_segundos);
        }
        break;
        case 1:
        {   
            time = clock();
            if (qtd_discos % 2 == 0)
            {
                quant_movements = resolve_recursivo(towers, 0, 1, quant_movements);
            }
            else
            {
                quant_movements = resolve_recursivo(towers, 0, 2, quant_movements);
            }

            time = clock() - time;
            int int_segundos = ((int)time)/(CLOCKS_PER_SEC);
            float frac_segundos = ((float)time)/(CLOCKS_PER_SEC)-((int)time)/(CLOCKS_PER_SEC);
            transforma_tempo(int_segundos, tempo);

            if (quant_movements == (int)pow(2, qtd_discos) - 1)
            {
                printf("Parabens, vc resolveu a torre de hanoi de %d Discos com %d movimentos! Quantidade de movimentos PERFEITA!\n", qtd_discos, quant_movements);
            }
            else
            {
                printf("Parabens, vc resolveu a torre de hanoi de %d Discos com %d movimentos! Mas ainda da pra resolver com menos movimentos, vc consegue?\n", qtd_discos, quant_movements);
            }

            printf("O Algoritmo resolveu em: %d Horas, %d Minutos, %d Segundos e %.3f Milesimos de segundos\n",tempo[0], tempo[1], tempo[2], frac_segundos);
        }
        break;
        case 2:
        {
            run = FALSE;
        }
        break;

        default:
            printf("Opcao Inválida");
        }
    }
}

int main(void)
{
    gamePlay();
}