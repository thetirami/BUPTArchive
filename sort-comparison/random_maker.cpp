#include<time.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>


using namespace std;


int main() {
	cout << "How long is the data? 	";
	int len, i;  /*用len来表示数据集长度*/
	int x;
    srand((unsigned)time(NULL)); //srand(3)
	ofstream data_in("data.txt", ios::trunc);/*每次删除并重建数据集*/
	cin >> len;
	for (i = 1; i <= len; i++) {
		x = rand() % len;
		data_in << x << " ";
	}
	data_in.close();/*创建数据集完成，保存并退出*/
	return 0;
}
