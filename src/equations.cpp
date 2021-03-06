#include "equations.h"

extern double CA_eccentricity;
extern double CA_wind_speed;
extern double CA_wind_angle;


/**
 * This tree show dependencies of all formulas, equations
 * and constants. All equations and parameters are represented through
 * their symbols used in the program
 *
 *
 * Legend:
 *	- All greek symbol names are uppercase (for brevity)
 *  - All known input parameters (CA Cells attributes) are bounded with square brackets
 *  - other symbols represent equations (represented by functions) that need to be evaluated
 * Meaning of Symbols:
 *	- Ro:		rate of spread (of fire)
 *  - Qig:		heat of preignition
 *  - EPSILON:	effective heating number
 *  - Pb:		ovendry bulk density
 *  - XI:		propagating flux ratio
 *  - BETA:		packing ratio
 *  - BETAop:	optimum packing ratio
 *  - Ir:		reaction intensity
 *  - ETAs:		mineral damping coefficient
 *  - ETAm:		moisture damping coefficient
 *  - Wn:		net fuel loading
 *  - GAMMA:	optimum reaction velocity
 *  - GAMMAmax:	maximum reaction velocity
 *
 * Input parameters of each Cell (known values):
 *  - [Mf]:		fuel moisture content
 *  - [Mx]:		fuel moisture content of extiction
 *  - [SIGMA]:	surface-to-volume ratio
 *  - [W0]:		fuel load
 *  - [DELTA]:	fuel depth
 *  - [Pp]:		ovendry particle density
 *  - [h]:		fuel heat content
 *  - [Se]:		fuel particle total mineral content
 *  - [St]:		fuel particle effective mineral content
 *
 *  Tree of dependencies between equations leading to single result 'Ro' (Rate of Spread):
 *
 * Ro-
 *   |___Qig___[Mf]
 *   |
 *   |
 *   |___EPSILON___[SIGMA] 
 *   |
 *   |
 *   |___Pb___[W0]
 *   |     |
 *   |     |__[DELTA]
 *   |
 *   |
 *   |___XI___[DELTA]
 *   |    |
 *   |    |___BETA___[Pp]
 *   |           |
 *   |           |___Pb___[W0]
 *   |                |
 *   |                |___[DELTA]
 *   |
 *   |
 *   |___Ir___[h]
 *        |
 *        |___ETAs___[Se]
 *        |
 *        |___ETAm___[Mf]
 *        |      |
 *        |      |___[Mx]
 *        |
 *        |___Wn___[W0]
 *        |    |
 *        |    |___[St]
 *        |
 *        |___GAMMA___GAMMAmax___[SIGMA]
 *                |
 *                |___BETAop___[SIGMA]
 *                |
 *                |___BETA___[Pp]
 *                       |
 *                       |___Pb___[W0]
 *                            |
 *                            |___[DELTA]
 *
 */


bool double_equals(double a, double b, double epsilon)
{
    return std::fabs(a - b) < epsilon;
}
#define CHECK_MIN(a,eps)	(double)(double_equals(a, 0, eps)? eps: a)



// auxilarry symbols/functions for better readibility of other equations that contain them

double A ( Cell& cell, double eps) {
	return ( 1 / CHECK_MIN((4.239 * pow(cell.surfaceToVolume, 0.1)) - 7.27, eps) );	
}
double B ( Cell& cell ) {
	return (0.0133 * pow(cell.surfaceToVolume, 0.54));
}
double C ( Cell& cell ) {
	return (7.47 * exp(-0.0693 * pow(cell.surfaceToVolume, 0.55)));
}
double E ( Cell& cell ) {
	return (0.715 * exp(-1.079 * pow(10, -4) * cell.surfaceToVolume));
}


/********************************************  main output functions used mainly to evaluate 'rate of spread' (R) parameter ************************************************/

double CA_rate_of_spread_eccentricity(Cell& cell, double radians) {
	//return CA_Ro(cell) * ((1 - CA_eccentricity) / (1 - (CA_eccentricity * cos(fabs(radians - CA_wind_angle)))));
	return (CA_Ro(cell) * (1 + CA_wind_coefficient(cell))) * ((1 - CA_eccentricity) / (1 - (CA_eccentricity * cos(fabs(radians - CA_wind_angle)))));
}

double CA_rate_of_spread_nowind(Cell& cell, double eps) {
	return ( (CA_IR(cell) * CA_Xi(cell)) * ((CA_wind_speed==0)? 1: (1 + CA_PHI(cell)))/ 
			CHECK_MIN(CA_Pb(cell) * CA_EPSILON(cell) * CA_Qig(cell), eps) );
}

double CA_wind_coefficient(Cell& cell) {
	return (C(cell) * pow(CA_wind_speed, B(cell)) * pow(CA_BETA(cell) / CA_BETAop(cell), -E(cell)) );
}

double CA_ovendry_bulk_density(Cell& cell, double eps) {
	return ( cell.load / CHECK_MIN(cell.depth, eps) );
}

double CA_packing_ratio(Cell& cell, double eps ) {
	return ( CA_Pb(cell) / CHECK_MIN(cell.ovendryDensity, eps) );
}

