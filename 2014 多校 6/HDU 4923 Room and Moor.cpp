/*
** HDU 4923 Room and Moor
** Created by Rayn @@ 2014/08/18
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
const int maxn = 100050;

struct Node
{
    int id;
    int cnt1, cnt0;
    double Bi;
    Node() {}
    Node(int id, int cnt1, int cnt0, double bi):
        id(id), cnt1(cnt1), cnt0(cnt0), Bi(bi) {}
};

int arr[maxn];
Node data[maxn];
stack<Node> sta;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &arr[i]);
        }
        int l = 0, r = n-1;
        while(l < n && arr[l] == 0)
            l++;
        while(r >= 0 && arr[r] == 1)
            r--;
        int m = 0;
        for(int i = l; i <= r; )
        {
            int j = 0, k = 0;
            while(i < n && arr[i] == 1) {
                i++;
                j++;
            }
            while(i < n && arr[i] == 0) {
                i++;
                k++;
            }
            data[m] = Node(m, j, k, (double)j/(j+k));
            m++;
        }

        while(!sta.empty())
            sta.pop();
        for(int i = 0; i < m; ++i)
        {
            if(sta.empty())
            {
                sta.push(data[i]);
            }
            else
            {
                if(sta.top().Bi <= data[i].Bi)
                {
                    sta.push(data[i]);
                }
                else
                {
                    while(true)
                    {
                        Node t = sta.top();
                        if(t.Bi > data[i].Bi)
                        {
                            data[i].cnt1 += t.cnt1;
                            data[i].cnt0 += t.cnt0;
                            data[i].Bi = (double)data[i].cnt1 / (data[i].cnt1 + data[i].cnt0);
                            sta.pop();
                        }
                        else
                        {
                            sta.push(data[i]);
                            break;
                        }
                        if(sta.empty())
                        {
                            sta.push(data[i]);
                            break;
                        }
                    }
                }
            }
        }
        double res = 0;
        while(!sta.empty())
        {
            Node t = sta.top();
            sta.pop();
            res += t.Bi*t.Bi*t.cnt0 + (1-t.Bi)*(1-t.Bi)*t.cnt1;
        }
        printf("%.6f\n", res);
    }
    return 0;
}
