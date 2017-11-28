#ifndef __AUTOMATA_H
#define __AUTOMATA_H

#define DEFAULT_SIZE 200


Cell {
	
}


class CA {
	private:
		int size;
		
		
	public:
		CA(int size=DEFAULT_SIZE);
		~CA();
		void run();
		
		int get_size();

};


#endif
