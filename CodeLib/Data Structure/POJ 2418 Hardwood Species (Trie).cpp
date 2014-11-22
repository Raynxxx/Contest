/*
** POJ 2418 Hardwood Species
** Created by Rayn @@ 2014/05/01
** Trie��
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
const int ChildSize = 256;

int tot;

struct TrieNode {
    int val;  /* ���ڼ�¼���ʳ��ֵĴ���*/
    TrieNode *child[ChildSize]; /* ��֧�ڵ�ĺ���ָ�� */
};
TrieNode *InitTrie()
{
    return (TrieNode*)calloc(1, sizeof(TrieNode));
}
void Insert(TrieNode *root, char *word)
{
    TrieNode *now = root;

    for(char *p=word; *p; p++)
    {
        int v = *p;
        if(now->child[v] == 0)
        {
            now->child[v] = (TrieNode*)calloc(1, sizeof(TrieNode));
        }
        now = now->child[v];
    }
    //�����¼ͳ�Ƶ��ʴ����Ľڵ�
    now->val++;
}
void Search(TrieNode *root)
{
    static char tmp[31];
    static int pos;

    if(root->val)
    {
        tmp[pos] = '\0';
        if(tmp[0])
        {
            printf("%s %.4f\n", tmp, (root->val*100.0)/tot);
        }
    }
    for(int i=0; i<256; ++i)
    {
        if(root->child[i])
        {
            tmp[pos] = i;
            pos++;
            Search(root->child[i]);
            pos--;  //����
        }
    }
}
int main()
{
    char word[31];
    TrieNode *root;

    tot = 0;
    root = InitTrie();
    while(gets(word))
    {
        Insert(root, word);
        tot++;
    }
    Search(root);
	return 0;
}
