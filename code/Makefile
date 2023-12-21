EXE=$(addsuffix .exe, $(basename $(wildcard *.cpp)))

all : $(EXE)

%.exe : %.cpp *.h
	g++ -O3 $< -o $@

clean:
	rm -f *.exe 

.PHONY: all clean
