#include <iterator>
#include <vector>

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
	using value_type = std::iterator_traits<Iterator>::value_type;
	
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


int Horner_polynome(int x,int* A,int n)
{
    int y = 0;
    for(int i = 0 ;i < n;i++) 
    {
        y = x * y + *(A+i);
    }
    return y;
}


template<class Iterator , class T>
Iterator find(Iterator first,Iterator last,const T& value)
{
	while(first != last && *first != value)
		++first;
	return first;
}




