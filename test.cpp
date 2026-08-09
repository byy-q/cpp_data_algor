#include<vector>
#include<iostream>
#include"algorithm.h"
int main()
{
    std::vector<int>arr = {4,3,2,5,6,3,};
    auto ptr = arr.begin();
    Merge_sort(arr.begin(),arr.end());
    while(ptr != arr.end())
    {
        std::cout<<*ptr<<" ";
        ptr++;
    }
    std::cout<<std::endl;
}
