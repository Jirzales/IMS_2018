#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <getopt.h>

#include "automata.h"

using namespace std;

/**** global variables *****/
int CA_size = CA_DEF_SIZE;	// Width/height of Cellular automaton's lattice


// function prototypes
void print_help( void );


int main(int argc, char *argv[]) {


	/******************** Arguments processing ********************/	
	int opt_index,
		c,
		_errno;
	char *strtol_err = nullptr;

	while(1) {
		
		static struct option long_options[] = {
			{ "help", no_argument,       0, 'h'},
			{ "size", required_argument, 0, 's'},
			{0, 0, 0, 0}
		};	
		
		c = getopt_long(argc, argv, "hs:", long_options, &opt_index);
		
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
					cout << "error";
				if (CA_size <= CA_MIN_SIZE || CA_size >= CA_MAX_SIZE || _errno == ERANGE)
					cout << "error";

				break;

			case '?':
			default:
				print_help();
				return 1;
		}
	}






	CA(CA_size);
	
	
	
	
	
	
	
	return EXIT_SUCCESS;
}


void print_help() {
	std::cout << "usage: simulator [-h] [-s <CA size>]\n";
}




