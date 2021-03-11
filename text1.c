typedef struct QueueNode
{
    int data;
    struct QueueNode* next;
}QueueNode;

typedef struct Queue
{
    struct QueueNode* Front;
    struct QueueNode* Back;
}Queue;

//初始化
void QueueInit(Queue* q)
{
   q->Back = q->Front=NULL;
}

//队列进数据
void QueuePush(Queue* q,int x)
{
    QueueNode* newnode=(QueueNode*)malloc(sizeof(QueueNode));
    newnode->data=x;
    newnode->next=NULL;
    if(q->Back==NULL)
    {
        q->Back=newnode;
        q->Front=newnode;
    }
    else
    {
        q->Back->next=newnode;
        q->Back=newnode;
    }
}

//获取队头元素
int QueueTop(Queue* q)
{
    return q->Front->data;
}

//获取队尾元素
int QueueBack(Queue* q)
{
    return q->Back->data;
}

//出队列
void QueuePop(Queue* q)
{
    QueueNode* cur=q->Front->next;
    free(q->Front);
    q->Front=cur;
}

//队列个数
int QueueSize(Queue* q)
{
    int count=0;
    QueueNode*cur=q->Front;
    while(cur)
    {
        count++;
        cur=cur->next;
    }
    return count;
}

//队列是否为空
int QueueEmpty(Queue* q)
{
    return q->Front==NULL?1:0;
}

//销毁
void QueueDestroy(Queue* q)
{
    QueueNode* cur=q->Front;
    while(cur)
    {
        QueueNode* next=cur->next;
        free(cur);
        cur=next;
    }
    q->Front=q->Back=NULL;
}

typedef struct {
    Queue q1;
    Queue q2;
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
    MyStack* st=(MyStack*)malloc(sizeof(MyStack));
    QueueInit(&st->q1);
    QueueInit(&st->q2);
    return st;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
    
    
    if(QueueEmpty(&obj->q1))
    {
        QueuePush(&obj->q2,x);  
    }
    else
    {
        QueuePush(&obj->q1,x);
    }
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
    Queue* qempty=&obj->q1;
    Queue* qnoempty=&obj->q2;
    if(!QueueEmpty(&obj->q1))
    {
        qempty=&obj->q2;
        qnoempty=&obj->q1;
    }
    while(QueueSize(qnoempty)>1)
    {
        QueuePush(qempty,QueueTop(qnoempty));
        QueuePop(qnoempty);
    }
    int top=QueueTop(qnoempty);
    QueuePop(qnoempty);
    return top;
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
     
    if(QueueEmpty(&obj->q1))
    {
       return QueueBack(&obj->q2);  
    }
    else
    {
       return QueueBack(&obj->q1);
    }
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
    return QueueEmpty(&obj->q1)&&QueueEmpty(&obj->q2);
}

void myStackFree(MyStack* obj) {
    QueueDestroy(&obj->q1);
    QueueDestroy(&obj->q2);
    free(obj);

}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/