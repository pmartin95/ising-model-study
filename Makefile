CC=g++ -std=c++17

SRCS=$(wildcard ./src/*.cpp)
OBJS=$(SRCS:./src/%.cpp=./obj/%.o)
DEP=$(wildcard ./includes/*.hpp)

FLAGS= -I ./includes -lm -O4

main.out: $(OBJS) $(DEP)
	@echo "Linking objects into main.exe..."
	@$(CC) $(INC) -o main.out $(OBJS)

obj/%.o : src/%.cpp $(DEP)
	@echo "Creating $(<:src/%.cpp=%) object file..."
	@$(CC) $(INC) -c -o $@ $<

.PHONY:clean 

clean:
	@rm -rf ./obj/*.o *.exe