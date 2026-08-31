#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iostream>

using namespace std;
int main()
{
    const int arraySize = 7;
    int ia[arraySize] = {0,1,2,3,4,5,6};
    vector<int> ivect(ia,ia+arraySize);
    list<int> ilist(ia,ia+arraySize);
    deque<int> ideque(ia,ia+arraySize);
    vector<int>::iterator it1 = find(ivect.begin(),ivect.end(),4);
    ve
}