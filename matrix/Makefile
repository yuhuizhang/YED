CPP = g++
CFLAGS = -Wall -g
OMP = #-fopenmp

BOOST_ROOT = ../../../boost_1_54_0 # !! relative location of boost file
#GSL_ROOT = /usr/local/include
YED_ROOT = ../

objects = countSize.o tool.o diaME.o dME.o tME.o dMETool.o tMETool.o publicFuncs.o

all : $(objects)
.PHONY : all

countSize.o : countSize.cpp matrix.h
	$(CPP) $(CFLAGS) $(OMP) -I$(BOOST_ROOT) -c countSize.cpp

tool.o : tool.cpp matrix.h
	$(CPP) $(CFLAGS) -c tool.cpp

diaME.o : diaME.cpp matrix.h
	$(CPP) $(CFLAGS) -c diaME.cpp

dME.o : dME.cpp matrix.h
	$(CPP) $(CFLAGS) -c dME.cpp

tME.o : tME.cpp matrix.h
	$(CPP) $(CFLAGS) -I$(BOOST_ROOT) -c tME.cpp

dMETool.o : dMETool.cpp matrix.h
	$(CPP) $(CFLAGS) -c dMETool.cpp

tMETool.o : tMETool.cpp matrix.h
	$(CPP) $(CFLAGS) -c tMETool.cpp

publicFuncs.o : publicFuncs.cpp matrix.h
	$(CPP) $(CFLAGS) $(OMP) -I$(BOOST_ROOT) -I$(YED_ROOT) -c publicFuncs.cpp

.PHONY : clean
clean :
	rm $(objects)