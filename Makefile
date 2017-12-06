NAME = simulator
CPP = g++
STD = -std=c++11
CXXFLAGS = $(STD) -pedantic -Wall -Wextra -g
ARGS = 

.PHONY: clean all run zip tests doc

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)


all: $(NAME)
	@echo Compiled successfully!

$(NAME): $(OBJS)
	$(CPP) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp %.h
	$(CPP) $(CXXFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f *.o && cd ./src/ && rm -f *.o
	rm -f $(NAME)
	rm -f tests/*.csv

zip:
	make clean
	zip -r 07_xzales12_xmosko04.zip ./

tests: 
	python ./tests/image_to_csv.py $(ARGS)


# show help page of Makefile
help:
	@echo ""
	@echo "-------------------- makefile echo --------------------"
	@echo "make:        Compile simulator"
	@echo "make run     Compile and runs simulator"	
	@echo "make all     Compile simulator"
	@echo "make clean   Remove all obj and csv files + executable file"
	@echo "make zip     Zip all files and directories in actual directory"
	@echo "make help    Shows this help"
	@echo "make tests   Python script for converting image colors into csv field"

