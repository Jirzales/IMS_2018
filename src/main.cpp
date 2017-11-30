#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <getopt.h>

#include "automata.h"

using namespace std;

/**** global variables *****/
int CA_size = CA_DEF_SIZE;  // Width/height of Cellular automaton's lattice


// function prototypes
void print_help( void );


int main(int argc, char *argv[]) {
    
    /******************** Arguments processing ********************/    
    int opt_index, 
        time,
        c,
        _errno,
        fire_end = 0;
    char *strtol_err = nullptr;

    while(1) {
        
        static struct option long_options[] = {
            { "help", no_argument,       0, 'h'},
            { "size", required_argument, 0, 's'},
            { "time", required_argument, 0, 't'},
            {0, 0, 0, 0}
        };  
        
        c = getopt_long(argc, argv, "hs:t:", long_options, &opt_index);
        
        if (c == -1)
            break;

        switch(c) {
            case 'h':
                print_help();
                return EXIT_SUCCESS;

            case 's':
                CA_size = strtol(optarg, &strtol_err, 0);
                _errno = errno;

                if (*strtol_err != '\0')
                    ERROR("Size must be integer",1);
                if (CA_size < CA_MIN_SIZE || CA_size > CA_MAX_SIZE || _errno == ERANGE)
                    ERROR("Wrong size!",1);

                break;

            case 't':
                time = strtol(optarg, &strtol_err, 10);
                if (*strtol_err != '\0') {
                    ERROR("Time must be integer",1);
                }
                break;

            case '?':
            default:
                print_help();
                return 1;
        }
    }

    CA *automata = new CA(CA_size); 
    fire_end = automata->run(time, -1);
    if (fire_end != 0){
        cout << "The fire burned out before the time limit. Time: " << fire_end << endl;
    }
    
    return EXIT_SUCCESS;
}


void print_help() {
    std::cout << "usage: simulator [-h] [-s <CA size>] [-t <CA time>]\n";
}




