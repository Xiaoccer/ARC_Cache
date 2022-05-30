BIN:=cache
SRC:=$(wildcard *.cpp)
OBJ:=$(SRC:.cpp=.o)
CXXFALGS:=-std=c++17

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFALGS) -o $@ $^

%.o: %.c
	$(CXX) $(CXXFALGS) -o $@  -c $<


.PHONY: clean test

test: P1 P2 P3 P4 P5 P6 P7 P12

P%: $(BIN)
	@./$(BIN) 1024 		./traces/P$*.lis >> output.txt
	@./$(BIN) 2048 		./traces/P$*.lis >> output.txt
	@./$(BIN) 4096 		./traces/P$*.lis >> output.txt
	@./$(BIN) 8192 		./traces/P$*.lis >> output.txt
	@./$(BIN) 16384 	./traces/P$*.lis >> output.txt
	@./$(BIN) 32768 	./traces/P$*.lis >> output.txt
	@./$(BIN) 65536 	./traces/P$*.lis >> output.txt
	@./$(BIN) 131072 	./traces/P$*.lis >> output.txt
	@./$(BIN) 262144 	./traces/P$*.lis >> output.txt
	@./$(BIN) 524288 	./traces/P$*.lis >> output.txt


clean:
	@rm $(OBJ) $(BIN)
