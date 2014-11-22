/*  Title :  Black Box
**  main  ：  寻找第k小 其中k是变动的 ADD：向大顶堆加入blood,GET：取出第k小
**  way : 建立小顶堆和大顶堆，大顶堆存放（要找的第k小，既有k个最小元素）最顶端为最大，即为第k小
**        小顶堆存放其余元素，最顶端存放最小的，当k+1时以便更新大顶堆
**        函数：updatemin, updatemax:分别从上到下更新小顶堆和大顶堆，（放入元素），buildmin,buildmax:分别从下到上小顶堆和大顶堆。
**        GET的值表示目前一共放了多少个元素，先拿到第一个GET = num,然后往小顶堆里面放num个元素，然后build，然后往打顶里面放入一个
**        然后分别build，然后取出大顶堆的head，然后build;
*/
#include <stdio.h>
int max_tree[30100],max_k, min_tree[30100],min_k;//分别是大顶堆和他的当前最大结点 小顶堆和他的当前最大结点

void build_maxtree()
{
    int pos;
    if (max_k == 1) return ;            //如果max_k = 1; 只有一个元素，head一定是最大的
    pos = max_k-1;
    while(pos != 0){
        if ((pos&1)==0){        //是偶数
            if (max_tree[pos]>max_tree[(pos-1)/2]){
                int temp = max_tree[pos];
                max_tree[pos] = max_tree[(pos-1)/2];
                max_tree[(pos-1)/2] = temp;
            }
            pos = (pos-1)/2;
        }
        else{           // 是奇数
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
        if ((pos&1)==0) {        //偶数
            if (min_tree[pos]<min_tree[(pos-1)/2]){
                int temp = min_tree[pos];
                min_tree[pos] = min_tree[(pos-1)/2];
                min_tree[(pos-1)/2] = temp;
            }
            pos = (pos-1)/2;
        }
        else{       //奇数
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
    while(pos*2+1 < max_k){       //pos*2+1表示左二子要存在
        if (pos*2+1==max_k-1 || max_tree[pos*2+1]>max_tree[pos*2+2]){       //左二子的pos等于max_k-1表示没有右儿子,|| 左二子大于右儿子
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
    while(pos*2+1 < min_k){       //pos*2+1表示左二子要存在
        if (pos*2+1==min_k-1 || min_tree[pos*2+1]<min_tree[pos*2+2]){       //左二子的pos等于max_k-1表示没有右儿子,|| 左二子小于右儿子
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
    max_k = min_k = cur = 0;    //当前最大结点都为0，cur 为elem的小标，表示当前要取出的元素，k为要找的第K小
    for (i = 0; i < N; i++){
        scanf("%d", &num);
        num = num - max_k- min_k;           //表示应该两颗树里面应该要填满num个元素了
        for (j = 0; j < num; j++){       //往小顶堆里面放元素,使两棵树一共能有num个元素
			int temp = elem[cur++];			//先存在temp里
			if (max_k>0 && temp<max_tree[0]){		//将temp于大顶堆的head比较，使其大于大顶堆	max_k写成max_tree了， 哎。。。。
				int a = temp; temp = max_tree[0]; max_tree[0] = a;
				update_maxtree();			//更新大顶堆 由上至下
			}
			min_tree[min_k++] = temp;		//将temp的值压入小顶堆
			build_mintree();				//又下至上便利小顶堆
		}
		max_tree[max_k++] = min_tree[0];
		min_tree[0] = min_tree[--min_k];
		build_maxtree();
		update_mintree();
        printf("%d\n", max_tree[0]);
    }
    return 0;
}

