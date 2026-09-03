/** 
    *@brief:find the max subarray in the array[begin,end)
    *@param:begin and last are the range of the array,begin is included while the end is excluded
    *@param:you need to declare two iterator in advance,after the function,the two iterator whill store the range 
        range of the max subarray,first is included while last is excluded
    *@return:the sum of the max subarray
    *@note:the function is based on the divide and conquer method ,the time complexity is O(nlogn)
*/
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