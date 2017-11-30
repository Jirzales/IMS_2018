#ifndef __AUTOMATA_H
#define __AUTOMATA_H

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <list>


#define CA_DEF_SIZE 200
#define CA_MIN_SIZE 50
#define CA_MAX_SIZE 1000

/*  Macro pro chybova hlaseni
*   @param Text chybonve hlasky
*   @param Navratovy kod chyby
*/
#define ERROR(msg, ret) do {                            \
        fprintf(stderr, "Aborting at %s:%d in %s...\n", \
                __FILE__, __LINE__, __func__);          \
        fprintf(stderr, "ERROR: %s", msg);              \
        perror(" ");                                    \
        exit(ret);                                      \
    } while (0);

typedef enum{
    NONIGNITED, 
    FIRE, 
    BURNED, 
    NONFLAMMABLE 
} cellType;

typedef struct{
    int x;
    int y;
    cellType type;
    double fuelLoad;
    double fuelDepth;
    double fuelHeat;
    double fuelMoisture;
    double fuelMoistExt;
    double ovendry;
    double fuelMineralTot;
    double fuelMineralEff;
    double windSpeed;
    double terain;
} Cell;

typedef struct{
    int id;
    Cell* cell; 
} cellF;

class CA {
    private:
        int size;
        std::list<cellF>cell_front;
        Cell** array;

        void addToFront();
        
    public:
        CA(int size=CA_DEF_SIZE);
        ~CA();

        int run(int time, int exportTime);
        int get_size();

};


#endif
