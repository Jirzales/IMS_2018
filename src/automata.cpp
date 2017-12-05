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
    a.load = 0;							// W0
    a.depth = 0;						// DELTA
	a.surfaceToVolume = 0;				// SIGMA
    a.heatContent = 0;					// h
    a.moistureContent = 0;				// Mf
    a.moistureContentOfExtinction = 0;	// Mx
    a.ovendryDensity = 0;				// Pp
    a.totalMineralContent = 0;			// St
    a.effectiveMineralContent = 0;		// Se
    a.windSpeed = 0;					// -
    //a.slope = 0;						// -
    element.cell = &a; 					// Prvni bunka pozaru

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

void CA::test_function() {
	Cell cell;
	cell.load = 1.08;						// W)
	cell.depth = 1.;						// DELTA
    cell.x = 51;
    cell.y = 51;
    cell.type = FIRE;
	cell.surfaceToVolume = 5000;			// SIGMA
    cell.heatContent = 1.5;					// h
    cell.moistureContent = 0.09;			// Mf
    cell.moistureContentOfExtinction = 0.3;// Mx
    cell.ovendryDensity = 40.;				// Pp
    cell.totalMineralContent = 0.001;		// St
    cell.effectiveMineralContent = 20.;		// Se
    //cell.slope = 10.;						

	// test cases
	std::cout.precision(17);
	std::cout << "result:  ";
	//std::cout << CA_Pb(cell) << std::endl;
	//std::cout << CA_BETA(cell) << std::endl;
	//std::cout << CA_Qig(cell) << std::endl;
	//std::cout << CA_EPSILON(cell) << std::endl;
	//std::cout << CA_ETA_S(cell) << std::endl;
	//std::cout << CA_ETA_M(cell) << std::endl;
	//std::cout << CA_BETAop(cell) << std::endl;
	//std::cout << CA_GAMMAmax(cell) << std::endl;
	//std::cout << CA_GAMMA(cell) << std::endl;
	//std::cout << CA_IR(cell) << std::endl;
	std::cout << CA_Ro(cell) << std::endl;
	//std::cout << CA_Wn(cell) << std::endl;

	//std::cout << A(cell) << std::endl;
	//std::cout << B(cell) << std::endl;
	//std::cout << C(cell) << std::endl;
	//std::cout << E(cell) << std::endl;

	//std::cout << CA_IR(cell) << std::endl;


	return;
}

















