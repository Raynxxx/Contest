/*
** ZOJ 3544 Draw a Mess
** Created by Rayn @@ 2014/09/16
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define sqr(x) ((x)*(x))
const int MAXN = 205;
const int MAXM = 50010;

struct Shape
{
    int type;
    vector<int> args;
    Shape() {}
    Shape(int type): type(type) {
        args.clear();
    }
};
struct UnionSet
{
    int pa[MAXM];
    bool cover[MAXM];

    void Init(int n) {
        memset(cover, false, sizeof(cover));
        for(int i = 0; i <= n; ++i) {
            pa[i] = i;
        }
    }
    int FindSet(int x) {
        if(x != pa[x])
            pa[x] = FindSet(pa[x]);
        return pa[x];
    }
    int Gao(int l, int r)
    {
        int left, right, ret = 0;
        left = FindSet(l);
        for(int k = r; k >= l; k = right - 1) {
            right = FindSet(k);
            if(!cover[right]) {
                ret++;
                cover[right] = true;
            }
            if(right != left) {
                pa[right] = left;
            }
        }
        return ret;
    }
};

Shape draw[MAXM];
UnionSet us[MAXN];
int res[15];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, m, q;
    while(scanf("%d%d%d", &n, &m, &q) != EOF)
    {
        for(int i = 0; i < q; ++i) {
            char shape[15];
            scanf("%s", shape);
            if(shape[0] == 'C') {
                draw[i] = Shape(1);
                for(int j = 0, x; j < 4; ++j) {
                    scanf("%d", &x);
                    draw[i].args.push_back(x);
                }
            } else if(shape[0] == 'D') {
                draw[i] = Shape(2);
                for(int j = 0, x; j < 4; ++j) {
                    scanf("%d", &x);
                    draw[i].args.push_back(x);
                }
            } else if(shape[0] == 'R') {
                draw[i] = Shape(3);
                for(int j = 0, x; j < 5; ++j) {
                    scanf("%d", &x);
                    draw[i].args.push_back(x);
                }
            } else if(shape[0] == 'T') {
                draw[i] = Shape(4);
                for(int j = 0, x; j < 4; ++j) {
                    scanf("%d", &x);
                    draw[i].args.push_back(x);
                }
            }
        }
        memset(res, 0, sizeof(res));
        for(int i = 1; i <= n; ++i) {
            us[i].Init(m);
        }
        for(int j = q-1; j >= 0; --j) {
            vector<int> args(draw[j].args);
            int type = draw[j].type;
            int xc = ++args[0], yc = ++args[1];
            if(type == 1) {
                int r = args[2], c = args[3];
                for(int i = max(1, xc - r); i <= min(n, xc + r); ++i) {
                    int range = (int)sqrt((double)(sqr(r) - sqr(i-xc)));
                    res[c] += us[i].Gao(max(1, yc - range), min(m, yc + range));
                }
            } else if(type == 2) {
                int r = args[2], c = args[3];
                for(int i = max(1, xc - r); i <= min(n, xc + r); ++i) {
                    int range = r - abs(i - xc);
                    res[c] += us[i].Gao(max(1, yc - range), min(m, yc + range));
                }
            } else if(type == 3) {
                int l = args[2], w = args[3], c = args[4];
                for(int i = xc; i <= min(n, xc + l - 1); ++i) {
                    res[c] += us[i].Gao(yc, min(m, yc + w - 1));
                }
            } else if(type == 4) {
                int w = args[2], c = args[3];
                for(int i = xc; i <= min(n, xc + w / 2); ++i) {
                    int range = (w - 2 * (i - xc)) / 2;
                    res[c] += us[i].Gao(max(1, yc - range), min(m, yc + range));
                }
            }
        }
        for(int i = 1; i <= 9; ++i) {
            printf("%d%c", res[i], (i == 9)? '\n' : ' ');
        }
    }
    return 0;
}
