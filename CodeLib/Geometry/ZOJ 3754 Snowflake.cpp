/*
** ZOJ 3754 Snowflake
** Created by Rayn @@ 2014/08/12
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const int SIZE = 200;
const int MOD = 100000;

struct BigNum
{
    int v[SIZE], len;
    void Init() {
        memset(v, 0, sizeof(v));
        len = 1;
    }
    BigNum setTo(int x) {
        BigNum ret;
        ret.Init();
        ret.v[0] = x;
        return ret;
    }

    BigNum add(BigNum x) {
        BigNum ret;
        int c = 0;
        ret.len = len; memcpy(ret.v, v, sizeof(v));
        if (x.len > ret.len) ret.len = x.len;
        for (int i = 0; i < ret.len; ++ i) {
            ret.v[i] += x.v[i] + c;
            c = ret.v[i] / MOD;
            ret.v[i] %= MOD;
        }
        if (c) ret.v[ret.len ++] = c;
        return ret;
    }

    BigNum add(int x) {
        BigNum ret;
        ret.len = len; memcpy(ret.v, v, sizeof(v));
        ret.v[0] += x;
        for (int i = 0; i < ret.len; ++ i) {
            ret.v[i+1] += ret.v[i] / MOD;
            ret.v[i] %= MOD;
        }
        if (ret.v[ret.len]) ret.len ++;
        return ret;
    }

    int compareTo(BigNum x) {
        if (len > x.len) return 1;
        if (len < x.len) return -1;
        for (int i = len - 1; i >= 0; -- i) {
            if (v[i] > x.v[i]) return 1;
            if (v[i] < x.v[i]) return -1;
        }
        return 0;
    }

    BigNum multiply(int x) {
        BigNum ret;
        int c = 0;
        ret.len = len; memcpy(ret.v, v, sizeof(v));
        for (int i = 0; i < ret.len; ++ i) {
            ret.v[i] = ret.v[i] * x + c;
            c = ret.v[i] / MOD;
            ret.v[i] %= MOD;
        }
        while (c) {
            ret.v[ret.len ++] = c % MOD;
            c /= MOD;
        }
        return ret;
    }

    BigNum subtract(BigNum x) {
        BigNum ret; ret.Init();
        memcpy(ret.v, v, sizeof(v));
        ret.len = len;
        for (int i = 0; i < x.len; ++ i) {
            if (ret.v[i] < x.v[i]) ret.v[i + 1] --, ret.v[i] += MOD;
            ret.v[i] = ret.v[i] - x.v[i];
        }
        while (ret.len && ret.v[ret.len - 1] == 0) ret.len --;
        return ret;
    }

    void print() {
        printf("%d", v[len - 1]);
        for (int i = len - 2; i >= 0; i --) {
            if (v[i] < 10000) putchar('0');
            if (v[i] < 1000) putchar('0');
            if (v[i] < 100) putchar('0');
            if (v[i] < 10) putchar('0');
            printf("%d", v[i]);
        }
        puts("");
    }

    string toString() {
        string st;
        st.clear();
        for (int i = len - 1; i >= 0; -- i) {
            if (i != len - 1) {
                if (v[i] < 10000) st += '0';
                if (v[i] < 1000) st += '0';
                if (v[i] < 100) st += '0';
                if (v[i] < 10) st += '0';
            }
            string tmp; tmp.clear();
            int n = v[i];
            do {
                char c = n % 10 + '0';
                tmp = c + tmp;
                n /= 10;
            } while (n);
            st += tmp;
        }
        return st;
    }
};

BigNum Left, Right, Total;
BigNum seg[2][3][8][2];
BigNum t[1600], p[1600];
int sum[2][3];
int x, d;

void add_seg(BigNum seg[8][2], int &n, BigNum x, BigNum cnt)
{
    for (int i = 0; i < n; ++ i) {
        if (seg[i][0].compareTo(x) == 0) {
            seg[i][1] = seg[i][1].add(cnt);
            return;
        }
    }
    seg[n][0] = x;
    seg[n ++][1] = cnt;
}

void percent(string st, int digit)
{
    BigNum ans; ans.len = 0;
    memset(ans.v, 0, sizeof(ans.v));
    for (int i = digit + 99; i >= digit; i -= 5) {
        ans.v[ans.len] += (st[i] - '0') * 1;
        ans.v[ans.len] += (st[i - 1] - '0') * 10;
        ans.v[ans.len] += (st[i - 2] - '0') * 100;
        ans.v[ans.len] += (st[i - 3] - '0') * 1000;
        ans.v[ans.len] += (st[i - 4] - '0') * 10000;
        ans.len++;
    }
    for (int i = 0; i < digit; ++ i) {
        ans.v[ans.len] = ans.v[ans.len] * 10 + (st[i] - '0');
    }
    ans.len ++;
    if (st[digit + 100] >= '5') ans = ans.add(1);
    st = ans.toString();
    for (int i = 0; i < digit; ++ i) {
        cout << st[i];
    }
    cout << ".";
    for (int i = digit; i < digit + 100; ++ i) {
        cout << st[i];
    }
    cout << "%" << endl;
}

void solve() {
    int n = 0, digit = 0;
    if (Left.compareTo(Total) == 0) {
        digit = 3;
    } else if (Left.multiply(10).compareTo(Total) >= 0) {
        digit = 2;
    } else {
        digit = 1;
    }
    for (int i = 0; i < 40; ++i) {
        Left = Left.multiply(1000);
    }
    p[0] = p[0].setTo(1);
    t[0] = Total;
    while (t[n].compareTo(Left) < 0) {
        n++;
        t[n] = t[n - 1].multiply(2);
        p[n] = p[n - 1].multiply(2);
    }
    BigNum ans = p[n], ret = t[n].subtract(Left);
    for (int i = n - 1; i >= 0; --i) {
        if (ret.compareTo(t[i]) >= 0) {
            ret = ret.subtract(t[i]);
            ans = ans.subtract(p[i]);
        }
    }
    percent(ans.toString(), digit);
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while (scanf("%d/%d", &x, &d) != EOF)
    {
        BigNum tmp, border;
        int s = 0, t = 1;
        x = 2 * (x * 2 + d);
        d <<= 2;
        if (x == 0) {
            printf("0.");
            for (int i = 0; i < 100; ++ i) printf("0");
            printf("%%\n");
            continue;
        }
        border = border.setTo(x);
        Right = Right.setTo(0);
        Left = Left.setTo(0);
        Total = Total.setTo(3);
        memset(sum[0], 0, sizeof(sum[0]));
        add_seg(seg[s][0], sum[s][0], tmp.setTo(0), tmp.setTo(1));
        add_seg(seg[s][1], sum[s][1], tmp.setTo(d/2), tmp.setTo(1));
        add_seg(seg[s][2], sum[s][2], tmp.setTo(0), tmp.setTo(1));
        for (int turn = 0; turn < 300; ++turn)
        {
            memset(sum[t], 0, sizeof(sum[t]));
            for (int type = 0; type < 3; ++ type)
            {
                for (int i = 0; i < sum[s][type]; ++i)
                {
                    BigNum pos = seg[s][type][i][0];
                    BigNum cnt = seg[s][type][i][1];
                    if (pos.compareTo(border) >= 0) {
                        Right = Right.add(cnt);
                        continue;
                    }
                    if (type == 0 && pos.add(d).compareTo(border) <= 0) {
                        Left = Left.add(cnt);
                        continue;
                    }
                    if (type > 0 && pos.add(d/2).compareTo(border) <= 0) {
                        Left = Left.add(cnt);
                        continue;
                    }
                    pos = pos.multiply(3);
                    switch (type) {
                        case 0:
                            add_seg(seg[t][0], sum[t][0], pos, cnt);
                            add_seg(seg[t][1], sum[t][1], pos.add(d + d/2), cnt);
                            add_seg(seg[t][2], sum[t][2], pos.add(d), cnt);
                            add_seg(seg[t][0], sum[t][0], pos.add(d*2), cnt);
                            break;
                        case 1:
                            add_seg(seg[t][1], sum[t][1], pos, cnt);
                            add_seg(seg[t][0], sum[t][0], pos.add(d/2), cnt);
                            add_seg(seg[t][1], sum[t][1], pos.add(d), cnt.multiply(2));
                            break;
                        case 2:
                            add_seg(seg[t][2], sum[t][2], pos, cnt.multiply(2));
                            add_seg(seg[t][0], sum[t][0], pos, cnt);
                            add_seg(seg[t][2], sum[t][2], pos.add(d), cnt);
                            break;
                    }
                }
            }
            if (sum[t][0] + sum[t][1] + sum[t][2] == 0)
                break;
            border = border.multiply(3);
            Left = Left.multiply(4);
            Right = Right.multiply(4);
            Total = Total.multiply(4);
            swap(s, t);
        }
        solve();
    }
    return 0;
}
