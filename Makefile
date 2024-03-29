SRC_DIR = ./src
INC_DIR = ./include
BIN_DIR = ./bin
OBJ = $(addprefix $(BIN_DIR)/, InputGenerator.o Job.o Simulator.o \
			       ComputeNode.o ComputeCluster.o FcfsScheduler.o \
			       FFDScheduler.o )
CXX = g++ 
CFLAGS = -I $(INC_DIR)
DEPS = $(INC_DIR)/%.h

all: run_simulator

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEPS) 
	mkdir -p $(BIN_DIR)
	$(CXX) -c -g -o $@ $< $(CFLAGS)	

run_simulator: $(OBJ)
	$(CXX) -Wall -g -o run_simulator run_simulator.cpp $(OBJ) $(CFLAGS)

clean: 
	rm -f -r run_simulator
	rm -f -r $(BIN_DIR)
