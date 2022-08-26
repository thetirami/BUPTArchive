#include<iostream>
#include<vector>
#include<fstream>
#include<time.h>
#include<cstdlib>
#include<iomanip>

using namespace std;

static long int compare_num=0;
static long int move_num=0;

void show()
{
	cout<<"\t移动次数:"<<move_num;
	cout<<"\t比较次数:"<<compare_num<<endl;
}

void insertsort(vector<int> &R)
{  
	for(int i=1;i<R.size();i++)   
	{
		int temp=R[i];
		int j=i-1; 
		while ((j>=0)&&(temp<R[j]))
		{      
			compare_num++;
			move_num++;
			R[j+1]=R[j]; 
			j--; 
		}
		compare_num++;
        R[j+1]=temp;
	}
}

void Merge(vector<int> &source,vector<int> &temp,int start,int mid,int end)
{
	int i=start, j=mid+1, k=start;
	while(i!=mid+1&&j!=end+1)
	{
		compare_num++;
		if(source[i]>source[j])
		{
			temp[k++]=source[j++];
			move_num++;
		}
		else
		{
			temp[k++]=source[i++];
			move_num++;
		}
	}
	while(i!=mid+1)
	{
		temp[k++]=source[i++];
		move_num++;
	}
	while(j!=end+1)
	{
		temp[k++]=source[j++];
		move_num++;
	}
	for(i=start;i<=end;i++)
		source[i]=temp[i];
}

void MergeSort(vector<int> &source,vector<int> &temp,int start,int end)
{
	int mid;
	if(start<end)
	{
		mid=(start+end)/2;
		MergeSort(source,temp,start,mid);
		MergeSort(source,temp,mid+1,end);
		Merge(source,temp,start,mid,end);
	}
}

void Quicksort(vector<int> &a,int low,int high)
{
    if(low >= high)
        return;
    int first=low;
    int last=high;
    int key=a[first];
 
    while(first<last)
    {
        while(first<last&&a[last]>=key)
		{
			--last;
			compare_num++;
		}
		compare_num++;
        a[first]=a[last];
		if(first!=last)
			move_num++;
        while(first<last&&a[first]<=key)
		{
			++first;
			compare_num++;
		}
		compare_num++;
        a[last] = a[first];
		if(first!=last)		
			move_num++;
    }
    a[first]=key;
    Quicksort(a,low,first-1);
    Quicksort(a,first+1,high);
}

