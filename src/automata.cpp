#include <cstdio>
#include "automata.h"
#include <iostream>


CA::CA(int size) {
	this->size = size;
}


CA::~CA() {
}

int CA::get_size() {
	return this->size;
}


