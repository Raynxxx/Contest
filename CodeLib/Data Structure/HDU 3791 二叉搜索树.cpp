/*
** HDU 3791 ¶þ²æËÑË÷Ê÷
** Created by Rayn @@ 2014/04/15
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1024;
char str1[12], str2[12];
int tree1[MAX], tree2[MAX];

int main()
{
    int n;
    while(scanf("%d", &n) != EOF && n)
    {
        scanf("%s", str1);

        memset(tree1, -1, sizeof(tree1));
        for(int i=0; str1[i] != '\0'; ++i)
        {
            int num = str1[i] - '0';
            int j = 1;
            while(tree1[j] != -1)
            {
                if(num <= tree1[j])
                    j = j*2;
                else
                    j = j*2 + 1;
            }
            tree1[j] = num;
        }
        while(n--)
        {
            scanf("%s", str2);
            memset(tree2, -1, sizeof(tree2));
            for(int i=0; str2[i] != '\0'; ++i)
            {
                int num = str2[i] - '0';
                int j = 1;
                while(tree2[j] != -1)
                {
                    if(num <= tree2[j])
                        j = j*2;
                    else
                        j = j*2 + 1;
                }
                tree2[j] = num;
            }
            int flag = 1;
            for(int i=0; i<1024; ++i)
            {
                if(tree1[i] != tree2[i])
                {
                    flag = 0;
                    break;
                }
            }
            if(flag)
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
