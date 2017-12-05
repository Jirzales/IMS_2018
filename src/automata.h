#ifndef __AUTOMATA_H
#define __AUTOMATA_H

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <list>

#include "equations.h"

#define CA_DEF_SIZE 200     // default number of automaton's rows and columns
#define CA_DEF_TIME 1000    // default simulation time [min]
#define CA_MIN_SIZE 50      // MINimal number of cells in row/col
#define CA_MAX_SIZE 1000    // MAXimal number of cells in row/col
#define CA_DEF_CELL_SIZE 10 // default size of each cell's side


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
    double windSpeed;
    double slope;
    double fire[8] = {0,};
} Cell;

typedef struct{
    int id;
    Cell* cell; 
} cellF;

class CA {
    private:
        int size;
        std::list<cellF>cell_front; // Horici bunky
        std::list<cellF>cell_front_nonig;   // Bunky pro mozne zapaleni
        double distance[8];
        Cell** array;

        void set_distance(double dist);
        double get_deltaT(std::list<cellF> front);
        void fire_expand(double ro, double deltaT, int x, int y, Cell& cell);
        
    public:
        CA(int size, double cell_size);
        ~CA();

        int run(int time, int exportTime);
        int get_size();
        
        // test functions
        void test_function();
        
};





#endif
