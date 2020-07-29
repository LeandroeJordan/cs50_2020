// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"
#define HASHT_SIZE 1500
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node* hasht[HASHT_SIZE];


unsigned int nword = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char temp_word[strlen(word)];
    strcpy(temp_word, word);
    for (int ind = 0; temp_word[ind] != '\0'; ind++)
    {
        temp_word[ind] = tolower(temp_word[ind]);
    }
    int ihash = hash(temp_word);
    if (hasht[ihash] != NULL)
    {
        for(node *nodep = hasht[ihash]; nodep != NULL; nodep = nodep->next)
        {
            if (strcmp(nodep->word, temp_word) ==0)
            {
                return true;
            }
        }    
        return false;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //DJB2 Dan Bernstein
    int nhash = 401;
	int c;

	while (*word != '\0') {
		nhash = ((nhash << 4) + (int)(*word)) % HASHT_SIZE;
		word++;
	}

	return nhash % HASHT_SIZE;
    
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        return false;
    }
    else
    {
        for (int ind = 0; ind < HASHT_SIZE; ind++)
        {
            hasht[ind] = NULL;
        }
        char word[LENGTH + 1];
        node* new_nodep;
        while (fscanf(infile, "%s", word) != EOF)
        {
            nword++;
            do
            {
               new_nodep = malloc(sizeof(node));
               if (new_nodep == NULL)
               {
                   free(new_nodep);
               }
            } while (new_nodep == NULL);
            
            strcpy(new_nodep->word, word);
            int ihash = hash(word);
            new_nodep->next = hasht[ihash];
            hasht[ihash] = new_nodep;
            
        }
        fclose(infile);
        
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return nword;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (nword == 0)
    {
        return false;
    }
    else
    {
       for (int ind = 0; ind < HASHT_SIZE; ind++)
        {
            if (hasht[ind] != NULL)
            {
                node* temp = hasht[ind];
                while (temp != NULL)
                {
                    node* pointr = temp;
                    temp = temp->next;
                    free(pointr);
                }
            }
        } 
        return true;
    }
    
}
