SRC_DIR = ./src
INC_DIR = ./include
#LIB_DIR = ./lib
BIN_DIR = ./bin
OBJ = $(addprefix $(BIN_DIR)/, InputGenerator.o Simulator.o)
CXX = g++
CFLAGS = -I $(INC_DIR)
DEPS = $(INC_DIR)/%.h

all: run_simulator

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEPS) 
	mkdir -p $(BIN_DIR)
	$(CXX) -c -o $@ $< $(CFLAGS)	

#run_simulator: $(OBJ)
#	mkdir -p $(LIB_DIR)
#	$(CXX) -Wall -o $(LIB_DIR)/hello.so $(BIN_DIR)/hello.o $(CFLAGS) -shared

run_simulator: $(OBJ)
	$(CXX) -Wall -o run_simulator run_simulator.cpp $(OBJ) $(CFLAGS)




clean: 
	rm -f -r run_simulator
	#rm -f -r $(LIB_DIR)
	rm -f -r $(BIN_DIR)
