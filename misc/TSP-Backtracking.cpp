/*
分支限界法PPT中的例子

代价矩阵
0	3	1	5	8
3	0	6	7	9
1	6	0	4	2
5	7	4	0	3
8	9	2	3	0
will be  loaded from data.cfg
*/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<limits>
#include<vector>

#define CityNum 5

using namespace std;

vector<vector<int> > jour(CityNum,vector<int>(CityNum));
vector<int> path(CityNum);
vector<int> bestpath(CityNum);
int cost=0;
int bestcost=numeric_limits<int>::max();

void output(int i)
{
	if(i==0)
		cout<<"A";
	else if(i==1)
		cout<<"B";
	else if(i==2)
		cout<<"C";
	else if(i==3)
		cout<<"D";
	else if(i==4)
		cout<<"E";
}

void backtrack(int t)
{
	int i,j;
	if(t==CityNum-1)   
    {//已经搜索到叶节点，已经选择了最后1个城市
        if(jour[path[t-1]][path[t]]!=0&&jour[path[t]][0]!=0)
		{//最后1个城市与前一城市相连，与第1个城市相连，组成1个满足条件的回路
			if(cost+jour[path[t]][0]<bestcost&&jour[path[t]][0]!=0)
			{
				bestcost=cost+jour[path[t]][0];
				for(j=0; j<=CityNum-1; j++)  
					bestpath[j]=path[j];
			}								
		}		
    }	
	else
	{
		for(j=t-1;j<=CityNum-1;j++)
		{//考察x[i]的各个可能取值
			if(jour[path[t-1]][path[j]]!=0&&cost+jour[path[t-1]][path[j]]<bestcost)
			{
				swap(path[t],path[j]);//加入第i个城市
                cost+=jour[path[t-1]][path[t]];//更新扩展后的路径的代价
				backtrack(t+1);//递归搜索以x[i]为根的后续子树
                cost-=jour[path[t-1]][path[t]];//搜索失败，回溯，回到
                swap(path[t],path[j]);
			}
		}		
	}
}

int main()
{
	int i,j;//iterator
	int temp;
	
	ifstream data_in("data.cfg");
	for(i=0;i<=CityNum-1;i++)
		for(j=0;j<=CityNum-1;j++)
			data_in>>jour[i][j];
	data_in.close();
	
	cout<<"Matrix shows below:\n";
	for(i=0;i<=CityNum-1;i++)
	{
		path[i]=i;
		for(j=0;j<=CityNum-1;j++)
			cout<<jour[i][j]<<"\t";
		cout<<endl;
	}
		
	cout<<"Suppose the traveler begins at Point A, the first point."<<endl;
	backtrack(1);
	cout<<"Path = ";
	for(i=0;i<=CityNum-1;i++)
	{
		output(bestpath[i]);
		cout<<" -> ";
	}	
	output(bestpath[0]);

	int length=0;
	for(i=0;i<=CityNum-2;i++)
		length+=jour[bestpath[i]][bestpath[i+1]];
	length+=jour[bestpath[CityNum-1]][0];
	cout<<endl<<"Cost = "<<length<<endl<<endl;
		
	system("pause");
	return 0;
}