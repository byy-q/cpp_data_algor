#include <iostream>
#include "algorithm.h"
#include <array>
#include <algorithm>

using std::array;
array<int,10> target = { 3,-4,3,2,-2,6,1,-5,7,-2 }; 
int main(int argc,char** argv)
{
    decltype(target.begin()) first = target.begin();
    decltype(target.end()) last = target.end();
    auto maxSum = MaxSubArray(target.begin(), target.end(), first, last);
    for(auto it = first ; it != last ;it++)
    {
        
        std::cout<<*it<<" ";
    }
    
    std::cout << "\nmaxSum = " << maxSum ;
    return 0;

}