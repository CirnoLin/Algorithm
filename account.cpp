#define MAXACCOUNTLENGTH 10
#define MINACCOUNTLENGTH 4
#define MAXPASSLENGTH 16
#define MINPASSLENGTH 6
#define MAXTABLESIZE 1000000
#define MAXD 5
#define KEYLENGTH 16
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef char ElementType[KEYLENGTH + 1];
typedef int  Index;
typedef int CountType;
/******************* ������Ķ��� *************************/
typedef struct LNode * PtrToLNode;
struct LNode{
    ElementType Account; /* �Ƚ�ACCOUNT */
    ElementType  PassWord;
    struct LNode * Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******************** ɢ�б����� ************************/
typedef struct TblNode * HashTable;
struct TblNode{     /* ɢ�б��㶨�� */
    int TableSize;  /* �����󳤶� */
    List Heads;     /* ָ������ͷ�������� */
};
int NextPrime (int N);
Index Hash(ElementType Key, int TableSize);
 
/******************** ��ϣ��Ĵ��� ************************/
HashTable CreateTable( int TableSize){
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶������� */
    H->TableSize = NextPrime(TableSize);
    
    /* ���·�������ͷ������� */
    H->Heads = (List)malloc(sizeof(struct LNode) * H->TableSize);
    /* ��ʼ����ͷ��� */
    for( i = 0; i < H->TableSize ; i++){
        H->Heads[i].PassWord[0] = '\0';
        H->Heads[i].Account[0] = '\0';
        H->Heads[i].Next = NULL;
    }
    return H;
}
/******************** ������ϣ���Ѱ�� ************************/
Position Find(HashTable H, ElementType Key){
    Position p;
    Index Pos;
    Pos = Hash (Key, H->TableSize);
    p = H->Heads[Pos].Next;
    while( p && strcmp(p->Account, Key)){
        p = p->Next;
    }
    return  p;  /* ��ʱP����ָ���ҵ��Ľ�㣬����ΪNULL */
}
/******************** ��ϣ��Ĳ��� ************************/
bool Insert(HashTable H, PtrToLNode NewNode){
    Position p, NewCell;
    Index Pos;
    
    p = Find(H, NewNode->Account);
    if(!p){ /* һ�㶼���뵽ͷ�ڵ��� */
        printf("New: OK\n");
        /* ���� */
        NewCell = (PtrToLNode)malloc(sizeof(struct LNode));
        strcpy(NewCell->Account, NewNode->Account);
        strcpy(NewCell->PassWord, NewNode->PassWord);
        Pos = Hash(NewNode->Account, H->TableSize);
        
        /* ���� */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }else{
        /* �Ѵ��� */
        printf("ERROR: Exist\n");
        return false; /* ALREADY EXIST!!! */
    }
}
/******************** Destroy *************************/
void DestroyTable ( HashTable H ){
    int i;
    Position p, tmp;
    
    for( i = 0; i < H->TableSize; i++){
        p = H->Heads[i].Next;
        while (p) {
            tmp = p->Next;
            free(p);
            p = tmp;
        }
    }
    free( H->Heads );
    free( H );
}
/******************** Ѱ�� Next Prime *************************/
int NextPrime (int N){
    int i, p = (N % 2) ? N + 2 : N + 1;  /*�Ӵ���N����һ��������ʼ */
    
    while( p <= MAXTABLESIZE){
        for( i = (int) sqrt(p); i > 2; i--){
            if( !(p%i) )
                break;   /* ˵��P�������� */
        }
        if ( i == 2 )  break; /* for����������˵��p������ */
        else  p += 2;
    }
    return p;
}
/******************** Ѱ�� Next Prime ************************/
Index Hash(ElementType Key, int TableSize){
    int NewKey = atoi(Key + MINACCOUNTLENGTH);
    return NewKey % TableSize;
}
/******************** ������ ************************/
int main(int argc, const char * argv[]) {
    int N, i;
    ElementType Acount, Password;
    HashTable H;
    char op = '\0';
    
    scanf("%d\n", &N);
    H = CreateTable( N * 2);
    for( i = 0; i < N; i++){
        scanf("%c ", & op);
        if( op == 'L'){
            scanf("%s %s\n", Acount, Password);
            
            PtrToLNode p =  Find(H, Acount);
            if( p && strcmp(p->PassWord, Password) == 0){        /* �ҵ������������ */
                printf("Login: OK\n");
            }else if(p && strcmp(p->PassWord, Password) != 0 ){  /* �ҵ��˵����벻�� */
                printf("ERROR: Wrong PW\n");
            }else{                                                /* û�ҵ� */
                printf("ERROR: Not Exist\n");
            }
            
        }
        if( op == 'N'){
            scanf("%s %s\n", Acount, Password);
            //test(Accout, Password);  ���������д���Ե�
            
            PtrToLNode NewCell = malloc(sizeof(struct LNode));
            strcpy(NewCell->Account, Acount);
            strcpy(NewCell->PassWord, Password);
            NewCell->Next = NULL;
            Insert(H, NewCell);
            free(NewCell);
        }
    }
    
    DestroyTable( H );
    return 0;
}
/******************** TEST ************************/
void test(ElementType Accout, ElementType Password){
    printf("%s %s\n", Accout, Password);
    printf("Length of Account is %d, Length of Password is %d", strlen(Accout), strlen(Password));
}
