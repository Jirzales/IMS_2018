
#include "automata.h"

CA::CA(int size) {
    this->size = size;

    // Vytvoreni pole
    Cell** array = new Cell*[size];
    for(int i = 0; i < size; ++i){
        array[i] = new Cell[size];
    }

    this->array = array;
}


CA::~CA() {
    for(int i = 0; i < size; ++i){
        free(this->array[i]);
    }
    free(this->array);
}

int CA::get_size() {
    return this->size;
}


