LIBS=-lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lXinerama -lXcursor -ldl -lrt -lglfw -lGLEW
CFLAGS=-std=c++11 -Wall -g


run.out: main.o log.o shader.o shape.o ColouredShape.o
	g++ main.o log.o shader.o shape.o ColouredShape.o -o run.out $(LIBS) $(CFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(CFLAGS) -o main.o
		
log.o: log.h log.cpp
	g++ -c log.cpp $(CFLAGS) -o log.o

shader.o: shader.h shader.cpp
	g++ -c shader.cpp -o shader.o $(CFLAGS) $(LIBS)

shape.o: shape.h shape.cpp
	g++ -c shape.cpp -o shape.o $(CFLAGS) $(LIBS)
	
ColouredShape.o: ColouredShape.h ColouredShape.cpp
	g++ -c ColouredShape.cpp -o ColouredShape.o $(CFLAGS) $(LIBS)
	
clean:
	rm -f *.o
	rm -f *~
