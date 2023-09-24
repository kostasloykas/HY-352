
run: clean library compile
	@./a.out;

compile: library JSONlang.h
	@g++ json.cpp library.o -g;
	@echo "Compile Done";

library: library.h library.cpp
	@g++ -c library.cpp -o library.o;


clean:
	-@rm -rf a.out;
	-@rm -rf library.o;
	@echo "Clean Done";