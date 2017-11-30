
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
    delete(this->array);
}

int CA::get_size() {
    return this->size;
}

int CA::run(int time, int export_time){
    int step = 0;
    cellF element,pom;
    Cell a;

    element.id = 0;
    // Prikladova bunka
    a.x = 50;
    a.y = 50;
    a.type = FIRE;
    a.fuelLoad = 0;
    a.fuelDepth = 0;
    a.fuelHeat = 0;
    a.fuelMoisture = 0;
    a.fuelMoistExt = 0;
    a.ovendry = 0;
    a.fuelMineralTot = 0;
    a.fuelMineralEff = 0;
    a.windSpeed = 0;
    a.terain = 0;
    element.cell = &a; //Prvni bunka pozaru

    cell_front.push_back(element);

    // Hlavni cyklus krokovani
    while(true) {

        // Dosel ohen
        if(cell_front.empty()) {
            return(step);
        }

        if ((element = cell_front.front()).id > step){
            step = element.id;

            if (step % export_time == 0) {
                // Vyplivnuti obrazku nynejsiho stavu?
            }

            // Dosel cas
            if (step == time) {
                return 0;
            }
        }
        // Vyhozeni pouzite nastene bunky z fronty
        cell_front.pop_front();

        // Okoli horici bunky
        for(int j = -1; j < 2; j++){
            for(int i = -1; i < 2; i++){

                // Zde zpracovani okolnich bunek

                //array[element.cell.x + i][element.cell.y + j] okoli soucasne bunky
                if((pom.cell = &(array[element.cell->x + i][element.cell->y + j]))->type == FIRE){
                    pom.id = step + 1;
                    cell_front.push_back(pom); // Ulozeni horici bunky
                }
            }
        }

    }
    return 0;
}


