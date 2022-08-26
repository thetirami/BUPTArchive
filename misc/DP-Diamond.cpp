#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<string>

#define DATA_LENGTH 100000//数据集长度

using namespace std;

clock_t start, stop;
double duration;

int more(int a, int b)
{
	return a>b ? a : b;
}

int MaxGet(vector<vector<int> > a,
		   vector<vector<int> > &max,
		   int max_x, int max_y, int height)
{
	if (height == 1)
		return a[0][0];
	else
	{
		if (max_y == 0)
			return MaxGet(a, max, max_x - 1, max_y, height - 1) 
						+ a[max_x][max_y];
		else if (max_y == height - 1)
			return MaxGet(a, max, max_x - 1, max_y - 1, height - 1) 
						+ a[max_x][max_y];
		else
			return more(MaxGet(a, max, max_x - 1, max_y - 1, height - 1) + a[max_x][max_y],
						MaxGet(a, max, max_x - 1, max_y, height - 1) + a[max_x][max_y]);
	}
}

void MaxGet(vector<vector<int> > a, vector<vector<int> > &max, int height)
{
	int k = 1;
	int i, j;
	max[0][0] = a[0][0];
	for (i = 1; i <= height - 1; i++)
	{
		for (j = 0; j <= k; j++)
		{
			if (j == 0)
				max[i][j] = max[i - 1][j] + a[i][j];
			else if (j == k)
				max[i][j] = max[i - 1][j - 1] + a[i][j];
			else
				max[i][j] = more(max[i - 1][j - 1] + a[i][j], 
					             max[i - 1][j] + a[i][j]);
		}
		k++;
	}
}

void ShowMatrix(vector<vector<int> > a)
{
	int k = 1, i, j;//更新
	for (i = 1; i <= a.size(); i++)
	{//从数据集中读取
		for (j = a.size() - 1; j >= k; j--)
			cout << " ";
		for (j = 1; j <= k; j++)
			cout << a[i - 1][j - 1] << " ";
		cout << endl;
		k++;
	}
}

vector<string> GetPath(vector<vector<int> > max)
{
	vector<string> path;
	int height = max.size();
	int i;
	int best = max[height - 1][0], best_i = 0;
	for (i = 1; i <= height - 1; i++)
	{
		if(max[height - 1][i] > best)
		{
			best = max[height - 1][i];
			best_i = i;
		}
	}

	for (i = height - 1; i >= 1; i--)
	{
		if (best_i == 0)
		{
			path.push_back("left");
			best_i = 0;
		}
			
		else if (best_i == i)
		{
			path.push_back("right");
			best_i = i - 1;
		}
		else
		{
			if (max[i - 1][best_i] > max[i - 1][best_i - 1])
				path.push_back("left");
			else
			{
				path.push_back("right");
				best_i--;
			}
		}
	}
	return path;
}

int main()
{
	int i, j;//for iterator
	srand((unsigned)time(NULL));
	ofstream data_in("data.txt", ios::trunc);//每次删除并重建数据集
	for (i = 1; i <= DATA_LENGTH; i++)
		data_in << rand() % 10 << " ";//选择的数值小是为了能够快速检查正确性(0-9)
	data_in.close();//创建数据集完成，保存并退出
	cout << "Data created!" << endl;

	ifstream data_out("data.txt");

	cout << "Input the height:";
	int height;
	cin >> height;
	while (height <= 0)
	{
		cout << "Input error! Try again:";
		cin >> height;
	}

	//还有这种操作
	vector<vector<int> > a(height, vector<int>(height));
	vector<vector<int> > max(height, vector<int>(height));
	vector<string> path;//记录路径

	/*笨死的操作
	a.resize(height);
	for(i=1;i<=height;i++)
	a[i-1].resize(height);
	max.resize(height);
	for(i=1;i<=height;i++)
	max[i-1].resize(height);
	*/

	//initial
	for (i = 1; i <= height; i++)
		for (j = 1; j <= height; j++)
			a[i - 1][j - 1] = 0;
	for (i = 1; i <= height; i++)
		for (j = 1; j <= height; j++)
			max[i - 1][j - 1] = 0;


	int temp;
	int k = 1;
	for (i = 1; i <= height; i++)
	{//从数据集中读取
		for (j = 1; j <= k; j++)
		{
			data_out >> temp;
			a[i - 1][j - 1] = temp;
		}
		k++;
	}

	cout << "Data shows below:" << endl << endl;
	ShowMatrix(a);

	cout << endl << "For best sum by choosing one path from top to the bottom:" << endl << endl;
	
	cout << "Recur:" << endl;
	
	start = clock();
	for (i = 0; i <= height - 1; i++)
		max[height - 1][i] = MaxGet(a, max, height - 1, i, height);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	for (i = 0; i <= height - 1; i++)
		cout << max[height - 1][i] << " ";
	cout << endl <<"Duration=" << duration << "s" << endl;
	cout << endl << endl;
	

	cout << "DP:" << endl;
	start = clock();
	MaxGet(a, max, height);
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;

	ShowMatrix(max);
	path = GetPath(max);
	cout << "\nPath: ";
	for (i = path.size() - 1; i >= 0; i--)
		cout << path[i] << " ";
	
	cout << endl << "\nDuration=" << duration << "s" << endl << endl;
	
	

	system("pause");
	return 0;
}
