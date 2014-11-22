/*
** HDU 1277 ȫ�ļ���
** Created by Rayn @@ 2014/04/30
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//MaxNode = StringNumber * StringLength;
const int MaxNode = 10010*60;
const int MAX = 60010;
const int Child = 10;

struct ACAutomaton {
    //ÿ���ڵ�Ķ���,����ǰ�ڵ��״̬ת��
    int chd[MaxNode][Child];
    //��¼��Ŀ���Ĺؼ�����
    int val[MaxNode];
    //��˵�е�failָ��
    int fail[MaxNode];
    //����,���ڹ�����ȼ���failָ��
    int que[MaxNode];
    //��ĸ��Ӧ��ID
    int ID[128];
    //��ʹ�ý�����
    int sz;
    int res[1010];

    //��ʼ��,������ĸ��Ӧ�Ķ���ID,��:'a'->0 ... 'z'->25
    void Init()
    {
        fail[0] = 0;
        for(int i=0; i<Child; ++i)
        {
            ID[i+'0'] = i;
        }
    }
    //���½�������Reset
    void Reset()
    {
        memset(res, 0, sizeof(res));
        memset(chd[0], 0, sizeof(chd[0]));
        memset(val, 0, sizeof(val));
        sz = 1;
    }
    //��ȨֵΪkey���ַ���a���뵽trie��
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
        val[p] = key;
    }
    //����AC�Զ���,ȷ��ÿ���ڵ��Ȩֵ�Լ�״̬ת��
    void Construct()
    {
        int *head = que , *tail = que;
        for(int i=0; i<Child; i++)
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
            for(int i=0; i<Child; i++)
            {
                int &v = chd[u][i];
                if(v)
                {
                    *tail++ = v;
                    fail[v] = chd[fail[u]][i];
                    //����һ�д���Ҫ������Ŀ����val�ĺ�����д
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
            if(tmp != 0 && val[tmp] != 0)
            {
                res[ans++] = val[tmp];
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
int M, N;

int main()
{
    solve.Init();
    solve.Reset();

    char ch, tmp[100];
    int i = 0;

    scanf("%d%d", &M, &N);
    str[0] = 0;
    while(M--)
    {
        scanf("%s", tmp);
        strcat(str, tmp);
    }
    for(int i=1; i<=N; ++i)
    {
        scanf("%s %s %s %s", tmp, tmp, tmp, tmp);
        solve.Insert(tmp, i);
    }
    solve.Construct();

    int cnt = solve.Search(str);
    if(cnt == 0)
        puts("No key can be found !");
    else
    {
        printf("Found key:");
        for(i=0; i<cnt; i++)
        {
            printf(" [Key No. %d]", solve.res[i]);
        }
        puts("");
    }
    return 0;
}

