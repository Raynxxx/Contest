/*  Title :  Black Box
**  main  ��  Ѱ�ҵ�kС ����k�Ǳ䶯�� ADD����󶥶Ѽ���blood,GET��ȡ����kС
**  way : ����С���Ѻʹ󶥶ѣ��󶥶Ѵ�ţ�Ҫ�ҵĵ�kС������k����СԪ�أ����Ϊ��󣬼�Ϊ��kС
**        С���Ѵ������Ԫ�أ���˴����С�ģ���k+1ʱ�Ա���´󶥶�
**        ������updatemin, updatemax:�ֱ���ϵ��¸���С���Ѻʹ󶥶ѣ�������Ԫ�أ���buildmin,buildmax:�ֱ���µ���С���Ѻʹ󶥶ѡ�
**        GET��ֵ��ʾĿǰһ�����˶��ٸ�Ԫ�أ����õ���һ��GET = num,Ȼ����С���������num��Ԫ�أ�Ȼ��build��Ȼ�������������һ��
**        Ȼ��ֱ�build��Ȼ��ȡ���󶥶ѵ�head��Ȼ��build;
*/
#include <stdio.h>
int max_tree[30100],max_k, min_tree[30100],min_k;//�ֱ��Ǵ󶥶Ѻ����ĵ�ǰ����� С���Ѻ����ĵ�ǰ�����

void build_maxtree()
{
    int pos;
    if (max_k == 1) return ;            //���max_k = 1; ֻ��һ��Ԫ�أ�headһ��������
    pos = max_k-1;
    while(pos != 0){
        if ((pos&1)==0){        //��ż��
            if (max_tree[pos]>max_tree[(pos-1)/2]){
                int temp = max_tree[pos];
                max_tree[pos] = max_tree[(pos-1)/2];
                max_tree[(pos-1)/2] = temp;
            }
            pos = (pos-1)/2;
        }
        else{           // ������
            if (max_tree[pos]>max_tree[pos/2]){
                int temp = max_tree[pos];
                max_tree[pos] = max_tree[pos/2];
                max_tree[pos/2] = temp;
            }
            pos = pos/2;
        }
    }
}
void build_mintree()
{
    int pos;
    if (min_k == 1) return ;
    pos = min_k-1;
    while (pos != 0){
        if ((pos&1)==0) {        //ż��
            if (min_tree[pos]<min_tree[(pos-1)/2]){
                int temp = min_tree[pos];
                min_tree[pos] = min_tree[(pos-1)/2];
                min_tree[(pos-1)/2] = temp;
            }
            pos = (pos-1)/2;
        }
        else{       //����
            if (min_tree[pos]<min_tree[pos/2]) {
                int temp = min_tree[pos];
                min_tree[pos] = min_tree[pos/2];
                min_tree[pos/2] = temp;
            }
            pos = pos/2;
        }
    }
}
void update_maxtree()
{
	int pos = 0, son;
	if (max_k<=1) return;
    while(pos*2+1 < max_k){       //pos*2+1��ʾ�����Ҫ����
        if (pos*2+1==max_k-1 || max_tree[pos*2+1]>max_tree[pos*2+2]){       //����ӵ�pos����max_k-1��ʾû���Ҷ���,|| ����Ӵ����Ҷ���
            son = pos*2+1;
        }
        else son = pos*2+2;
        if (max_tree[pos]<max_tree[son]){
            int temp = max_tree[pos];
            max_tree[pos] = max_tree[son];
            max_tree[son] = temp;
        }
        pos = son;
    }
}
void update_mintree()
{
	int pos = 0, son;
	if (min_k<=1) return;
    while(pos*2+1 < min_k){       //pos*2+1��ʾ�����Ҫ����
        if (pos*2+1==min_k-1 || min_tree[pos*2+1]<min_tree[pos*2+2]){       //����ӵ�pos����max_k-1��ʾû���Ҷ���,|| �����С���Ҷ���
            son = pos*2+1;
        }
        else son = pos*2+2;
        if (min_tree[pos]>min_tree[son]){
            int temp = min_tree[pos];
            min_tree[pos] = min_tree[son];
            min_tree[son] = temp;
        }
        pos = son;
    }
}
int main()
{
    int M, N, i, j, elem[30100],cur,num;
    scanf("%d%d", &M, &N);
    for (i = 0; i < M; i++){
        scanf("%d", &elem[i]);
    }
    max_k = min_k = cur = 0;    //��ǰ����㶼Ϊ0��cur Ϊelem��С�꣬��ʾ��ǰҪȡ����Ԫ�أ�kΪҪ�ҵĵ�KС
    for (i = 0; i < N; i++){
        scanf("%d", &num);
        num = num - max_k- min_k;           //��ʾӦ������������Ӧ��Ҫ����num��Ԫ����
        for (j = 0; j < num; j++){       //��С���������Ԫ��,ʹ������һ������num��Ԫ��
			int temp = elem[cur++];			//�ȴ���temp��
			if (max_k>0 && temp<max_tree[0]){		//��temp�ڴ󶥶ѵ�head�Ƚϣ�ʹ����ڴ󶥶�	max_kд��max_tree�ˣ� ����������
				int a = temp; temp = max_tree[0]; max_tree[0] = a;
				update_maxtree();			//���´󶥶� ��������
			}
			min_tree[min_k++] = temp;		//��temp��ֵѹ��С����
			build_mintree();				//�������ϱ���С����
		}
		max_tree[max_k++] = min_tree[0];
		min_tree[0] = min_tree[--min_k];
		build_maxtree();
		update_mintree();
        printf("%d\n", max_tree[0]);
    }
    return 0;
}

