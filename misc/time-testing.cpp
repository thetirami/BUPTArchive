#include<time.h>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<iomanip>

using namespace std;

clock_t start,stop;
double duration;

int MaxSubsequenceSum1(const int A[],int N)
{
	int ThisSum,MaxSum,i,j,k;
	MaxSum=0;
	for(i=0;i<N;i++)
	{
		for(j=i;j<N;j++) 
		{
			ThisSum=0;
			for(k=i;k<=j;k++)
				ThisSum+=A[k];
			if(ThisSum>MaxSum)
				MaxSum=ThisSum;
		}
	}
	return MaxSum;
}

int MaxSubsequenceSum4(const int A[],int N)
{
	int ThisSum,MaxSum,j;
	ThisSum=MaxSum=0;
	for(j=0;j<N;j++) 
	{
		ThisSum+=A[j];
		if(ThisSum>MaxSum)
			MaxSum=ThisSum;
		else if(ThisSum<0)
			ThisSum=0;
	}
	return MaxSum;
}

int main()
{
	cout<<"How long is the data? 	";
	int len,i;/*用len来表示数据集长度*/
	ofstream data_in("data.txt",ios::trunc);/*每次删除并重建数据集*/
	cin>>len;
	for(i=1;i<=len;i++)
		data_in<<i<<" ";
	data_in.close();/*创建数据集完成，保存并退出*/
	ifstream data_out("data.txt");/*读取方式重新打开*/
	i=0;
	
	int A[len];
	while(!data_out.eof())
	{
		data_out>>A[i];
		i++;
	}/*已经将数据集录入*/
	
	cout<<"Which algorithm do you want to test?\n";
	cout<<"Please input 1 or 4 to choose:";
	
	int method,result;
	cin>>method;
	while(method!=1&&method!=4)
	{
		cout<<"Please input 1 or 4 to choose!\n";
		cout<<"Which algorithm do you want to test?";
		cin>>method;
	}
	
	if(method==1)
	{
		start=clock();
		//for(i=0;i<5;i++)
	    result=MaxSubsequenceSum1(A,len);
		stop=clock();
		duration=((double)(stop - start))/CLK_TCK;
		cout<<"Doing Algorithm 1 takes "<<fixed<<duration<<"s\n";
	}
	
	else if(method==4)
	{
		start=clock();
		for(i=0;i<10000;i++)
			result=MaxSubsequenceSum4(A,len);
		stop=clock();
		duration=((double)(stop - start))/CLK_TCK;
		cout<<"Doing Algorithm 4 10000 times takes "<<fixed<<duration<<"s\n";
	}
	
	system("pause");
	return 0;
}
