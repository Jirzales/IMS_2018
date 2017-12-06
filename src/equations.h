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
#define CA_Ro(a)		(CA_rate_of_spread_nowind(a))
#define CA_R(a,ang)		(CA_rate_of_spread_eccentricity(a,ang))
#define CA_PHI(a)		(CA_wind_coefficient(a))

// macro-functions for better readibility in other functions

double A (Cell& cell, double eps=EPS);
double B (Cell& cell);
double C (Cell& cell);
double E (Cell& cell);

// main output functions used mainly to evaluate 'rate of spread' (R) parameter

double CA_rate_of_spread_nowind			(Cell& cell, double eps=EPS);
double CA_rate_of_spread_eccentricity	(Cell& cell, double radians);
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
double CA_wind_coefficient				(Cell& cell);
     
// equations for computing eccentricity of fire/elipse spread shape

// U.S. standard versions for different wind speed in mid-height of 6.1m [m/s]
double CA_LW__USstandard27  (double wnid_speed);	// wind speed less than 12.07 m/s
double CA_LW__USstandard27_2(double wnid_speed);	// wind speed less than 12.07 m/s
double CA_LW__USstandard25  (double wnid_speed);	// wind speed less than 11.176 m/s
double CA_LW__USstandard1   (double wnid_speed);	// wind speed greather than 0.447 m/s

// versions used for different density and/or type of fuels
double CA_LW__dense_forest(double wind_speed);
double CA_LW__open_forest(double wind_speed);
double CA_LW__light_fuels(double wind_speed);

// other LW equations
double CA_LW__McArthur(double wind_speed);
double CA_LW();
double CA_get_eccentricity();

#endif
