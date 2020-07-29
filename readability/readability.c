#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int Slen = 0;
    string text;
    //loop para input das frases
    do
    {
        text = get_string("Text: ");
    }
    while ((Slen = strlen(text)) == 0);
    int i = 0, cletters = 0, cwords = 0, csentences = 0;
  
    //obter tamanho de letters, sentences, words
 
    for (i = 0; i <= Slen; i++)
    {
        if (toupper(text[i]) >= 'A' &&  toupper(text[i]) <= 'Z') // check is is letters
        {
            cletters++;
        }
        else
        {
            if (text[i] == ' ') // check is is spaces
            {
                cwords++;
            }
            else if (text[i] == '!' || text[i] == '.'  || text[i] == '?') // check is is sinais
            {
                csentences++;
            }
        }
    }
    cwords++;
  
    float index = 0.0588 * (((float)(cletters) * 100) / cwords) - 0.296 * (((float)csentences * 100) / cwords) - 15.8;
    int grade = round(index);
    // print result
    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
 
}
