#build project 3
EXEC = CS216PA3
#list the compile options
OBJECTS = Graph.o WordLadder.o CS216PA3main.o 
HEADERS = Graph.h WordLadder.h
$(EXEC): $(OBJECTS)
		g++ $^ -o $@
#only rebuilds object files whose *.cpp have been updated since last build
%.o: %.cpp $(HEADERS)
		g++ -c $< -o $@
#to delete object files, type "make clean"
clean: 
	rm -i *.o $(EXEC)

