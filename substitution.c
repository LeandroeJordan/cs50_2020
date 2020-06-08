#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>



int validatekey(string key)
{
//Validate KEY
    int cdup = 0, ckey = 0;
    
    
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    else
    {
    
        //check for repeted characters and digits in the KEY
        for (ckey = 0; ckey <= 25; ckey++)
        {
            if (!isalpha(key[ckey]))
            {
                printf("Key must only contain alphabetic chcaracters.");
                return 1;
                break;
            }
            else
            {
                //check for repeted characters
                for (cdup = ckey + 1; cdup <= 25; cdup++)
                {
                    if (key[ckey] == key[cdup])
                    {
                        printf("Key must not contain repeated chcaracters.");
                        return 1;
                        break;
                    }
                }
            }
        }
        
        return 0;
    }
}


int main(int argc, string argv[])
{
    
    string alphabect =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string plaintext = " ";
    string key = argv[1]; //Get the key from argument
   
    int cont = 0, contalf = 0, Slen = 0, vreturn = 0;
    
    
    
    //Validate KEY
  
    if (argc == 1)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
        vreturn = 1;
    }
    else
    {
        vreturn = validatekey(key);
    }
    
    if (vreturn == 0)
    {
        // Get the plaintext
        do
        {
            plaintext = get_string("plaintext: ");
       
        }
        while ((Slen = strlen(plaintext)) == 0);   
    
    
        //printf("plaintext:  %s\n", plaintext);
        printf("ciphertext: ");
        //Enciphier plaintext
        for (cont = 0; cont < Slen; cont++) //loop to read each caraters from plain text
    
        {
            if (isalpha(plaintext[cont]))
        
            {
                contalf = 0;
                while (toupper(alphabect[contalf]) != toupper(plaintext[cont])) //loop to search plaintext caracter in alphabet
                {
                    contalf++;
            
                }
            }
            else
            {
                
                printf("%c", plaintext[cont]);
                
            }
            //Print the characters alpha
            if (contalf <= 25 && isalpha(plaintext[cont]))
            {
                if (islower(plaintext[cont]))
                {    
                    printf("%c",  tolower(key[contalf]));
                }
                else
                {
                    printf("%c",  toupper(key[contalf]));    
                }
            }
        
        }
    }    
    printf("\n");
    return vreturn;
}    