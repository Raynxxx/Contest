/*
** HDU 2222 Keywords Search
** Created by Rayn @@ 2014/04/29
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//MaxNode = StringNumber * StringLength;
const int MAX = 1000010;
const int MaxNode = 10010 * 50;

struct ACAutomaton {
    //每个节点的儿子,即当前节点的状态转移
    int chd[MaxNode][26];
    //记录题目给的关键数据
    int val[MaxNode];
    //传说中的fail指针
    int fail[MaxNode];
    //队列,用于广度优先计算fail指针
    int que[MaxNode];
    //字母对应的ID
    int ID[128];
    //已使用结点个数
    int sz;

    //初始化,计算字母对应的儿子ID,如:'a'->0 ... 'z'->25
    void Init()
    {
        fail[0] = 0;
        for(int i=0; i<26; ++i)
        {
            ID[i+'a'] = i;
        }
    }
    //重新建树需先Reset
    void Reset()
    {
        memset(chd[0], 0, sizeof(chd[0]));
        memset(val, 0, sizeof(val));
        sz = 1;
    }
    //将权值为key的字符串a插入到trie中
    void Insert(char *a, int key)
    {
        int p = 0;
        for(; *a; ++a)
        {
            int c = ID[(int)(*a)];
            if(!chd[p][c])
            {
                memset(chd[sz], 0, sizeof(chd[sz]));
                val[sz] = 0;
                chd[p][c] = sz++;
            }
            p = chd[p][c];
        }
        val[p] += key;
    }
    //建立AC自动机,确定每个节点的权值以及状态转移
    void Construct()
    {
        int *head = que , *tail = que;
        for(int i=0; i<26; i++)
        {
            if(chd[0][i])
            {
                fail[chd[0][i]] = 0;
                *tail++ = chd[0][i];
            }
        }
        while(head != tail)
        {
            int u = *head++;
            for(int i=0; i<26; i++)
            {
                int &v = chd[u][i];
                if(v)
                {
                    *tail++ = v;
                    fail[v] = chd[fail[u]][i];
                    //以下一行代码要根据题目所给val的含义来写
                    //val[v] |= val[fail[v]];
                }
                else
                {
                    v = chd[fail[u]][i];
                }
            }
        }
    }
    int Search(char *str)
    {
        int ans = 0;
        int i = 0, p = 0;
        while(str[i])
        {
            int c = ID[(int)str[i]];
            while(p != 0 && !chd[p][c])
                p = fail[p];
            if(chd[p][c])
                p = chd[p][c];
            else
                p = 0;

            int tmp = p;
            while(tmp != 0 && val[tmp] != 0)
            {
                ans += val[tmp];
                val[tmp] = 0;
                tmp = fail[tmp];
            }
            ++i;
        }
        return ans;
    }
};

ACAutomaton solve;
char str[MAX];
int N;

int main()
{
    solve.Init();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        char tmp[60];
        scanf("%d", &N);
        solve.Reset();
        for(int i=0; i<N; ++i)
        {
            scanf("%s", tmp);
            solve.Insert(tmp, 1);
        }
        solve.Construct();
        scanf("%s", str);
        printf("%d\n", solve.Search(str));
    }
    return 0;
}
