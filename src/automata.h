#ifndef __AUTOMATA_H
#define __AUTOMATA_H

#define CA_DEF_SIZE 200
#define CA_MIN_SIZE 50
#define CA_MAX_SIZE 1000

class Cell {
	
};


class CA {
	private:
		int size;
		
		
	public:
		CA(int size=CA_DEF_SIZE);
		~CA();
		void run();
		
		int get_size();

};


#endif
