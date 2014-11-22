/*
** POJ 1308 Is It A Tree
** Created by Rayn @@ 2014/04/27
** ���鼯
** 0 0 ����Ҳ����
** 1 1 0 0 ���� not a tree��
** ����֮��Ҫע�����ѭ���������
** 1 2 1 3 2 1 0 0 // not a tree
** ���������������
** 1 2 3 4 0 0 //not a tree
*/
#include <cstdio>
#include <cstring>

const int MAX = 110;
int pa[MAX];
int flag;

void Init()
{
    memset(pa, -1, sizeof(pa));
    flag = 0;
}
int FindSet(int x)
{
    if(pa[x] == -1)
        pa[x] = x;
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int main()
{
    int cases = 0, x, y, px, py;

    Init();
    while(scanf("%d%d", &x, &y) != EOF)
    {
        if(x == -1 && y == -1)
            break;
        if(x == 0 && y == 0)
        {
            if(!flag)
            {
                int cnt = 0;
                for(int i=0; i<MAX; ++i)
                {
                    if(pa[i] == i)
                        cnt++;
                }
                if(cnt > 1)
                    flag = 1;
            }
            if(!flag)
                printf("Case %d is a tree.\n", ++cases);  //��ĩ�ĵ�ţ�WA����
            else
                printf("Case %d is not a tree.\n", ++cases);
            Init();
            continue;
        }
        px = FindSet(x);
        py = FindSet(y);
        if(px == py)
            flag = 1;
        pa[py] = px;
    }
    return 0;
}
