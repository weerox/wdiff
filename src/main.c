#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIM "\n .!?"

void cmp(char *, char *);
/* add c to str with length len
	 set len to -1 to make function calculate length */
char *stradd(char *str, int len, char c, int null_terminated);

char *stradd(char *str, int len, char c, int null_terminated)
{
	if (len == -1 && !null_terminated)
		return NULL;
	else if (len == -1 && null_terminated)
		len = strlen(str);

	str = realloc(str, len + 1);
	*(str + len) = c;
	
	if (null_terminated)
		*(str + len + 1) = 0;

	return str;
}

int main(int argc, char **argv)
{
	cmp("Lorem ipsum", "Lorem dolor");
	return 0;
}

void cmp(char *file1, char *file2)
{
	char *word1 = malloc(0);
	char *word2 = malloc(0);
	unsigned int p1, p2, len1, len2, wlen1, wlen2;
	p1 = 0;
	p2 = 0;
	len1 = strlen(file1);
	len2 = strlen(file2);
	wlen1 = 0;
	wlen2 = 0;
	int lock1, lock2;
	lock1 = 0;
	lock2 = 0;
	
	printf("file1: %s\n", file1);
	printf("file2: %s\n", file2);
	printf("len1: %i\n", len1);
	printf("len2: %i\n", len2);

	while (p1 < len1 || p2 < len2)
	{
		printf("p1 %i		p2 %i\n", p1, p2);
		
		if (p1 == len1)
		{
			printf("file1 end\n");

			if (wlen1 > 0)
				printf("deletion: %s\n", word1);

			/* end of file1 reached, all from here on is additions  */
			for (; p2 < len2; p2++)
			{
				if (strchr(DELIM, *(file2 + p2)) != NULL)
				{
					printf("loop1 delim\n");
					if (wlen2 > 0)
						printf("addition: %s\n", word2);
					word2 = realloc(word2, 0);
					wlen2 = 0;
					continue;
				}
				printf("p2: %i\n", p2);
				stradd(word2, wlen2, *(file2 + p2), 0);
				wlen2++;
			}
			printf("addition: %s\n", word2);
			break;
		}
		else if (p2 == len2)
		{
			printf("file2 end\n");
			
			if (wlen2 > 0)
				printf("addition: %s\n", word2);

			/* end of file2 reached, all from here on is deletions */
			for (; p1 < len1; p1++)
			{
				if (strchr(DELIM, *(file1 + p1)) != NULL)
				{
					printf("loop2 delim\n");
					if (wlen1 > 0)
						printf("deletion: %s\n", word1);
					word1 = realloc(word1, 0);
					wlen1 = 0;
					continue;
				}
				printf("p1: %i\n", p1);
				stradd(word1, wlen1, *(file1 + p1), 0);
				wlen1++;
			}
			printf("deletion: %s\n", word1);
			break;
		}

		if (strchr(DELIM, *(file2 + p2)) != NULL)
		{
			printf("loop delim\n");
			
			if (wlen1 == 0 && wlen2 > 0)
			{
				printf("addition: %s\n", word2);
			}
			word1 = realloc(word1, 0);
			word2 = realloc(word2, 0);
			wlen1 = 0;
			wlen2 = 0;
			
			if (!lock1)
				p1++;
			p2++;
		}
		else if (*(file1 + p1) != *(file2 + p2))
		{
			lock1 = 1;
			printf("file2 different\n");
			stradd(word2, wlen2, *(file2 + p2), 0);
			printf("word2: %s\n", word2);
			wlen2++;
			p2++;
		}
		else
		{
			lock1 = 0;
			p1++;
			p2++;
		}
	}
}
