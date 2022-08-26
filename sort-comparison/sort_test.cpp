#include"sort_algorithm.cpp"


clock_t start,stop;
double duration;


int main() {
	ifstream data_in;
	vector<int> a;
	vector<int> temp;   // renew
	vector<int> temp1;  // for merge sort
	int temp_int,i;

	cout<<"测试数据规模为100,1000,5000,10000,40000\n\n";

	/////////////100，顺序//////////////////////////////////////////////////
	cout<<"数据规模为100：\n";
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
	cout<<"  插入排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	////////////////////100，逆序//////////////////////////////////////
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
	cout<<"  插入排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////100,随机///////////////////////////////////	
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
	cout<<"  插入排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	/////////////1000，顺序//////////////////////////////////////////////////
	vector <int>().swap(a);
	cout<<"\n数据规模为1000：\n";
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
	cout<<"  插入排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////1000，逆序/////////////////////////////////////////////////	
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
	cout<<"  插入排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////1000,随机///////////////////////////////////
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
	cout<<"  插入排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	/////////////5000，顺序//////////////////////////////////////////////////
	vector <int>().swap(a);
	cout<<"\n数据规模为5000：\n";
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
	cout<<"  插入排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();
	///////////////////5000，逆序/////////////////////////////////////////////////	
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
	cout<<"  插入排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////5000,随机///////////////////////////////////
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
	cout<<"  插入排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	cout<<"\n数据规模为10000:\n";
	/////////////10000，顺序//////////////////////////////////////////////////
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
	cout<<"  插入排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	////////////////////10000，逆序////////////////////////////////////////
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
	cout<<"  插入排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////10000,随机///////////////////////////////////
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
	cout<<"  插入排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	cout<<"\n数据规模为40000:\n";
	/////////////40000，顺序//////////////////////////////////////////////////
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
	cout<<"  插入排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    顺序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	////////////////////40000，逆序////////////////////////////////////////////////
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
	cout<<"  插入排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	MergeSort(a,temp,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    逆序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();
	////////////////////////40000,随机///////////////////////////////
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
	cout<<"  插入排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	temp1=a;
	start=clock();
	MergeSort(a,temp1,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  归并排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	compare_num=0;
	move_num=0;//reset
	a=temp;
	start=clock();
	Quicksort(a,0,a.size()-1);
	stop=clock();
	duration=((double)(stop - start))/CLK_TCK;
	cout<<"  快速排序:\n    无序数据\t耗时:"<<duration<<"s";
	show();

	data_in.close();

	cout<<"\n\n--------------------比较完成-------------------------";

	cin.get();
	return 0;
}
