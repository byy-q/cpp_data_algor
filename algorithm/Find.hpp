template<class Iterator>
Iterator __Find(Iterator first, Iterator last,const typename Iterator_traits<Iterator>::value_type& value,std::forward_iterator_tag)
{
	Iterator current = first;
	while(*current != value && current != last)
		current++;
	if(*current == value)
		return current;
	return last;
}

template<class Iterator>
Iterator Find(Iterator first,Iterator last ,const typename Iterator_traits<Iteator>::value_type& value)
{
	return __Find(first,last,value,typename Iterator_traits<Iterator>::iterator_category);
}