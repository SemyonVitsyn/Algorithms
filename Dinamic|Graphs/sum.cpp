#include <iostream>

template<typename Type1, typename Type2>

void copy_array(Type1* src, Type2* dst, size_t size = 1) {
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
}