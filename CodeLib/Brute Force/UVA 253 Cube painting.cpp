/*
** UVA 253 Cube painting
** Created by Rayn @@ 2014/04/25
** 翻转然后枚举
*/
#include <cstdio>
#include <cstring>
const int MAX = 20;

char str[MAX], str1[MAX], str2[MAX];
char tmp[MAX];
int dir[6][6] = {
    {0,1,2,3,4,5}, {1,5,2,3,0,4}, {2,1,5,0,4,3},
    {3,1,0,5,4,2}, {4,0,2,3,5,1}, {5,4,2,3,1,0}
};

bool Judge()
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            tmp[j] = str1[dir[i][j]];
        }
        for(int j=0; j<4; j++)
        {
            char ch;
            ch = tmp[1];
            tmp[1] = tmp[2];
            tmp[2] = tmp[4];
            tmp[4] = tmp[3];
            tmp[3] = ch;
            if(strcmp(tmp, str2)==0)
                return true;
        }
    }
    return false;
}
int main()
{
    while(scanf("%s",str) != EOF)
    {
        for(int i=0; i<6; i++)
            str1[i] = str[i];
        for(int i=0; i<6; i++)
            str2[i] = str[i+6];
        if(Judge())
            printf("TRUE\n");
        else
            printf("FALSE\n");
    }
    return 0;
}
