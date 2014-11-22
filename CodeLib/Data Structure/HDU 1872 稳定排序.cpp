/*
** ÎÈ¶¨ÅÅĞò
** Created by Rayn @@ 2014/3/25
*/
#include <cstdio>
#include <cstring>

typedef struct{
    char name[60];
    int score;
} stu;

stu arr1[310], arr2[310];

void StableSort(stu *arr, int n)   //ÎÈ¶¨µÄÃ°ÅİÅÅĞò
{
	int i, j;
	stu tmp;
	for(i=1; i<n; i++)
    {
		for(j=0; j<n-i; j++)
		{
			if(arr[j].score < arr[j+1].score)
			{
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}
int main()
{
    int n;

    while(scanf("%d", &n) != EOF)
    {
        for(int i=0; i<n; ++i)
            scanf("%s %d", &arr1[i].name, &arr1[i].score);
        for(int i=0; i<n; ++i)
            scanf("%s %d", &arr2[i].name, &arr2[i].score);

        StableSort(arr1, n);

        int flag = 0;
        for(int i=0; i<n; ++i)
        {
            if(strcmp(arr1[i].name, arr2[i].name) != 0)
            {
                if(arr1[i].score != arr2[i].score)
                    flag = 1;
                else
                    flag = 2;
            }
        }

        if(flag == 0)
        {
            printf("Right\n");
            continue;
        }
        if(flag == 1)
            printf("Error\n");
        else if(flag == 2)
            printf("Not Stable\n");
        for(int i=0; i<n; ++i)
            printf("%s %d\n", arr1[i].name, arr1[i].score);

    }
    return 0;
}
