/*
** POJ 2109 Power of Cryptography
** Created by Rayn @@ 2014/3/23
** ��ѧ
** ���ڲ�֪��double����G++������,����%lf��д������%f
*/
#include <cstdio>
#include <cmath>

int main()
{
    double n, p;

    while(scanf("%lf%lf", &n, &p) != EOF)
    {
        printf("%.0f\n", pow(p, 1.0/n));   //�ټ���һ��\n�����˲��밡
    }
    return 0;
}
