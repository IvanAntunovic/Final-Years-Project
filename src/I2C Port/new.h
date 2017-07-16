#ifndef 	_NEW_H_
#define		_NEW_H_

#include <stdlib.h>

void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void * ptr);
void operator delete[](void * ptr);

#endif