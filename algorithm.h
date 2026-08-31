#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <cstddef>
#include <iterator>
#include <vector>





//创造一个迭代器
template<class T>
class Iterator
{
	public:
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::input_iterator_tag;
	private:
		T* ptr;
};

template<class Iterator>
class Iterator_traits
{
	using iterator_category = typename Iterator::iterator_category;
	using value_type = typename Iterator::value_type;
	using difference_type = typename Iterator::difference_type;
	using pointer = typename Iterator::pointer;
	using reference = typename Iterator::reference;
};
//特化版本
template<class T>
class Iterator_traits<T*>
{
	public:
		using value_type =  T;
		using pointer =  T*;
		using reference =  T&;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;	
};

template<class T>
class Iterator_traits<const T*>
{
	using value_type =  T;
	using pointer =  T*;
	using reference =  T&;
	using difference_type = ptrdiff_t;
	using iterator_category = std::random_access_iterator_tag;	
};

//设计一个算法


/*template<class Iterator>
void _func(Iterator first,Iterator last,std::input_iterator_tag);
template<class Iterator>
void func(Iterator first,Iterator last)
{
	typename Iterator_traits<Iterator>::value_type;
	typename Iterator_traits<Iterator>::pointer;
	typename Iterator_traits<Iterator>::reference;
	typename Iterator_traits<Iterator>::difference_type;
	typename Iterator_traits<Iterator>::iteraor_category;
	_func(first,last,Iterator_traits<Iterator>::iterator_category);//补充迭代器类别
}
*/







template<typename Iterator>
void swap(Iterator first, Iterator second)
{
	using value_type = typename std::iterator_traits<Iterator>::value_type;
	value_type temp = *first;
	*first = *second;
	*second = temp;
}

template<typename Iterator>
void Insertion_sort(Iterator first, Iterator last)
{
	if (first == last)
		return;

	for (Iterator it = std::next(first); it != last; ++it) {
		auto value = *it;
		Iterator pos = it;

		while (pos != first) {
			Iterator prev = std::prev(pos);
			if (*prev <= value)
				break;
			*pos = *prev;
			pos = prev;
		}

		*pos = value;
	}
}

template<typename Iterator>
void Merge_sort(Iterator first, Iterator last)
{
	auto distance = std::distance(first, last);
	if (distance < 2)
		return;

	Iterator mid = first;
	std::advance(mid, distance / 2);
	Merge_sort(first, mid);
	Merge_sort(mid, last);
    //merge procedure
	using value_type = typename std::iterator_traits<Iterator>::value_type;
	std::vector<value_type> buffer;
	buffer.reserve(static_cast<size_t>(distance));

	Iterator left = first;
	Iterator right = mid;

	while (left != mid && right != last) {
		if (*left <= *right) {
			buffer.push_back(*left);
			++left;
		} else {
			buffer.push_back(*right);
			++right;
		}
	}

	while (left != mid) {
		buffer.push_back(*left);
		++left;
	}

	while (right != last) {
		buffer.push_back(*right);
		++right;
	}

	Iterator out = first;
	for (const auto& val : buffer) {
		*out = val;
		++out;
	}
}




using std::forward_iterator_tag;

int Horner_polynome(int,int*,int n);

template<class Iterator>
typename Iterator_traits<Iterator>::value_type  MaxSubArray(Iterator begin, Iterator end, Iterator& first, Iterator& last)
{
	//first point to the begin of the subarray ,and the last point to the next position of the last subarray
	//using the divide_handle 
	using value_type = typename Iterator_traits<Iterator>::value_type;
	using difference_type = typename Iterator_traits<Iterator>::difference_type;
	using Iterator_category = typename Iterator_traits<Iterator>::iterator_category;
	using pointer = typename Iterator_traits<Iterator>::pointer;
	using reference = typename Iterator_traits<Iterator>::reference;

	if (begin == end) {
		first = begin;
		last = end;
		return 0;
	}

	difference_type length = end - begin;
	if (length == 1) {
		first = begin;
		last = begin + 1;
		return *begin;
	}

	Iterator Mid = begin + (difference_type)((length - 1) / 2);

	

	//find the maxsubarray cross the middle point
	
	//find the left bond
	value_type crossMid_left_current_Sum = *Mid;
	value_type crossMid_left_max_Sum = crossMid_left_current_Sum;
	Iterator leftBond = Mid;
	Iterator current_iterator =  Mid - 1;
	while(current_iterator != begin-1)
	{
		crossMid_left_current_Sum += *current_iterator;
		if(crossMid_left_current_Sum > crossMid_left_max_Sum)
		{
			crossMid_left_max_Sum = crossMid_left_current_Sum;
			leftBond = current_iterator;
		}
		//std::cout<<crossMid_left_max_Sum<<"\n";
		current_iterator--;
	}
	//std::cout<<"\n";

	//find the right 
	value_type crossMid_right_current_Sum = *(Mid+1);
	value_type crossMid_right_max_Sum = crossMid_right_current_Sum;
	Iterator rightBond = Mid+2;
	current_iterator = rightBond;
	while(current_iterator != end)
	{
		crossMid_right_current_Sum += *current_iterator;
		if(crossMid_right_current_Sum > crossMid_right_max_Sum)
		{
			rightBond = current_iterator;
			crossMid_right_max_Sum = crossMid_right_current_Sum;
		}
		//std::cout<<crossMid_right_max_Sum<<"\n";
		current_iterator++;
	}
	value_type crossMid_MaxSum = 0;
	if(crossMid_right_max_Sum <= 0 )
	{
			crossMid_MaxSum = crossMid_left_max_Sum;
			rightBond = Mid + 1;
	}
	else
	{
		crossMid_MaxSum = crossMid_left_max_Sum + crossMid_right_max_Sum;
		rightBond += 1;
	}
	//find the maxsubarray in the array[bigen:Mid)
	Iterator leftFirst = begin, leftLast = Mid;
	value_type leftSum = MaxSubArray(begin, Mid , leftFirst, leftLast);

	//find the maxsubarray in the array[Mid+1，end);
	Iterator rightFirst = Mid + 1, rightLast = end;
	value_type rightSum = MaxSubArray(Mid + 1, end, rightFirst, rightLast);


	if(leftSum >= rightSum && leftSum >= crossMid_MaxSum)
	{
		first = leftFirst;
		last = leftLast;
		return leftSum;
	}	
	else if(rightSum > leftSum && rightSum > crossMid_MaxSum)
	{
		first = rightFirst;
		last = rightLast;
		return rightSum;
	}
	else
	{
		first = leftBond;
		last = rightBond;
		return crossMid_MaxSum;
	}
}


#endif