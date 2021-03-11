typedef struct satck
{
    int* array;
    int size;
    int capacity;
}stack;
//初始化
void stackInit(stack* st)
{
    st->array=(int*)malloc(sizeof(int)*4);
    st->size=0;
    st->capacity=4;
}

//进栈
void stackPush(stack* st,int x)
{
    if(st->size>=st->capacity)
    {
        st->capacity*=2;
        st->array=(int*)realloc(st->array,sizeof(int)*(st->capacity));
    }
    st->array[st->size]=x;
    st->size++;
}

//出栈
void stackPop(stack* st)
{
    st->size--;
}

//获取栈顶元素
int stackTop(stack* st)
{
    return st->array[st->size-1];
}

//获取栈中有效元素个数
int stackSize(stack* st)
{
    return st->size;
}
//判断栈是否为空
int stackEmpty(stack* st)
{
    return st->size==0?1:0;
}

//销毁栈
void stackDestroy(stack* st)
{
    st->size=0;
    st->capacity=0;
    free(st->array);
}


typedef struct {
    stack s1;//s1为进栈栈
    stack s2;////s2为出栈栈
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
    MyQueue* q=(MyQueue*)malloc(sizeof(MyQueue));
    stackInit(&q->s1);
    stackInit(&q->s2);
    return q;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    stackPush(&obj->s1,x);
    
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    if(stackEmpty(&obj->s2))
    {
         while(stackSize(&obj->s1))
        {
            stackPush(&obj->s2,stackTop(&obj->s1));
            stackPop(&obj->s1);
         }
    }
   
    int top=stackTop(&obj->s2);
    stackPop(&obj->s2);
    return top;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    
    if(stackEmpty(&obj->s2))
    {
         while(stackSize(&obj->s1))
        {
            stackPush(&obj->s2,stackTop(&obj->s1));
            stackPop(&obj->s1);
         }
    }
   
    int top=stackTop(&obj->s2);
    return top;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    return stackEmpty(&obj->s1)&&stackEmpty(&obj->s2);
}

void myQueueFree(MyQueue* obj) {
    stackDestroy(&obj->s1);
    stackDestroy(&obj->s2);
    free(obj);

}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);
 
 * int param_2 = myQueuePop(obj);
 
 * int param_3 = myQueuePeek(obj);
 
 * bool param_4 = myQueueEmpty(obj);
 
 * myQueueFree(obj);
*/