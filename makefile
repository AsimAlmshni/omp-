CC=g++ -fopenmp
CFLAGS= -Wall

OBJ = parallel.o serial.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -O3 -o $@ $^
test1:
	time ./serial oimage.txt mask.txt of.txt

test2:
	time ./parallel oimage.txt mask.txt of.txt 10

test3:
	time ./parallel oimage.txt mask.txt of.txt 20

test4:
	time ./parallel oimage.txt mask.txt of.txt 15

test5:
	time ./parallel oimage.txt mask.txt of.txt 25

test6:
	time ./parallel oimage.txt mask.txt of.txt 30

test7:
	time ./parallel oimage.txt mask.txt of.txt 40

test8:
	time ./parallel oimage.txt mask.txt of.txt 50
clean:
	rm -f *.o *~ core

