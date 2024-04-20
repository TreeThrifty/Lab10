#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    // the times the word comes up\ the ocurrances
    int count;
    // array of pointers to next node
    struct Trie *next[26];

};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    // if the word is empty, return
    if (word[0] == '\0')
    {
        return;
    }
    // allocating memory for the next node if it is null
    if (pTrie->next[word[0] - 'a'] == NULL)
    {
        pTrie->next[word[0] - 'a'] = (struct Trie *)malloc(sizeof(struct Trie));
        // check if malloc was successful
        if (pTrie->next[word[0] - 'a'] == NULL) 
        {
            fprintf(stderr, "Failed to allocate memory.\n");
            exit(1);
        }
        pTrie->next[word[0] - 'a']->count = 0;
        for (int i = 0; i < 26; i++)
        {
            pTrie->next[word[0] - 'a']->next[i] = NULL;
        }
    }
    // incrementing count when the word is empty 
    if (word[1] == '\0')
    {
        pTrie->next[word[0] - 'a']->count++;
    }
    // if not , call the insert function recursively
    else
    {
        insert(pTrie->next[word[0] - 'a'], word + 1);
    }



}



// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    // if the word is empty, the count is

    if (word[0] == '\0')
    {
        return pTrie->count;
    }

    // when the next node is null, 0 is returned
    if (pTrie->next[word[0] - 'a'] == NULL)
    {
        return 0;
    }

    // if the word is not empty, call the numberOfOccurances function recursively
    else
    {
        return numberOfOccurances(pTrie->next[word[0] - 'a'], word + 1);
    }





}

// deallocating the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{

    // if the trie is null, return null
    
    if (pTrie == NULL)
    {
        return NULL;
    }

    // deallocating the trie structure
    for (int i = 0; i < 26; i++)
    {
        pTrie->next[i] = deallocateTrie(pTrie->next[i]);
    }
    free(pTrie);
    return NULL;





}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    // check if malloc was successful
    if (pTrie == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
    }
    pTrie->count = 0;
    for (int i = 0; i < 26; i++)
    {
        pTrie->next[i] = NULL;
    }
    return pTrie;



}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    // open the file
    FILE *file = fopen(filename, "r");
    // check if the file was opened successfully
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file.\n");
        exit(1);
    }
    // read the number of words in the dictionary
    int numWords;
    fscanf(file, "%d", &numWords);
    // read the words in the dictionary
    for (int i = 0; i < numWords; i++)
    {
        pInWords[i] = (char *)malloc(256);
        // check if malloc was successful
        if (pInWords[i] == NULL) 
        {
            fprintf(stderr, "Failed to allocate memory.\n");
            exit(1);
        }
        fscanf(file, "%s", pInWords[i]);
    }
    // close the file
    fclose(file);
    return numWords;




}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}