#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <cstddef>
#include <iterator>
#include <vector>


#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/Iterator.hpp"
#elif defined(__linux__)
	#include "algorithm/Iterator.hpp"
#elif defined(__APPLE__)
	#include "algorithm/Iterator.hpp"
#endif


#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/sort.hpp"
#elif defined(__linux__)
	#include "algorithm/sort.hpp"
#elif defined(__APPLE__)
	#include "algorithm/sort.hpp"
#endif



#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/horner.hpp"
#elif defined(__linux__)
	#include "algorithm/horner.hpp"
#elif defined(__APPLE__)
	#include "algorithm/horner.hpp"
#endif



#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/sort.hpp"
#elif defined(__linux__)
	#include "algorithm/sort.hpp"
#elif defined(__APPLE__)
	#include "algorithm/sort.hpp"
#endif


#if defined(_WIN32) || defined(_WIN64)
	#include "algorithm/Find.hpp"
#elif defined(__linux__)
	#include "algorithm/Find.hpp"
#elif defined(__APPLE__)
	#include "algorithm/Find.hpp"
#endif



#endif