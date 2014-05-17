#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct pTrie {
	struct pTrie* a[26];
	int	word;
} pTrie;

pTrie *pTrieNew()
{
	pTrie *p;
	int i;

	p = malloc(sizeof(pTrie));
	for(i=0; i<26; i++) {
		p->a[i] = NULL;
	}	
	p->word = 0;
	return(p);
}

int pTrieInsert(pTrie *p, char *w) 
{
	if(p->a[w[0]-'a'] == NULL) p->a[w[0]-'a'] = pTrieNew();
	if(w[1] != 0) {
		return(pTrieInsert(p->a[w[0]-'a'], &w[1]));
	}
	p->a[w[0]-'a']->word = 1;
	return(0);
	
}

int pTriePrint(pTrie *p, char *prefix) 
{
	int i, prefixLen;
	char *newPrefix;
	
	if(p->word == 1) { printf("%s\n", prefix); }
	prefixLen = strlen(prefix);
	newPrefix = malloc((prefixLen + 2)*sizeof(char));
	strncpy(newPrefix, prefix, prefixLen+2);
	for(i=0; i<26; i++) {
		newPrefix[prefixLen] = 'a' + i;
		if(p->a[i] != NULL) pTriePrint(p->a[i], newPrefix);
	}
}

pTrie *pTriePrefix(pTrie *p, char *prefix, int prefixLen) 
{
	int i;

	if(prefixLen == 0) {
		if(p->word == 1) return p;
		for(i=0; i<26; i++) {
			if(p->a[i] != NULL) return p;
		}
		return(NULL);
	}
	return(pTriePrefix(p->a[prefix[0]-'a'], &prefix[1], prefixLen-1));
}



int main(int argc, char *argv[])
{
	pTrie	*p;
	pTrie*	pList[30];
	int	i, j, k, fd, rc;
	size_t	fileLen, wordLen;
	struct stat	sb;
	char	*f, *g, *cursor, *box;

	fd = open("/usr/share/dict/words", O_RDONLY);
	fstat(fd, &sb);
	f = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	g = malloc(sizeof(char)*sb.st_size);
	memcpy(g, f, sb.st_size);
	for(cursor = g; cursor < g + sb.st_size; cursor++)  {
		if(*cursor == 10) *cursor = 0;
		if(*cursor >= 'A' && *cursor <= 'Z') *cursor = *cursor + 'a' - 'A';
	}
	cursor = g;
	p = pTrieNew();
	for(i=0; i<30; i++) { pList[i] = pTrieNew(); }
	while(cursor < g + sb.st_size ) {
		wordLen = strlen(cursor);
		pTrieInsert(pList[wordLen], cursor);
		while(*cursor != 0 && cursor < g + sb.st_size) cursor++;
		cursor++;
	}
	for(i=0; i<30; i++) { pTriePrint(pList[i], ""); }
	return(0);		
}
