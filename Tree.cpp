#include <cstdio>
#include <cctype>

#define N 10

typedef struct Node
{
    int data, left, right;
} TreeNode;
TreeNode node[N];
TreeNode Queue[N];          //����ʵ�ֶ���

int first = -1, last = -1;

void Push(TreeNode tn);
TreeNode Pop();
void printLeaves(int root, int n);

int charToInt(char ch);

int main()
{
    int n;
    bool isRoot[N];
    int root;

    scanf("%d\n", &n);
    for (int i = 0; i < n; i++)
        isRoot[i] = 1;
    for (int i = 0; i < n; i++)
    {
        char cLeft, cRight;
        scanf("%c %c", &cLeft, &cRight);
        getchar();      //��ȡ�������Ļس���
        node[i].left = charToInt(cLeft);
        node[i].right = charToInt(cRight);
        node[i].data = i;
        //һ���ڵ�����Ӻ��Һ���һ�����Ǹ��ڵ�
        if (node[i].left != -1)
            isRoot[node[i].left] = 0;
        if (node[i].right != -1)
            isRoot[node[i].right] = 0;
    }
    //�ҵ����ڵ�
    for (int i = 0; i < n; i++)
    {
        if (isRoot[i])
        {
            root = i;
            break;
        }
    }
    printLeaves(root, n);

    return 0;
}

void Push(TreeNode treeNode)
{
    Queue[++last] = treeNode;
}

TreeNode Pop()
{
    return Queue[++first];
}

//����������ڵ㲢��ӡ��Ҷ�ڵ㣺����ʵ��
void printLeaves(int root, int n)
{
    int leaves[N];
    int k = 0;
    Push(node[root]);
    for (int i = 0; i < n; i++)
    {
        TreeNode tn = Pop();
        //���Ӻ��Һ��Ӷ�������ʱ����Ҷ�ڵ��ֵ���浽�����У����ڸ�ʽ����ӡ
        if (tn.left == -1 && tn.right == -1)
            leaves[k++] = tn.data;
        if (tn.left != -1)
            Push(node[tn.left]);
        if (tn.right != -1)
            Push(node[tn.right]);
    }
    for (int i = 0; i < k-1; i++)
        printf("%d ", leaves[i]);
    printf("%d\n", leaves[k-1]);
}

int charToInt(char ch)
{
    if (isdigit(ch))
        return ch - '0';
    else
        return -1;
}
