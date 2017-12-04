#ifndef __EQUATIONS_H
#define __EQUATIONS_H

struct Cell;

// libraries
#include <limits>
#include <math.h>
#include <iostream>
#include "automata.h"

// tolerated precission (minimal value for denominator)
#define EPS 0.000000000000001	// 10^(-15)	

bool double_equals(double a, double b, double epsilon = EPS);


/*************** Cell input parameters ****************/
// pravdepodobne tieto makra nevyuzijeme, bolo to tu iba kvoli testovaniu
// bud ich nahradia globalne premenne alebo .. nieco ine
#define CELL_W0		1	// fuel load
#define CELL_DELTA 	1	// fuel depth
#define CELL_SIGMA 	1	// surface-to-volume ratio
#define CELL_h 		1	// fuel heat content
#define CELL_Mf 	1	// fuel moisture content
#define CELL_Mx 	1	// fuel moisturecontent of extinction
#define CELL_Pp 	1	// ovendry particle density
#define CELL_St 	1	// fuel particle total mineral content
#define CELL_Se 	1	// fuel particle effective mineral content
#define CELL_Um 	1	// midflame-height wind speed
#define CELL_SLOPE 	1	// terrain slope


/****************** output functions *******************/

// symbol macros for better more intuitive usage
#define CA_Pb(a) 		(CA_ovendry_bulk_density(a))
#define CA_BETA(a)	 	(CA_packing_ratio(a))
#define CA_BETAop(a) 	(CA_optimum_packing_ratio(a))
#define CA_Xi(a) 		(CA_propagating_flux_ratio(a))
#define CA_GAMMAmax(a) 	(CA_maximum_reaction_velocity(a))
#define CA_GAMMA(a)		(CA_optimum_reaction_velocity(a))
#define CA_Wn(a) 		(CA_net_fuel_loading(a))
#define CA_ETA_M(a)		(CA_moisture_damping_coefficient(a))
#define CA_ETA_S(a)		(CA_mineral_damping_coefficient(a))
#define CA_IR(a)		(CA_reaction_intensity(a))
#define CA_EPSILON(a)	(CA_effective_heating_number(a))
#define CA_Qig(a)		(CA_heat_of_preignition(a))
#define CA_R(a)			(CA_rate_of_spread(a))


// macro-functions for better readibility in other functions

double A (Cell& cell, double eps=EPS);
double B (Cell& cell);
double C (Cell& cell);
double E (Cell& cell);

// main output functions used mainly to evaluate 'rate of spread' (R) parameter

double CA_rate_of_spread				(Cell& cell, double eps=EPS);
double CA_ovendry_bulk_density			(Cell& cell, double eps=EPS);
double CA_packing_ratio					(Cell& cell, double eps=EPS);
double CA_optimum_packing_ratio			(Cell& cell);
double CA_propagating_flux_ratio		(Cell& cell, double eps=EPS); 
double CA_maximum_reaction_velocity		(Cell& cell);
double CA_optimum_reaction_velocity		(Cell& cell);
double CA_net_fuel_loading				(Cell& cell);
double CA_moisture_damping_coefficient	(Cell& cell, double eps=EPS);
double CA_mineral_damping_coefficient	(Cell& cell);
double CA_reaction_intensity			(Cell& cell);
double CA_effective_heating_number		(Cell& cell, double eps=EPS);
double CA_heat_of_preignition			(Cell& cell);
     



#endif
