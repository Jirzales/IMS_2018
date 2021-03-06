#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <random>
#include <getopt.h>

#include "automata.h"
#include "equations.h"

using namespace std;

/**** global variables *****/
int CA_size = CA_DEF_SIZE,				// Width/height of Cellular automaton's lattice
	CA_cell_size = CA_DEF_CELL_SIZE,	// automaton's cell size [m]
    CA_time = CA_DEF_TIME,				// simulation time [min]
	CA_fuel_prob = CA_DEF_FUEL_PROB;	// probability [0-100%] that celltype of each cell will be NONIGNITED
double CA_wind_speed,					// wind speed [m/s]
       CA_wind_angle,					// angle of wind [deg]
       CA_eccentricity;					// eccentricity of elliptic shape of fire spread

// function prototypes
void print_help( void );
double angles_to_radians(double angles);


/********************************************************************* MAIN FUNCTION **********************************************************************/

int main(int argc, char *argv[]) {
    
    /******************** Arguments processing ********************/    
    int opt_index, 
        c,
        _errno,
        fire_end = 0;
    char *strtol_err = nullptr,
	 	 *strtk = nullptr,
		 *csv = nullptr;

    while(1) {
        
        static struct option long_options[] = {
            { "help" , no_argument,       0, 'h'},
            { "size" , required_argument, 0, 's'},
            { "cell" , required_argument, 0, 'c'},
            { "time" , required_argument, 0, 't'},
            { "fuel" , required_argument, 0, 'f'},
            { "wind" , required_argument, 0, 'w'},
            { "image", required_argument, 0, 'i'},
            {0, 0, 0, 0}
        };  
        
        c = getopt_long(argc, argv, "hs:t:w:x:c:f:i:", long_options, &opt_index);
        
        if (c == -1)
            break;

        switch(c) {
            case 'h':	// --help
                print_help();
                return EXIT_SUCCESS;

            case 'i':	// --size
                csv = optarg;
				
				break;

            case 's':	// --size
                CA_size = strtol(optarg, &strtol_err, 0);
                _errno = errno;

                if (*strtol_err != '\0')
                    ERROR("Size must be integer!\n",1);
                if (CA_size < CA_MIN_SIZE || CA_size > CA_MAX_SIZE || _errno == ERANGE)
                    ERROR("Wrong size!",1);

				break;
	
            case 'c':	// --cell
                CA_cell_size = strtol(optarg, &strtol_err, 0);
                _errno = errno;

                if (*strtol_err != '\0')
                    ERROR("Size must be integer!\n",1);
                if (CA_cell_size < CELL_MIN_SIZE || CA_cell_size > CELL_MAX_SIZE || _errno == ERANGE)
                    ERROR("Wrong CA size format/number!",1);

				break;

            case 'f':	// --fuel
                CA_fuel_prob = strtol(optarg, &strtol_err, 10);
                _errno = errno;

                if (*strtol_err != '\0') {
                    ERROR("Time must be integer!\n",1);
                }
                if (CA_fuel_prob < 0 || CA_fuel_prob > 100 ||_errno == ERANGE)
                    ERROR("Wrong range or format for fuel probability!",1);

				break;

            case 't':	// --time
                CA_time = strtol(optarg, &strtol_err, 10);
                _errno = errno;

                if (*strtol_err != '\0') {
                    ERROR("Time must be integer!\n",1);
                }
                if (CA_time <= 0 || _errno == ERANGE)
                    ERROR("Wrong simulation time number!",1);

				break;

            case 'w':	// --wind
				strtk = strtok(optarg, ",");

				if (strtk == NULL)
					ERROR("Wring format for wind size!\n", 1);
	 
				CA_wind_speed = strtol(strtk, &strtol_err, 10);
               	_errno = errno;
				if (*strtol_err != '\0') 
					ERROR("Wind speed in meters per second expected!\n",1);
				
				if ((strtk = strtok(NULL, ",")) == NULL )
					ERROR("You forgot to specify the angle of wind!\n",1);
				if (strtok(NULL, ",") != NULL)
					ERROR("option -w contains too much values!\n",1);
					
				CA_wind_angle = strtol(strtk, &strtol_err, 10);
               	_errno = errno;
				if (*strtol_err != '\0') 
					ERROR("Angle in radians expected!\n",1);

				CA_wind_angle = angles_to_radians(CA_wind_angle);
				CA_eccentricity = CA_get_eccentricity();
					
				break;
            
		case '?':
		default:
			print_help();
			return 1;
        }
    }

    CA *automata = new CA(csv? csv: NULL); 
	automata->get_image_of_fire(CA_size, CA_size, "sim");
   
	fire_end = automata->run();
	if (fire_end != 0){
        cout << "The fire burned out before the time limit. Time: " << fire_end << endl;
    }

	automata->test_function();

    delete automata;
    return EXIT_SUCCESS;
}


void print_help() {
    std::cout << "usage: simulator [-h] [-s <CA size>] [-t <CA time(min)>] [-w <speed(m/s),angle(rad)>] [-c <size(m)>] [-f <0, 100>] [-i <csv_name>]\n";
}


double angles_to_radians(double angles) {
	return (3.1415927 * angles) / 180.;	
}






