#cplex addresses!!!!
#folder include
#INCCPLEX= -I/opt/ibm/ILOG/CPLEX_Studio1251/cplex/include/
#folder lib
#LIBCPLEX= -L/opt/ibm/ILOG/CPLEX_Studio1251/cplex/lib/x86-64_sles10_4.1/static_pic/ -m64 -lcplex -lm -lpthread
#folder concert
#CONCPLEX= -I/opt/ibm/ILOG/CPLEX_Studio1251/concert/include/ 


#folder include
INCCPLEX= -I/opt/ibm/ILOG/CPLEX_Studio127/cplex/include/
#folder lib
LIBCPLEX= -L/opt/ibm/ILOG/CPLEX_Studio127/cplex/lib/x86-64_linux/static_pic/ -m64 -lcplex -lm -lpthread
#folder concert
CONCPLEX= -I/opt/ibm/ILOG/CPLEX_Studio127/concert/include/

all: tools solver main

tools: 
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Set.cpp -o lib/set.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Graph.cpp -o lib/graph.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/tools/Timer.cpp -o lib/time.o
		
solver: 
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/solver/Solver.cpp -o lib/solver.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/NewRepresentative.cpp -o lib/newrepr.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/ImpRepresentative.cpp -o lib/repr.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/Heuristic.cpp -o lib/heu.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/BasicHeuristic.cpp -o lib/bheu.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/ImpRepresentativeRelax.cpp -o lib/repr_relax.o
	g++ -c -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) src/solver/TrivialHeuristic.cpp -o lib/theu.o
	
main: 
	g++ -c -Wextra -ansi -O3 -funroll-all-loops src/main/Reader.cpp -o lib/reader.o
	g++ -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) lib/time.o lib/set.o lib/graph.o lib/reader.o lib/solver.o lib/repr.o lib/newrepr.o lib/heu.o lib/bheu.o lib/repr_relax.o lib/theu.o src/main/Main.cpp -o bin/main $(LIBCPLEX)
	g++ -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) lib/time.o lib/set.o lib/graph.o lib/reader.o lib/solver.o lib/repr.o lib/heu.o lib/bheu.o lib/repr_relax.o lib/theu.o src/main/main_porta.cpp -o bin/main_porta $(LIBCPLEX)
	g++ -Wextra -ansi -O3 -funroll-all-loops -DIL_STD $(INCCPLEX) $(CONCPLEX) lib/time.o lib/set.o lib/graph.o lib/reader.o lib/solver.o lib/repr.o lib/heu.o lib/bheu.o lib/repr_relax.o lib/theu.o src/main/Main_heu.cpp -o bin/main_heu $(LIBCPLEX)