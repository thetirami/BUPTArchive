#include"sort_algorithm.cpp"


clock_t start,stop;
double duration;


int main() {
	ifstream data_in;
	vector<int> a;
	vector<int> temp;   // renew
	vector<int> temp1;  // for merge sort
	int temp_int,i;

	cout<<"�������ݹ�ģΪ100,1000,5000,10000,40000\n\n";

	/////////////100��˳��//////////////////////////////////////////////////
	cout<<"���ݹ�ģΪ100��\n";
	data_in.open("big_end_ordered.txt");
	for(i=0;i<=99;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	////////////////////100������//////////////////////////////////////
	vector <int>().swap(a);
	data_in.open("small_end_ordered.txt");
	for(i=0;i<=99;i++) {
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////100,���///////////////////////////////////	
	vector <int>().swap(a);
	data_in.open("unordered.txt");
	for (i = 0; i <= 99; i++) {
		data_in >> temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	/////////////1000��˳��//////////////////////////////////////////////////
	vector <int>().swap(a);
	cout<<"\n���ݹ�ģΪ1000��\n";
	data_in.open("big_end_ordered.txt");
	for(i=0;i<=999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////1000������/////////////////////////////////////////////////	
	vector <int>().swap(a);
	data_in.open("small_end_ordered.txt");
	for(i=0;i<=999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////1000,���///////////////////////////////////
	vector <int>().swap(a);
	data_in.open("unordered.txt");
	for(i=0;i<=999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	/////////////5000��˳��//////////////////////////////////////////////////
	vector <int>().swap(a);
	cout<<"\n���ݹ�ģΪ5000��\n";
	data_in.open("big_end_ordered.txt");
	for(i=0;i<=4999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();
	///////////////////5000������/////////////////////////////////////////////////	
	vector <int>().swap(a);
	data_in.open("small_end_ordered.txt");
	for(i=0;i<=4999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////5000,���///////////////////////////////////
	vector <int>().swap(a);
	data_in.open("unordered.txt");
	for(i=0;i<=4999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	cout<<"\n���ݹ�ģΪ10000:\n";
	/////////////10000��˳��//////////////////////////////////////////////////
	vector <int>().swap(a);
	data_in.open("big_end_ordered.txt");
	for(i=0;i<=9999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	////////////////////10000������////////////////////////////////////////
	vector <int>().swap(a);
	data_in.open("small_end_ordered.txt");
	for(i=0;i<=9999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////10000,���///////////////////////////////////
	vector <int>().swap(a);
	data_in.open("unordered.txt");
	for(i=0;i<=9999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	cout<<"\n���ݹ�ģΪ40000:\n";
	/////////////40000��˳��//////////////////////////////////////////////////
	vector <int>().swap(a);
	data_in.open("big_end_ordered.txt");
	for(i=0;i<=39999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ˳������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	////////////////////40000������////////////////////////////////////////////////
	vector <int>().swap(a);
	data_in.open("small_end_ordered.txt");
	for(i=0;i<=39999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////40000,���///////////////////////////////
	vector <int>().swap(a);
	data_in.open("unordered.txt");
	for(i=0;i<=39999;i++)
	{
		data_in>>temp_int;
		a.push_back(temp_int);
	}
	temp=a;

	compare_num=0;
	move_num=0;//reset
	start=clock();
	insertsort(a);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  �鲢����:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  ��������:\n    ��������\t��ʱ:"<<duration<<"s";
	show();

	data_in.close();

	cout<<"\n\n--------------------�Ƚ����-------------------------";

	cin.get();
	return 0;
}
