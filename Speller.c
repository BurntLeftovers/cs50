// Implements a dictionary's functionality
// Make sure that LOAD works correctly first using the SMALL dictionary
// Start with ./speller dictionaries/small texts/cat.txt
// Checking for memory errors? Use: valgrind ./speller texts/lalaland.txt

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 35023;

// Hash table + Word count global variable for the word count function.
node *table[N];
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // setting some variables
    int table_check = 0;
    int compare;
    // commenting out a print-check that function is working printf("Word to check: %s\n", word);

    // converting to lower case so that hash funciton is correct
    char *temp_word = malloc(100);
    strcpy(temp_word, word);
    for(int i = 0; temp_word[i]; i++)
    {
        temp_word[i] = tolower(temp_word[i]);
    }

    // Get hash table value for checking of word from text.
    table_check = hash(temp_word);
    // commenting out a print-check that function is working printf("table[%i]: ", table_check);
    // free the memory for temp word for future.
    free(temp_word);
    // check the hash value for the word using (strcasecmp)
    // return true if it is in the list, false if not
    for (node *tmp = table[table_check]; tmp != NULL; tmp = tmp->next)
    {
        // copy the words into compare to check that they are identical. if 0 then they are the the same.
        compare = strcasecmp(word, tmp->word);
        if (compare == 0)
        {
            // commenting out a print-check that function is working printf("%s is in dictionary.\n", word);
            return true;
            break;
        }
        else if (tmp->next == NULL)
        {
            // commenting out a print-check that function is working printf("%s is NOT in dictionary.\n", word);
            return false;
            continue;
        }
    }
    return false;
}

// Hashes word to a number
// take input (word) from load function, hashes the value of the word into a number, which will be the hash table entry.
// should always produce the same value for the a word.
unsigned int hash(const char *word)
{
    // using the djb2 hash function from https://www.cs.dartmouth.edu/~campbell/cs50/hash.c
    unsigned long hash = 5381;
    int c;
    while ((c = *word++) != 0)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dic = fopen(dictionary, "r");
    // check if the file is valid (not NULL)
    if (dic == NULL)
    {
        fprintf(stderr, "Error. Could not read dictionary %s.\n", dictionary);
        unload();
        return false;
    }
    // creating some variables for use in the main loop.
    char storage[LENGTH];
    int temp_hash;

    // Read string words from dictionary file 1 at a time using scanf
    while (fscanf(dic, "%s", storage) != EOF)
    {
        // making sure the variable is clear
        temp_hash = 0;
        //create a new node using malloc
        node *n = malloc(sizeof(node));
        // check if malloc is null and exit
        if (n == NULL)
        {
            printf("Could not allocate memory for node.\n");
            return false;
        }

        // copy word into the node using strcpy, setting pointer as Null for now.
        strcpy(n->word, storage);
        n->next = NULL;
        // get hash location
        temp_hash = hash(n->word);

        // check if hash location already has data, if clear, store the word there.
        if (table[temp_hash] == NULL)
        {
            table[temp_hash] = n;
        }
        // if the hash location already has a value, add the word to the linked list
        else if (table[temp_hash] != NULL)
        {
            n->next = table[temp_hash];
            table[temp_hash] = n;
        }
        // commenting out print function printf("Dictionary word: %s\nTemp Hash: %i\nWord Count: %i\n", storage, temp_hash, word_count);
        word_count ++;
    }
    // comenting out test printf("End of Dictionary\n");
    fclose(dic);
    return true;
}

// Returns number of words in dictionary
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
// Loop over the hash table, and free all of the nodes in the linked list
bool unload(void)
{
    // establishing cursor and temporary node variables for the freeing of the memories.
    node *tmp = NULL;
    node *cursor = NULL;
    // Loop through each array of the Hash Table
    for (int x = 0; x <= N; x ++)
    {
        // point tmp at the top of the linked list
        tmp = table[x];
        // if the variable is empty, free tmp just to be safe.
        if (tmp == NULL)
        {
            free(tmp);
        }
        // found some data, let's clear it out.
        if (tmp != NULL)
        {
            // repeat until tmp is NULL (that means that we have found the end of the linked list)
            while (tmp != NULL)
            {
                // point cursor at temp so the data can be freed. Move tmp to the next node so we don't orphan our list, then free the cursor
                cursor = tmp;
                tmp = tmp->next;
                free(cursor);
            }
        }
    }
    free(tmp);
    return true;
}
