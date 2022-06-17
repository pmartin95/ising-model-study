CC=g++ -std=c++17

SRCS=$(wildcard ./src/*.cpp)
OBJS=$(SRCS:./src/%.cpp=./obj/%.o)
DEP=$(wildcard ./includes/*.hpp)

FLAGS= -I./include -lm -O4

main.out: $(OBJS) $(DEP)
	@echo "Linking objects into main.exe..."
	@$(CC) $(FLAGS) -o main.out $(OBJS)

obj/%.o : src/%.cpp $(DEP)
	@echo "Creating $(<:src/%.cpp=%) object file..."
	@$(CC) $(FLAGS) -c -o $@ $<

.PHONY:clean 

clean:
	@rm -rf ./obj/*.o *.exe