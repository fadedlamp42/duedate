CXX=g++ -std=c++11

all: build

build: clean
	$(CXX) main.cpp -g -o due

clean:
	rm -f due

install: build
	cp due /usr/local/bin/