double CA_optimum_packing_ratio(Cell& cell) {
	return ( 3.348 * pow(cell.surfaceToVolume, -0.8189) );
}

double CA_propagating_flux_ratio(Cell& cell, double eps) {
	return ( exp((0.792 + (0.376  * pow(cell.surfaceToVolume, 0.5))) * (CA_BETA(cell) + 0.1)) / 
			CHECK_MIN(192. + (0.0791 * cell.surfaceToVolume), eps) );
}

double CA_maximum_reaction_velocity(Cell& cell) {
	return ( (pow(cell.surfaceToVolume, 1.5)) / (1171.27 + (3.564 * pow(cell.surfaceToVolume, 1.5))) );
}

double CA_optimum_reaction_velocity(Cell& cell) {
	return ( CA_GAMMAmax(cell) * pow((CA_BETA(cell) / CA_BETAop(cell)), A(cell)) * 
				exp(A(cell) * (1 - (CA_BETA(cell) / CA_BETAop(cell)))) );
}

double CA_net_fuel_loading(Cell& cell) {
	return ( cell.load / (1 + cell.totalMineralContent) );
}

double CA_moisture_damping_coefficient(Cell& cell, double eps) {
	// neskor vymazat pretoze sa zbytocne vola v kazdom cykle na tie iste bunky... kontrolovat prednostne
	cell.moistureContentOfExtinction = CHECK_MIN(cell.moistureContentOfExtinction, eps);
	return ( 1 - 
			(2.59 * (cell.moistureContent / cell.moistureContentOfExtinction)) + 
			(5.11 * pow((cell.moistureContent / cell.moistureContentOfExtinction), 2)) - 
			(3.52 * pow(cell.moistureContent / cell.moistureContentOfExtinction, 3)) );
}

double CA_mineral_damping_coefficient(Cell& cell) {
	return ( 0.174 * pow(cell.effectiveMineralContent, -0.19) );
}

double CA_reaction_intensity(Cell& cell) {
	return ( CA_GAMMA(cell) * CA_Wn(cell) * CA_ETA_M(cell) * CA_ETA_S(cell) * cell.heatContent );
}

double CA_effective_heating_number(Cell& cell, double eps) {
	return CHECK_MIN(exp((-4527.56) / cell.surfaceToVolume), eps);
}

double CA_heat_of_preignition(Cell& cell) {
	return ( 522. + (2332. * cell.moistureContent) );
}

/****************************************************** Equations for computing Length-to-Width ratio of ellipse ********************************************************/

// U.S. standard versions for different wind speed in mid-height of 6.1m [m/s]

double CA_LW__USstandard27(double wind_speed) {		// less than 12.07 m/s
	return 1.0 + (0.00452 * pow(wind_speed / 0.277777, 2.154));
}
double CA_LW__USstandard27_2(double wind_speed) {	// less than 12.07 m/s
	return 0.5 + 0.5 * exp(0.20862 * wind_speed);
}
double CA_LW__USstandard25(double wind_speed) {		// less than 11.176 m/s
	return exp(0.11626 * pow(wind_speed / 0.44704, 0.86559));
}
double CA_LW__USstandard1(double wind_speed) {		// greater than 0.447 m/s
	return 1.46 * pow(wind_speed / 0.44704, 0.464);
}

// versions used for different density and/or type of fuels

double CA_LW__dense_forest(double wind_speed) {		// used for dense forest
	return (0.936 * exp(0.04464 * wind_speed) + 0.461 * exp(-0.02693 * wind_speed));
}
double CA_LW__open_forest(double wind_speed) {		// used for open forests
	return (0.936 * exp(0.007 * wind_speed) + 0.461 * exp(-0.04032 * wind_speed));
}
double CA_LW_light_fuels(double wind_speed) {		// used for grass, low/medium slash, leafless hardwood stands
	return (0.936 * exp(0.1607 * wind_speed) + 0.461 * exp(-0.05364 * wind_speed));
}

// other equations gained through experiments
double CA_LW__McArthur(double wind_speed) {
	return 1.1 * pow(wind_speed / 0.277777, 0.464);
}



// function which automatically choose best function for evaluating length-to-width
// based upon all relevant CA parameters
double CA_LW() {
	return CA_LW__open_forest (CA_wind_speed);		// used for open forests

	if (CA_wind_speed != 0) {
		// use universal equation for winds faster than 12.07 m/s
		if (CA_wind_speed > 11.176 )
			return CA_LW__USstandard1(CA_wind_speed);
		else if (CA_wind_speed > 0.447 )
			return CA_LW__USstandard1(CA_wind_speed);
		else 
			return CA_LW__McArthur(CA_wind_speed);
	}

	// no-wind conditions 
	else {
		// you can set there any value from above US standard values depending on fuel type
		if(1) {
			return CA_LW__McArthur(CA_wind_speed);
		}
	}
}

// return eccentricity
double CA_get_eccentricity() {
	return sqrt(1 - (1 / pow(CA_LW(), 2)));
}









