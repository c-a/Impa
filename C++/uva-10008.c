#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char c;
    int count;
} character;

static int
cmp_character (const void* p1, const void* p2)
{
    const character* c1 = p1;
    const character* c2 = p2;

    return c1->count < c2->count;
}

#define N_CHARS 25

int main(void)
{
    character characters[N_CHARS];
    int i, n;
    char buffer[1024];

    for (i = 0; i < N_CHARS; i++)
    {
        characters[i].c = 'A' + i;
        characters[i].count = 0;
    }

    scanf("%d", &n);
    fgets(buffer, 1024, stdin);
    for (i = 0; i < n; i++)
    {
        char* c;

        if (!fgets(buffer, 1024, stdin))
            break;

        for (c = buffer; *c; c++)
        {
            if (!isalpha(*c))
                continue;

            *c = toupper(*c);
            characters[*c - 'A'].count++;
        }
    }

    qsort(&characters, N_CHARS, sizeof(character), cmp_character);

    for (i = 0; i < N_CHARS; i++)
    {
        if (characters[i].count == 0)
            break;

        printf("%c %d\n", characters[i].c, characters[i].count);
    }
    
    return 0;
}
