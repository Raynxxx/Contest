/*
** ZOJ 3150 Dareda?
** Created by Rayn @@ 2014/08/02
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

int n, m;
vector<string> group_name;
map<string, double> group_prob;
map<string, map<string, map<string, double> > > feature_prob;
/* <grpup_name, <aspect_name, <feature, probability> > > */

void Init()
{
    feature_prob.clear();
    group_name.clear();
    group_prob.clear();
}
int dcmp(double x)
{
    if(fabs(x) < 1e-8)
        return 0;
    return (x < 0)? -1 : 1;
}
void Read()
{
    double prob, p;
    char group[2000], aspect[2000], feat[2000];

    for(int i = 0; i < m; ++i)
    {
        scanf("%s", aspect);
    }
    for(int i = 0; i < n; ++i)
    {
        scanf("%s %lf%%", group, &prob);
        group_name.push_back(group);
        group_prob[group] = prob / 100.0;

        for(int j = 0, cnt; j < m; ++j)
        {
            scanf("%s%d", aspect, &cnt);
            map<string, double> feature;
            while(cnt--)
            {
                scanf("%s %lf%%", feat, &p);
                feature[feat] = p / 100.0;
            }
            feature_prob[group][aspect] = feature;
        }
    }
}
void SplitQuery(char query[], vector<string>& res)
{
    res.clear();
    string tmp;
    int len = strlen(query);
    for(int i = 10; i < len; ++i)
    {
        if(query[i] == '&')
        {
            if(tmp.size())
                res.push_back(tmp);
            tmp = "";
        }
        else
        {
            tmp += query[i];
        }
    }
    if(tmp.size())
        res.push_back(tmp);
}
void SplitCond(const string& cond, string& aspect, string& feat)
{
    int mid = -1;
    for(int i =0; i < (int) cond.size(); ++i) {
        if(cond[i] == '=') {
            mid = i;
            break;
        }
    }
    if(mid != -1) {
        aspect = cond.substr(0, mid);
        feat = cond.substr(mid+1, cond.size()-mid-1);
    }
}
bool Check(const vector<string>& cond)
{
    map<string, string> mp;
    string aspect, feat;
    for(int i = 0; i < (int) cond.size(); ++i)
    {
        SplitCond(cond[i], aspect, feat);
        if(mp.count(aspect) && mp[aspect] != feat) {
            return false;
        }
        mp[aspect] = feat;
    }
    return true;
}
void removeDuplicate(vector<string>& cond)
{
    map<string, string> mp;
    vector<string> res;
    string aspect, feat;
    for(int i = 0; i < (int) cond.size(); ++i)
    {
        SplitCond(cond[i], aspect, feat);
        if(!mp.count(aspect))
            res.push_back(cond[i]);
        mp[aspect] = feat;
    }
    cond = res;
}
double AskFeature(string& group, string& aspect, string& feat)
{
    if(feature_prob[group][aspect].count(feat))
        return feature_prob[group][aspect][feat];
    else
        return 0;
}
double AskGroup(string& group, const vector<string>& cond)
{
    double prob = group_prob[group];
    string aspect, feat;
    for(int i = 0; i < (int) cond.size(); ++i)
    {
        SplitCond(cond[i], aspect, feat);
        prob *= AskFeature(group, aspect, feat);
    }
    return prob;
}
void CalcProb(const vector<string>& cond)
{
    double p2 = 0, res = 0;
    for(int i = 0; i < (int) group_name.size(); ++i)
    {
        p2 += AskGroup(group_name[i], cond);
    }
    printf("<reply ");
    for(int i = 0; i < (int) group_name.size(); ++i)
    {
        double p1 = AskGroup(group_name[i], cond);
        if(dcmp(p1) == 0 || dcmp(p2) == 0)
            res = 0;
        else
            res = p1 / p2 * 100.0;
        printf("%s=%.3f%% ", group_name[i].c_str(), res);
    }
    printf("/>\n");
}
void Work()
{
    int Q;
    char query[5000];
    vector<string> cond;

    scanf("%d", &Q);
    while(Q--)
    {
        scanf("%s", query);
        SplitQuery(query, cond);
        if(!Check(cond))
        {
            printf("<reply ");
            for(int i = 0; i < (int) group_name.size(); ++i)
            {
                printf("%s=0.000%% ", group_name[i].c_str());
            }
            printf("/>\n");
            continue;
        }
        removeDuplicate(cond);
        CalcProb(cond);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        Init();
        Read();
        printf("<answer cid=%d>\n", ++cases);
        Work();
        printf("</answer>\n");
    }
    return 0;
}
