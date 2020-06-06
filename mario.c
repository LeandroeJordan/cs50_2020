#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int lines;
    //Solicita a informação de quantas linhas
    do
    {
        lines =  get_int("How many lines (1 - 8)?\n");
    } 
    while (lines < 1 || lines > 8);
    
    int col = 1;
    int lin;
    //imprir a piramide    
    for (lin = 1; lin < (lines + 1); lin++)
    {
        col = 1;
        //Imprimir espaços anteriores
        while (col <= (lines - lin))
        {
            printf(" ");
            col++;
        }              
        //imprimir as #
        for (; col <= lines; col++)
        {
            printf("#");
        }
        printf("  "); //imprimir os dois espacos entre as colunas
        for (col = 1; col < (lin + 1); col++)
        {
            printf("#"); //imprimir a parte final
        }
        printf("\n");
    }

}
