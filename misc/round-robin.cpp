#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

void show(vector<vector<int> > a,int size)
{
	int i, j;
	cout << "Number before\":\"means the player. After the \":\" means the player's opponent in No.i day.\n";
	cout << "\t";
	for (j = 0; j <= a[0].size() - 2; j++)
		cout << "Day" << j + 1 << "\t";
	cout << endl;
	for (i = 0; i <= size - 1; i++)
	{
		for (j = 0; j <= a[i].size() - 1; j++)
		{
			if (j == 0)
				cout << a[i][j] << ":\t";
			else
				cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void replaceVirtual(vector<vector<int> > &a, int m)
{
	int i, j;
	for (i = 0; i<a.size() - 1; i++)
	{
		for (j = 0; j <= a[0].size() - 1; j++)
		{
			if (a[i][j] == m)
				a[i][j] = 0;
		}
	}
}

void copyeven(vector<vector<int> > &a, int m)
{
	int i, j;
	for (j = 0; j<m; j++)
	{//求第2组的安排
		for (i = 0; i<m; i++)
			a[i + m][j] = a[i][j] + m;
	}
	for (j = m; j<2 * m; j++)//两组间比赛的安排
	{
		for (i = 0; i<m; i++)
			a[i][j] = a[i + m][j - m];//把左下角拷贝到右上角
		for (i = m; i<2 * m; i++)
			a[i][j] = a[i - m][j - m];//把左上角拷贝到右下角
	}
}

void copyodd(vector<vector<int> > &a, int m)
{
	int i, j;
	for (j = 0; j <= m; j++)
	{//求第2组的安排
		for (i = 0; i<m; i++)
		{
			if (a[i][j] != 0)
				a[i + m][j] = a[i][j] + m;
			else
			{//两个队各有一名选手有空
				a[i + m][j] = i + 1;
				a[i][j] = i + m + 1;
			}
		}
	}

	for (i = 0, j = m + 1; j<2 * m; j++)
	{//安排两组选手
		a[i][j] = j + 1;//1号选手的后m-1天的安排
		a[(a[i][j] - 1)][j] = i + 1;//对手后m-1天的安排
	}

	//先安排1号的赛程
	for (i = 1; i<m; i++)
	{//其他选手的后m-1天的安排
		for (j = m + 1; j<2 * m; j++)
		{//向下m+1~2*m循环递增
			a[i][j] = ((a[i - 1][j] + 1) % m == 0) ? a[i - 1][j] + 1 : m + (a[i - 1][j] + 1) % m;//对应组的对手也要做相应的安排
			a[(a[i][j] - 1)][j] = i + 1;
		}
	}
}

void copy(vector<vector<int> > &a, int m)
{
	if (m % 2 == 1)
		copyodd(a, m / 2);
	else
		copyeven(a, m / 2);
}

void tournament(vector<vector<int> > &a, int num)
{
	if (num == 1)
	{
	}
	else
	{
		if (num % 2 == 0)
		{//偶数
			tournament(a, num / 2);
			copy(a, num);
		}
		else
		{//奇数
			tournament(a, num + 1);
			replaceVirtual(a, num + 1);
		}
	}
}

void schedule(vector<vector<int> > &a, int num)
{
	int i;
	for (i = 0; i <= a.size() - 1; i++)
		a[i][0] = i + 1;
	tournament(a, num);
}

int main()
{
	int i, j,size;
	vector<vector<int> > a;
	cout << "Please input the number of players:_\b";
	cin >> size;
	while (size != 0)
	{
		for (i = 0; i <= a.size() - 1; i++)
		{
			if (size % 2 == 0)
			{
				a.resize(size);
				a[i].resize(size);
			}
			else if (size % 2 == 1)
			{
				a.resize(size+1);
				a[i].resize(size + 1);
			}			
		}
		for (i = 0; i <= a.size() - 1; i++)
			for (j = 0; j <= a[i].size() - 1; j++)
				a[i][j] = 0;

		schedule(a, size);
		show(a,size);
		cout << "Please input the number of players(Press 0 to exit):_\b";
		cin >> size;
	}
	system("pause");
	return 0;
}
