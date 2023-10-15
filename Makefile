main:
	g++ -O3 -std=c++20 -pthread main.cpp sha256.cpp
load:
	module load gcc-12.1.0-gcc-11.2.0 # This line does not run: module not a shell command
clean:
	rm a.out
