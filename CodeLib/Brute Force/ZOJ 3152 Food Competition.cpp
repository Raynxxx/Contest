/*
** ZOJ 3152 Food Competition
** Created by Rayn @@ 2014/08/04
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50010;
const LL INF = 0x7f7f7f7f7f7f7f7fLL;

int n, a, b;
int pos[maxn], dir[maxn];
long long W, Va1, Va2, Wa, Vb1, Vb2, Wb;
long long ta, tb;
vector<LL> pa, pb;

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d%d", &n, &a, &b) != EOF)
    {
        pa.clear();
        pb.clear();
        for(int i = 0; i < n; ++i) {
            scanf("%d", &pos[i]);
        }
        for(int i = 0; i < n; ++i) {
            scanf("%d", &dir[i]);
        }
        scanf("%lld%lld%lld%lld%lld%lld%lld", &W, &Va1, &Va2, &Wa, &Vb1, &Vb2, &Wb);
        swap(Va1, Vb1);
        swap(Va2, Vb2);
        ta = -a * (Va1 + Va2);
        tb = b * (Vb1 + Vb2);
        for(int i = 0; i < n; ++i)
        {
            if(pos[i] < 0)
            {
                if(dir[i] == -1)
                {
                    pa.push_back(ta + Va2 * abs(pos[i]));
                    W += Wa;
                }
                else if(dir[i] == 1)
                {
                    pa.push_back(ta - Va1 * abs(pos[i]));
                }
            }
            else if(pos[i] > 0)
            {
                if(dir[i] == 1)
                {
                    pb.push_back(tb + Vb2 * pos[i]);
                    W += Wb;
                }
                else if(dir[i] == -1)
                {
                    pb.push_back(tb - Vb1 * pos[i]);
                }
            }
        }

        LL l = 0ll, r = INF;
        while(l < r)
        {
            LL mid = (l + r) / 2;
            LL now = W;
            for(int i = 0; now > 0 && i < (int) pa.size(); ++i)
            {
                now -= (mid + pa[i]) / ta * Wa;
            }
            for(int i = 0; now > 0 && i < (int) pb.size(); ++i) {
                now -= (mid + pb[i]) / tb * Wb;
            }
            if(now <= 0)
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        LL t = l;
        double res1 = 0, res2 = 0;
        bool fa = false, fb = false;
        for(int i = 0; i < (int) pa.size(); ++i) {
            LL now = (t + pa[i]) / ta * Wa;
            if ((t + pa[i]) % ta == 0) {
                now -= Wa;
                fa = true;
            }
            W -= now;
            res1 += now;
        }
        for(int i = 0; i < (int) pb.size(); ++i) {
            LL now = (t + pb[i]) / tb * Wb;
            if ((t + pb[i]) % tb == 0) {
                now -= Wb;
                fb = true;
            }
            W -= now;
            res2 += now;
        }

        if(fa && fb)
        {
            if(Wa * 2 < W)
            {
                res1 += Wa;
                res2 += W - Wa;
            }
            else if(Wb * 2 < W)
            {
                res1 += W - Wb;
                res2 += Wb;
            }
            else
            {
                res1 += W / 2.0;
                res2 += W / 2.0;
            }
        }
        else if(fa)
        {
            res1 += W;
        }
        else if(fb)
        {
            res2 += W;
        }
        printf("%.1f %.1f\n", res1, res2);
    }
    return 0;
}
