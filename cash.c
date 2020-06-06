#include <cs50.h>
#include <stdio.h>
#include <math.h>

void calculate(float *coin, int *cont, float *change)
{
    // Função que calcula a quantidade de moedas
    
    int partint = ((int) trunc(*change / *coin));
    *cont = *cont + partint;
    *change = *change - (*coin * partint);
        
}

int main(void)
{
   
    float change;
    float coin;
    int cont;         

    //array de moedas
    float coins[4] = {round(0.25 * 100), round(0.10 * 100), round(0.05 * 100), round(0.01 * 100)
                     };

    // loop para entrada de dados
   
    do
    {
        change =  get_float("How much change is owed. (Just positives Values)?\n");
        change = round(change * 100);
    }   
    while (change <= 0.00);
    
    cont = 0;
    int i;
    
    // loop para percorrer o array de moedas
    for (i = 0; i <= 3; i++)
    {   
        if (change > coins[i])
        {
            coin = coins[i];
            calculate(&coin, &cont, &change); 
        } 
        else if (change == coins[i])      
        {            
            cont = cont + 1; 
            break;
                   
        } 
        
    }

//Resultado Final
    printf("%i\n", cont);  
     
}
