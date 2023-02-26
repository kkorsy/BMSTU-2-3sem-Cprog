// 1 вариант.

#include <stdio.h>
#define N 5

int input(char arr[N][N][N]);
void output(char arr[N][N][N], int n);

int main(void)
{
	char arr[N][N][N];
	int n = input(arr);
	output(arr, n);
	
	return 0;
}

int input(char arr[N][N][N])
{
	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			char word;
			int k = 0;
			while (scanf("%c", &word) == 1 && k < N)
			{
			    arr[i][j][k] = word;
			    k++;
			}
		}
		
	return n;
}

void output(char arr[N][N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; i++)
        {
            for (int k = 0; k < n; i++)
                printf("%c", arr[i][j][k]);
            printf(" ");
        }
        printf("\n");
    }
}
