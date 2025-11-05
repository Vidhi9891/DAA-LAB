#include <stdio.h>
#include <string.h>

#define MAX 100

struct Cell
{
    int v; 
    char d; 
};

struct Cell cost[MAX][MAX];

int max(int x, int y){
    return (x > y) ? x : y;
}

int count = 0;
void printLCS(int i, int j, char a[], struct Cell cost[MAX][MAX])
{

    if (i == 0 || j == 0)
        return;

    if (cost[i][j].d == 'D')
    {
        printLCS(i - 1, j - 1, a, cost);
        printf("%c", a[i - 1]);
        count++;
    }
    else if (cost[i][j].d == 'U')
    {
        printLCS(i - 1, j, a, cost);
    }
    else if (cost[i][j].d == 'S')
    {
        printLCS(i, j - 1, a, cost); 
    }
}

int main()
{
    char a[MAX], b[MAX];
    int m, n;
    int i, j;

    printf("Enter string A: ");
    scanf("%s", a);
    strcpy(b, a); // copied a on b so now b have same string as a
    m = strlen(a);
    n = strlen(b);

    for (i = 0; i <= m; i++)
    {
        cost[i][0].v = 0;
        cost[i][0].d = 'H';
    }
    for (j = 0; j <= n; j++)
    {
        cost[0][j].v = 0;
        cost[0][j].d = 'H';
    }

    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1] && i != j)
            { 
                    cost[i][j].v = cost[i - 1][j - 1].v + 1;
                cost[i][j].d = 'D';
            }
            else
            {
                if (cost[i - 1][j].v >= cost[i][j - 1].v)
                {
                    cost[i][j].v = cost[i - 1][j].v;
                    cost[i][j].d = 'U';
                }
                else
                {
                    cost[i][j].v = cost[i][j - 1].v;
                    cost[i][j].d = 'S';
                }
            }
        }
    }
    printf("LRS: ");
    printLCS(m, n, a, cost);
    printf("\n");
    printf("length of lrs:%d\n", count);
    printf("\n");
    return 0;
}
