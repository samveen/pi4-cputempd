.PHONY: all clean

all:pi4-cputempd
	echo "Do something"

pi4-cputempd: main.o
	gcc -o $@ $^ 

clean:
	rm -f *.o pi4-cputempd
