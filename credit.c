#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    long cardnum, number;
    string company;

    int contdig = 0;
    int numbers[16];
    
    cardnum =  get_long("Number: "); 
    number = cardnum;
   
    //Carregar o array de numeros de cartoes separando os digitos
    while (number != 0)
    {
        numbers[contdig] = (int)(number % 10);
        number = number / 10;
        contdig++;
    }

    int i, prod;
    // Calculando os produtos dos numeros * 2
    for (i = 1; i <= (contdig - 1); i = i + 2)
    {
        if ((numbers[i] * 2) >= 10)
        {
            prod = prod + (((numbers[i] * 2) % 10) + 1);    
        } 
        else
        {
            prod = prod + (numbers[i] * 2);     
        }
    }

   
    int sum = 0;

    //Fazendo o somatório dos digitos restantes com o produto
    for (i = 0; i <= (contdig - 1); i = i + 2)
    
    {
        sum = sum + numbers[i];     

    }
    sum = sum + prod;

    // Imprimindo o resultado final 
    sum = sum % 10;
    if (sum == 0 && contdig > 12)
    {
        if (numbers[(contdig - 1)] == 4)
        { 
            printf("VISA\n"); 
        } 
        else if (numbers[(contdig - 1)] == 5 && numbers[(contdig - 2)] <= 5)
        {
            printf("MASTERCARD\n");
        } 
        else if (numbers[(contdig - 1)] == 3 && (numbers[(contdig - 2)] == 4 || numbers[(contdig - 2)] == 7))
        {
            printf("AMEX\n");
        } 
        else
        {
            printf("INVALID\n");  
        }
    } 
    else
    {
        printf("INVALID\n");  
    }
}   

