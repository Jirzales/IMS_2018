#ifndef __AUTOMATA_H
#define __AUTOMATA_H

#include <cstdio>
#include <iostream>
#include <random>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <list>

#include "equations.h"

#define CA_DEF_SIZE 200     // default number of automaton's rows and columns
#define CA_DEF_TIME 1000    // default simulation time [min]
#define CA_MIN_SIZE 50      // MINimal number of cells in row/col
#define CA_MAX_SIZE 1000    // MAXimal number of cells in row/col
#define CA_DEF_CELL_SIZE 10 // default size of each cell's side
#define CA_DEF_FUEL_PROB 50	// default size of each cell's side
#define CELL_MIN_SIZE 1		// minimal cell size [m]
#define CELL_MAX_SIZE 100	// maximal cell size [m]

#define RO_TR 0.02425
#define RO_ZV 0.01865
#define RO_HL 0.012095

/*  Macro pro chybova hlaseni
*   @param Text chybove hlasky
*   @param Navratovy kod chyby
*/
#define ERROR(msg, ret) do {                            \
        fprintf(stderr, "Aborting at %s:%d in %s...\n", \
                __FILE__, __LINE__, __func__);          \
        fprintf(stderr, "ERROR: %s", msg);              \
        perror(" ");                                    \
        exit(ret);                                      \
    } while (0)

typedef enum{
    NONIGNITED, 
    FIRE, 
    BURNED, 
    NONFLAMMABLE 
} cellType;

typedef struct Cell{
    int x;
    int y;
    cellType type;
    double load;
    double depth;
    double surfaceToVolume;
    double heatContent;
    double moistureContent;
    double moistureContentOfExtinction;
    double ovendryDensity;
    double totalMineralContent;
    double effectiveMineralContent;
    double fire[8] = {0,};
} Cell;

typedef struct {
    int id;
    Cell cell; 
} cellF;

class CA {
    private:
        int size;
        std::list<cellF>cell_front; // Horici bunky
        std::list<cellF>cell_front_nonig;   // Bunky pro mozne zapaleni
        double distance[8];
        double distance_sum = 0;
        Cell** array;

        void set_distance(double dist);
        double get_deltaT(std::list<cellF> front);
        void fire_expand(Cell& from_cell, double deltaT, int x, int y, Cell& to_cell);
        void cell_ignite();
		void initialize_CA_cells(std::ifstream& file, int width, int height);

    public:
        CA(char *csv);
		CA();
        ~CA();

		void get_image_of_fire(int w, int h, char *name); 
        void check_neighbours(cellF& cellf, int step, double deltaT);
		int run();
        int get_size();
        
        // test functions
        void test_function();
        
};

int rndm();



#endif
