#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> v;
    for(int i = 0 ; i < 5 ; i ++){
        v.push_back(i);
    }
    // const vector<int>::iterator
    // 错误的,此时注意 it的指向不可以发生改变
    // for(const vector<int>::iterator it = v.begin() ; it != v.end() ; it++){

    // }
    // vector<int>::const_iterator 表示指针执行的值得不可以改变
    for(vector<int>::const_iterator it = v.begin() ; it != v.end() ; it ++){
        cout << *it << "  ";
    }
    cout << endl;
}