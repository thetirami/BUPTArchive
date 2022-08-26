#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <windows.h>

using namespace std;
const int MAX_BUF = 1024; 	//最大缓冲区大小
const int MAX_REQ = 20;   	//最大请求数
const int P = 1;           	//生产者
const int C = 0;           	//消费者

int BUFFER_SIZE;           	//缓冲区大小，即用户设定的仓库容量
int Pro_no;                	//生产的产品号，从1开始
int in;                     //缓冲区里产品的下界
int out;                    //缓冲区里产品的上界
int buffer[MAX_BUF];     	//用数组模拟循环队列的缓冲区
int req_num;               	//对仓库的操作请求数
struct request{
    int p_c;               	//请求者类型
	int ti;                	//请求时间,单位ms
} req[MAX_REQ];				//请求序列

//定义三个信号量
HANDLE mutex;             	//用于进程对仓库的互斥操作
HANDLE full_sema;         	//当仓库满时生产者必须等待
HANDLE empty_sema;        	//当仓库空时消费者必须等待
HANDLE thread[MAX_REQ];   	//各线程的handle
DWORD pro_id[MAX_REQ];    	//生产者线程的标识符
DWORD con_id[MAX_REQ];    	//消费者线程的标识符

//对请求按时间排序的比较函数
bool cmp(request a, request b) { return a.ti < b.ti; }
/*初始化函数*/
void initial() {
    Pro_no = 1;
    in=out=0;
    memset(buffer, 0, sizeof(buffer));
    printf("Please input the size of storage:    ");  // 读入仓库大小，即缓冲区大小
    scanf("%d", &BUFFER_SIZE);
    printf("Please input the number of request:  ");  // 读入仓库操作请求个数
    scanf("%d", &req_num);
    printf("Please input the request type(P or C) and occur time(eg:P 4):\n");
    //读入各个请求的类型和时间
	int i;
    char ch[3];
    for (i = 0; i < req_num; i++) {
        printf("The No.%2d request:   ", i);
        scanf("%s %d", ch, &req[i].ti);
        if (ch[0] == 'P')
            req[i].p_c = P;
        else
            req[i].p_c = C;
    }
    //将请求按时间轴排序
    sort(req, req + req_num, cmp);
}


/*****生产者线程****/
DWORD WINAPI producer(LPVOID lpPara) {
    WaitForSingleObject(full_sema, INFINITE); //等待空位
	WaitForSingleObject(mutex, INFINITE);     //对仓库的操作权

    //̸跳过生产过程
	//开始放产品进入仓库
    printf("\nProducer %d put product %d in now.\n", (long long)lpPara, Pro_no);
    buffer[in] = Pro_no++;
    in = (in + 1) % BUFFER_SIZE;

    Sleep(5);
    printf("Producer %d put product success.\n\n", (long long)lpPara);

    ReleaseMutex(mutex);                      //释放仓库操作权
    ReleaseSemaphore(empty_sema, 1, NULL);    //非空位加一
    return 0;
}


/****消费者线程****/
DWORD WINAPI consumer(LPVOID lpPara) {
    WaitForSingleObject(empty_sema, INFINITE);  //等待非空位
    WaitForSingleObject(mutex, INFINITE);       //对仓库的操作权
    //开始从仓库取出产品
    printf("\nConsumer %d take product %d out now.\n", (long long)lpPara, buffer[out]);
    buffer[out] = 0;
    out = (out + 1) % BUFFER_SIZE;

    Sleep(5);
    printf("Consumer %d take product success.\n\n", (long long)lpPara);

    //跳过消费过程
    ReleaseMutex(mutex);                         //释放对仓库的操作权
    ReleaseSemaphore(full_sema, 1, NULL);     //空位加一
    return 0;
}


int main() {
    initial();
    // 创建各个互斥信号
    mutex = CreateMutex(NULL, false, NULL);
    full_sema = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    empty_sema = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

	int pre = 0; // 上一个请求的时间
    for (int i = 0; i < req_num; i++) {
        if(req[i].p_c == P) {
            // 创建生产者线程
            thread[i] = CreateThread(NULL, 0, producer, (LPVOID)i, 0, &pro_id[i]);
            if (thread[i] == NULL)
                return -1;
            printf("\nRequest at %d: Producer %d want to put a product in storage.\n", req[i].ti, i);
        } else {
            // 创建消费者线程
            thread[i] = CreateThread(NULL, 0, consumer, (LPVOID)i, 0, &con_id[i]);
            if (thread[i] == NULL)
                return -1;
            printf("\nRequest at %d: Consumer %d want to get a product out storage.\n", req[i].ti, i);
        }
        Sleep(req[i].ti - pre); // 模拟时间
		pre = req[i].ti;
    }
    // 等待所有线程结束或超时，返回请求答复结果
    int nIndex = WaitForMultipleObjects(req_num, thread, TRUE, 500);
    if (nIndex == WAIT_TIMEOUT)  // 超时500毫秒
		printf("\nSome request can't be satisfied.\n");
    else
        printf("\nAll request are satisfy.\n");
    // 销毁线程和信号量，防止线程的内存泄露
    for(int i = 0; i < req_num; i++)
		CloseHandle(thread[i]);
    CloseHandle(mutex);
    CloseHandle(full_sema);
    CloseHandle(empty_sema);

    system("pause");
    return 0;
}
