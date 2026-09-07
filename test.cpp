#include <iterator>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
    std::vector<int> vec = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    auto begin = vec.begin();
    auto Move_begin = std::make_move_iterator(begin);// the *operator of move iterator return a rvalue
    std::allocator<int> alloc;
    auto end = alloc.allocate(10);
    auto last = std::uninitialized_copy(std::make_move_iterator(begin),std::make_move_iterator(vec.end()),last);
    
    

}
