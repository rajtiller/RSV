# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -std=c++17

# Targets
TARGETS = main rsv_to_csv_converter benchmark

# Default rule to build all targets
all: $(TARGETS)

# Rule to build main executable
main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

# Rule to build rsv_to_csv_converter executable
rsv_to_csv_converter: rsv_to_csv_converter.cpp
	$(CXX) $(CXXFLAGS) -o rsv_to_csv_converter rsv_to_csv_converter.cpp

benchmark: benchmark.cpp
	$(CXX) $(CXXFLAGS) -o benchmark benchmark.cpp

# Clean rule to remove compiled files
clean:
	rm -f $(TARGETS) *.o

# Phony targets
.PHONY: all clean
