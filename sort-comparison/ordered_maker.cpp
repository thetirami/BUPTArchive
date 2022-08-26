#include<time.h>
#include<iostream>
#include<fstream>


using namespace std;


int main() {
	cout << "How long is the data? 	";
	int len, i;  /*用len来表示数据集长度*/
	ofstream data_in("data.txt", ios::trunc);  /*每次删除并重建数据集*/
	cin >> len;
	for (i = len; i >= 0; i--)
		data_in << i << " ";
	data_in.close(); /*创建数据集完成，保存并退出*/
	return 0;
}
