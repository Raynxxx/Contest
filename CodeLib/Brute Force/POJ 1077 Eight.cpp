/*
** POJ 1077 Eight
** Created by Rayn @@ 2014/05/22
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>
using namespace std;
const int MAX = 400000;

int nGoalStatus;
bitset<387420498> Flag;
char szRes[MAX], szMove[MAX];
char Dir[] = "udrl";
int Pre[MAX], Queue[MAX];
int Head, Tail;

int NineToTen(char *s)  //九进制字符串转化为十进制数字
{
    int res = 0;
    for(int i=0; s[i]; ++i)
    {
        res = res * 9 + s[i] - '0';
    }
    //printf("%d\n", res);
    return res;
}
int TenToNine(int n, char *s)   //十进制数字转化为九进制字符串
{
    int ZeroPos, nBase = 1;
    while (nBase <= n)
        nBase *= 9;

    nBase /= 9;
    int j = 0;
    do {
        s[j] = n/nBase + '0';
        if (s[j] == '0')
            ZeroPos = j;
        j++;
        n %= nBase;
        nBase /= 9;
    } while(nBase >= 1);
    s[j] = '\0';

    if(j < 9)
    {
        for(int i = j+1; i > 0; --i)
        {
            s[i] = s[i-1];
        }
        s[0] = '0';
        return 0;
    }
    return ZeroPos;
}
int NewStatus(int nStatus, char cMove)
{
    char tmp[20];
    int ZeroPos = TenToNine(nStatus, tmp);  //返回空格的位置
    switch(cMove)
    {
        case 'u':
            if (ZeroPos - 3 < 0) return -1; //空格在第一行
            else {
                tmp[ZeroPos] = tmp[ZeroPos-3];
                tmp[ZeroPos-3] = '0';
            }
            break;
        case 'd':
            if (ZeroPos + 3 > 8) return -1; //空格在第三行
            else {
                tmp[ZeroPos] = tmp[ZeroPos+3];
                tmp[ZeroPos+3] = '0';
            }
            break;
        case 'l':
            if (ZeroPos % 3 == 0) return -1; //空格在第一列
            else {
                tmp[ZeroPos] = tmp[ZeroPos-1];
                tmp[ZeroPos-1] = '0';
            }
            break;
        case 'r':
            if (ZeroPos % 3 == 2) return -1; //空格在第三列
            else {
                tmp[ZeroPos] = tmp[ZeroPos+1];
                tmp[ZeroPos+1] = '0';
            }
            break;
    }
    return NineToTen(tmp);
}
bool BFS(int nStatus)
{
    int nNewStatus;
    Head = Tail = 0;
    Queue[Head] = nStatus;
    Tail++;
    while (Head < Tail)
    {
        nStatus = Queue[Head];
        if(nStatus == nGoalStatus)
            return true;
        for(int i=0; i<4; ++i)
        {
            nNewStatus = NewStatus(nStatus, Dir[i]);
            if(nNewStatus == -1)
                continue;
            if(Flag[nNewStatus])
                continue;
            Flag.set(nNewStatus, true);
            Queue[Tail] = nNewStatus;
            Pre[Tail] = Head;
            szMove[Tail] = Dir[i];
            Tail++;
        }
        Head++;
    }
    return false;
}
int main()
{
    nGoalStatus = NineToTen("123456780");
    Flag.reset();
    char Line1[50], Line2[20];
    cin.getline(Line1, 40);
    int i, j;
    for(i=0, j=0; Line1[i]; ++i)
    {
        if(Line1[i] != ' ')
        {
            if(Line1[i] == 'x')
                Line2[j++] = '0';
            else
                Line2[j++] = Line1[i];
        }
    }
    Line2[j] = '\0';
    if( BFS(NineToTen(Line2)) )
    {
        int nMove = 0;
        int nPos = Head;
        do {
            szRes[nMove++] = szMove[nPos];
            nPos = Pre[nPos];
        } while(nPos);
        for(int i = nMove-1; i >= 0; --i)
        {
            cout << szRes[i];
        }
    }
    else
    {
        cout << "unsolvable" << endl;
    }
    return 0;
}
