
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





