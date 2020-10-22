CXX=g++

all: build

build: clean
	$(CXX) main.cpp -o due

clean:
	rm -f due

install: build
	cp due /usr/local/bin/
