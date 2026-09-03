#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <cstddef>
#include <iterator>
#include <vector>


#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/Iterator.cpp"
#elif defined(__linux__)
	#include "algorithm/Iterator.cpp"
#elif defined(__APPLE__)
	#include "algorithm/Iterator.cpp"
#endif


#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/sort.cpp"
#elif defined(__linux__)
	#include "algorithm/sort.cpp"
#elif defined(__APPLE__)
	#include "algorithm/sort.cpp"
#endif



#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/horner.cpp"
#elif defined(__linux__)
	#include "algorithm/horner.cpp"
#elif defined(__APPLE__)
	#include "algorithm/horner.cpp"
#endif



#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/sort.cpp"
#elif defined(__linux__)
	#include "algorithm/sort.cpp"
#elif defined(__APPLE__)
	#include "algorithm/sort.cpp"
#endif


#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/Find.cpp"
#elif defined(__linux__)
	#include "algorithm/Find.cpp"
#elif defined(__APPLE__)
	#include "algorithm/Find.cpp"
#endif



#endif