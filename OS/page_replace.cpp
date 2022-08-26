#include<bits/stdc++.h>


using namespace std;


int replace(vector<int> & frames,int data) {
    // 如果能够命中，返回命中位置，不能则返回-1
    for(int i = 0; i < frames.size(); ++i)
        if(frames[i] == data)
            return i;
    return -1;
}


void printFrames(vector<int>& frames) {
    // 输出frames
    for(int frame : frames)
        cout<<frame<<" ";
    cout<<endl;
}


void pageReplaceFIFO(vector<int> nums,int size) {
    // 数据 页帧数
    vector<int> frames(size, -1);
    int ptr=0, cnt=1;
    for (int num : nums) {
        if(replace(frames, num) != -1)
            ++cnt;
        else
            frames[ptr] = num;
            ptr = (ptr + 1) % size;
        printFrames(frames);
    }
    cout << "Page fault: " << nums.size() - cnt << " times" << endl;
}


void pageReplaceLRU(vector<int> nums,int size) {
    //数据 页帧数
    vector<int> frames(size, -1);
    vector<int> flag(size, 0);
    int ptr, cnt=1, time=0, isFull=0;
    for (int num : nums) {
        if (time >= size)
            isFull = 1;
        ptr = replace(frames, num);
        if (ptr == -1) {
            if (isFull)
                ptr = min_element(flag.begin(), flag.end()) - flag.begin();
            else
                // 如果是非满状态则逐个填入，恰好使用time作为计数器
                ptr = time;
            frames[ptr] = num;
        } else
            ++cnt;
        flag[ptr] = time++;  // 无论是否命中都更新最近命中时间
        printFrames(frames);
    }
    cout << "Page fault: " << nums.size() - cnt << " times" << endl;
}


void init(vector<int>& nums, int& size) {
    int len;
    srand(time(NULL));
    cout << "请输入随机序列长度，页帧数量" << endl;
    cin >> len >> size;
    nums.clear();
    for (int i = 0; i < len; ++i)
        nums.push_back(rand()%10);
}


int main() {
    vector<int> nums{7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int size = 3;

    pageReplaceFIFO(nums,size);
    pageReplaceLRU(nums,size);
    system("pause");
}
