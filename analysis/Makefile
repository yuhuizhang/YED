CPP = g++
CFLAGS = -Wall -g

objects = nameFileTool.o input.o compare.o newForm.o output.o

all : $(objects)
.PHONY : all

nameFileTool.o : nameFileTool.cpp analysis.h
	$(CPP) $(CFLAGS) -c nameFileTool.cpp

input.o : input.cpp analysis.h
	$(CPP) $(CFLAGS) -c input.cpp

compare.o : compare.cpp analysis.h
	$(CPP) $(CFLAGS) -c compare.cpp

newForm.o : newForm.cpp analysis.h
	$(CPP) $(CFLAGS) -c newForm.cpp

output.o : output.cpp analysis.h
	$(CPP) $(CFLAGS) -c output.cpp

.PHONY : clean
clean :
	rm $(objects)