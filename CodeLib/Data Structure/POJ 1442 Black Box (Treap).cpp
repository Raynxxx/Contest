#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int maxNode=444444;
const int INF=0x3f3f3f3f;
int M,N,II,cc;
int arr[33000];
int u[33000];

struct Treap
{
    int root,treapCnt,key[maxNode],priority[maxNode],
    childs[maxNode][2],cnt[maxNode],ssize[maxNode];

    Treap()
    {
        root=0;
        treapCnt=1;
        priority[0]=INF;
        ssize[0]=0;
    }

    void update(int x)
    {
        ssize[x]=ssize[childs[x][0]]+cnt[x]+ssize[childs[x][1]];
    }
    void rotate(int &x,int t)
    {
        int y=childs[x][t];
        childs[x][t]=childs[y][1-t];
        childs[y][1-t]=x;
        update(x);
        update(y);
        x=y;
    }
    void _insert(int &x,int k)
    {
        if(x)
        {
            if(key[x]==k)
            {
                cnt[x]++;
            }
            else
            {
                int t=key[x]<k;
                _insert(childs[x][t],k);
                if(priority[childs[x][t]]<priority[x])
                {
                    rotate(x,t);
                }
            }
        }
        else
        {
            x=treapCnt++;
            key[x]=k;
            cnt[x]=1;
            priority[x]=rand();
            childs[x][0]=childs[x][1]=0;
        }
        update(x);
    }

    int _getKth(int &x,int k)
    {
        if(k<=ssize[childs[x][0]])
        {
            return _getKth(childs[x][0],k);
        }
        k -= ssize[childs[x][0]] + cnt[x];
        if(k<=0)
        {
            return key[x];
        }
        return _getKth(childs[x][1],k);
    }

    void Insert(int k)
    {
        _insert(root,k);
    }

    int GetKth(int k)
    {
        return _getKth(root,k);
    }

}T;

int main()
{
    scanf("%d%d",&M,&N);

    II=0;cc=1;

    for(int i=1;i<=M;i++)
    {
        scanf("%d",arr+i);
    }
    for(int i=1;i<=N;i++)
    {
        scanf("%d",u+i);
    }
    for(int i=1;i<=M;i++)
    {
        T.Insert(arr[i]);
        while(i==u[cc])
        {
            cc++;II++;
            printf("%d\n",T.GetKth(II));
        }
    }
    return 0;
}
