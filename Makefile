
test: all_unit_testing.cpp ReadData.cpp SetDeposit.cpp Dividend.cpp Display.cpp Investment.cpp Portfolio.cpp
	@echo "Compiling test program..."
	@g++ -std=c++11 all_unit_testing.cpp ReadData.cpp SetDeposit.cpp Dividend.cpp Portfolio.cpp Display.cpp Investment.cpp -o test
	@echo "Running test..."
	@./test


clean:
	@echo "Cleaning up..."
	@rm -f test

# Target to build everything
all: test
