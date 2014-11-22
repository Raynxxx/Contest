/*
** UVA 11995 I Can Guess the Data Structure!
** Created by Rayn @@ 2014/3/30
** 基础数据结构,stack, queue, priority_queue 的模拟
*/
#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>
#define MAX 1005
using namespace std;

int order, num;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n;
    while(scanf("%d", &n)!=EOF)
    {
        stack<int> sta;
        queue<int> que;
        priority_queue<int> prique;

        bool is_sta = true;
        bool is_que = true;
        bool is_prique = true;

        for(int i=0; i<n; ++i)
        {
            scanf("%d%d", &order, &num);
            if(order == 1)
            {
                sta.push(num);
                que.push(num);
                prique.push(num);
            }
            if(order == 2)
            {
                if(is_sta)
                {
                    if(!sta.empty() && num == sta.top())
                        sta.pop();
                    else
                        is_sta = false;
                }
                if(is_que)
                {
                    if(!que.empty() && num == que.front())
                        que.pop();
                    else
                        is_que = false;
                }
                if(is_prique)
                {
                    if(!prique.empty() && num == prique.top())
                        prique.pop();
                    else
                        is_prique = false;
                }
            }
        }
        if(is_sta && !is_que && !is_prique)
            printf("stack\n");
        else if(!is_sta && is_que && !is_prique)
            printf("queue\n");
        else if(!is_sta && !is_que && is_prique)
            printf("priority queue\n");
        else if(!is_sta && !is_que && !is_prique)
            printf("impossible\n");
        else
            printf("not sure\n");
    }
    return 0;
}
