#include "automata.h"

extern int CA_cell_size;
extern int CA_size;
extern int CA_fuel_prob;
extern int CA_time;

using namespace std;

CA::CA() {
	std::cout << "implicit constructor called!\n"; 
}


CA::CA(char *csv) {
	char buffer[256];		// name inserted through cmd line
	int width  = CA_size, 
		height = CA_size;
	ifstream file;

	// open input image/csv to check if height-width matches set CA size
	if (csv != NULL) {
		strcpy(buffer, "tests/");
		strcat(buffer, csv);
		file.open(buffer);	
		if (!file.is_open())
			ERROR("File could not be opened! Unexpected format!\n", 1);
		
		// get csv-image reslution
		file.getline(buffer, 100, '\n');
		width = atoi(strtok(buffer, ","));
		height = atoi(strtok(NULL, ", "));

		if ((width != height) && (width != CA_size))
			ERROR("Error: input size is different from csv data size", 2);
	}
    this->size = width;

    // allocating space for Cellular Automaton
    Cell** array = new Cell*[this->size];
    for(int i = 0; i < size; ++i){
        array[i] = new Cell[this->size];
    }

    this->array = array;
	srand(time(NULL));

	// set randomly every cell to FUEL or IGNITED
	// yo can set probability (in %) of generating FUEL	
	for (int i=0; i < this->size; i++) {
		for (int j=0; j < this->size; j++) {
			if (rndm() <= CA_fuel_prob) {
				this->array[i][j].type = NONIGNITED;
			}
			else {
				this->array[i][j].type = NONFLAMMABLE; 
			}
		}
	}
    set_distance(CA_cell_size);
	
	if (csv != NULL) {
		initialize_CA_cells(file, width, height);
		file.close();
	}
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

int CA::run(){
    int step = 0;
    cellF element,pom;
    Cell a;

    element.id = 0;


	double act_time = 0;


	for (int i=0; i < this->size; i++)
		for (int j=0; j < this->size; j++)
//cout << "actual time: " << act_time << endl;
			if (element.cell.type == FIRE) {
				element.cell = this->array[i][j];
				cell_front.push_back(element);
			}

    double deltaT = get_deltaT(cell_front);

    // Hlavni cyklus krokovani
    while(true) {

        // Dosel ohen
        if(cell_front.empty()) {
            return(step);
        }

        if ((element = cell_front.front()).id > step){
            step = element.id;
			
			// Zjisteni zda se ma nehorici bunka podpalit
            cell_ingite(); 

			// get next timestep difference in seconds and check for end of simulation
           	deltaT = get_deltaT(cell_front);
			act_time += deltaT;
			if (act_time > CA_time ) {
				get_image_of_fire(this->size, this->size, "final");
				return EXIT_SUCCESS;
			}
			

        }

        // Vyhozeni pouzite nastene bunky z fronty
        cell_front.pop_front();

        // Okoli horici bunky
        for(int j = -1; j < 2; j++){
            for(int i = -1; i < 2; i++){
                pom.cell = (array[element.cell.x + i][element.cell.y + j]);

                if (pom.cell.type == NONIGNITED){
                    //fire_expand(CA_Ro(element.cell), deltaT, i, j, pom.cell);
    				switch(i){ // j == y
						case -1:
							switch(j){
								case -1:
                    				fire_expand(CA_R(element.cell, 2.3561), deltaT, i, j, pom.cell);
									break;
								case 0:
                    				fire_expand(CA_R(element.cell, 3.14159), deltaT, i, j, pom.cell);
									break;
								case 1:
                    				fire_expand(CA_R(element.cell, 3.927), deltaT, i, j, pom.cell);
									break;

							}
						case 0:
							switch(j){
								case -1:
                    				fire_expand(CA_R(element.cell, 1.57079), deltaT, i, j, pom.cell);
									break;
								case 1:
                    				fire_expand(CA_R(element.cell, 4.71238), deltaT, i, j, pom.cell);
									break;
								
							}
						case 1:
							switch(j){
								case -1:
                    				fire_expand(CA_R(element.cell, 0.78539), deltaT, i, j, pom.cell);
									break;
								case 0:
                    				fire_expand(CA_R(element.cell, 0), deltaT, i, j, pom.cell);
									break;
								case 1:
                    				fire_expand(CA_R(element.cell, 5.49778), deltaT, i, j, pom.cell);
									break;
								
							}
					}
                    cell_front_nonig.push_back(pom);
                }

                //array[element.cell.x + i][element.cell.y + j] okoli soucasne bunky
                if(pom.cell.type == FIRE){
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
    cell.totalMineralContent = 0.0001;		// St
    cell.effectiveMineralContent = 20.;		// Se

	// test cases
	std::cout.precision(17);
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
	//std::cout << CA_Wn(cell) << std::endl;
	//std::cout << CA_Ro(cell) << std::endl;
	//std::cout << CA_R(cell, 0) << std::endl;

	//std::cout << A(cell) << std::endl;
	//std::cout << B(cell) << std::endl;
	//std::cout << C(cell) << std::endl;
	//std::cout << E(cell) << std::endl;

	//std::cout << CA_IR(cell) << std::endl;


	return;
}

void CA::set_distance(double dist){
    for (int i = 0; i < 8; i++){
        distance[i] = (i == 0 || i == 2 || i == 5 || i == 7) ? hypot(dist, dist) : dist;
        distance_sum += distance[i];
    }
}

// evaluate Ro (Rate of Spread) of every ignited cell 
// and after that evaluate size of next timestep from max. Ro found
double CA::get_deltaT(std::list<cellF> front){
    double ro = 0;
    double pom;
    std::list<cellF> pom_front;

    while (!front.empty()){
        if ((pom = CA_Ro(front.front().cell)) > ro){
            ro = pom;
        }
        pom_front.push_back(front.front());
        front.pop_front();
    }

    //cell_front = pom_front;
    return CA_cell_size / ro;
}

void CA::fire_expand(double ro, double deltaT, int x, int y, Cell &cell){
    switch(x){
        case -1:
            switch(y){
                case -1:
                    cell.fire[0] += ro * deltaT;
                    return;
                case 0:
                    cell.fire[1] += ro * deltaT;
                    return;
                case 1:
                    cell.fire[2] += ro * deltaT;
                    return;

            }
        case 0:
            switch(y){
                case -1:
                    cell.fire[3] += ro * deltaT;
                    return;
                case 1:
                    cell.fire[4] += ro * deltaT;
                    return;
                
            }
        case 1:
            switch(y){
                case -1:
                    cell.fire[5] += ro * deltaT;
                    return;
                case 0:
                    cell.fire[6] += ro * deltaT;
                    return;
                case 1:
                    cell.fire[7] += ro * deltaT;
                    return;
                
            }
    }
}

void CA::cell_ingite(){
    double cell_sum = 0;
    Cell pom_cell;

    while(!cell_front_nonig.empty()){
        pom_cell = cell_front_nonig.front().cell;
        for (int i = 0; i < 8; i++){
            if (pom_cell.fire[i] > distance[i]){
                pom_cell.type = FIRE; 
                break;
            }

            cell_sum += pom_cell.fire[i];
        }

        if (distance_sum / 2 < cell_sum){
            pom_cell.type = FIRE;
        }

        cell_front_nonig.pop_front();
    }
}

void CA::initialize_CA_cells(std::ifstream& file, int width, int height) {
	char R[4], G[4], B[4];

	for (int i=0; i<height; i++) {
		for (int j=0; j<width; j++) {
			file.getline(R, 4, ',');
			file.getline(G, 4, ',');
			file.getline(B, 4, ',');

			if ((atoi(R) < 50) && (atoi(G) < 50) && (atoi(B) < 50)) {
				this->array[i][j].type = NONFLAMMABLE;
			}
			else if (atoi(R) > 128 && (atoi(G) < 128) && (atoi(B) < 128)) {
				this->array[i][j].type = FIRE;
			}
		}
		file.getline(R, 1, '\n');	
	}
}


void CA::get_image_of_fire(int w, int h, char *name) {
	static int i = 0;		// counter for creating unique names of images
	char img_name[256];
	sprintf(img_name, "%d_%s.bmp", i, name);


	FILE *f;
	unsigned char *img = NULL;
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int
	int x, y;
	unsigned char r,g,b;

	img = (unsigned char *)malloc(3*w*h);
	memset(img,0,3*w*h);
	
	for(int i=0; i<w; i++)
	{
	    for(int j=0; j<h; j++)
	    {
	        x=i; y=(h-1)-j;
	        
			switch (this->array[i][j].type) {
				case NONIGNITED:	r=0;   g=255; b=0;	break;
				case FIRE:			r=255; g=0;   b=0;	break;
				case BURNED:		r=50;  g=50;  b=50;	break;
				case NONFLAMMABLE:	r=255; g=255; b=255;break;
			}

			// bmp stores colors as BGR (0,1,2 indices)
	        img[(x+y*w)*3+2] = (unsigned char)(r);
	        img[(x+y*w)*3+1] = (unsigned char)(g);
	        img[(x+y*w)*3+0] = (unsigned char)(b);
	    }
	}
	
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};
	
	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);
	
	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);
	
	f = fopen(img_name,"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<h; i++)
	{
	    fwrite(img+(w*(h-i-1)*3),3,w,f);
	    fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	
	free(img);
	fclose(f);	
	
}

int rndm() {
	return 1 + (rand() % static_cast<int>(100));
}











