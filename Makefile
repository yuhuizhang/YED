CPP = g++
CFLAGS = -Wall -g

BOOST_ROOT = ../../boost_1_54_0 # !! relative location of the boost file

OMP = #-fopenmp

BASIS_ROOT = basis
ITR_ROOT = interaction
MATRIX_ROOT = matrix
ED_ROOT = ED
ANALYSIS_ROOT = analysis

#GSL_ROOT = /usr/local/include
#ALL_GSL_LIBS = -lgsl -lgslcblas -lm
# !! in the following, whenever you see .a file, it means the Makefile tries to find the location of a library file. This Makefile comes from my code in cluster, where I put a lot of library files in lib, bin or binn directories. But in your laptop the locations should be very different. In the email, I attached this Makefile running in my laptop, you may find the related .a files based on that Makefile. If you cannot find it, google it to see usually where a certain .a file usually installed.
ALL_GSL_LIBS = -lgsl -lgslcblas -lm

SUPERLU_LIB  = /usr/lib/libsuperlu.a
ARPACK_LIB   = /usr/lib/libarpack.a
LAPACK_LIB   = -llapack
BLAS_LIB     = -lblas
FORTRAN_LIBS = -lgfortran -lgfortranbegin -lnsl 
ALL_ED_LIBS  = $(ARPACK_LIB) $(LAPACK_LIB) \
               $(BLAS_LIB) $(FORTRAN_LIBS) 

objects = $(BASIS_ROOT)/constr.o $(BASIS_ROOT)/tool.o $(BASIS_ROOT)/dGen.o $(BASIS_ROOT)/tGen.o $(BASIS_ROOT)/publicFuncs.o \
	$(ITR_ROOT)/vmIntegrand.o $(ITR_ROOT)/dItr.o $(ITR_ROOT)/tItr.o $(ITR_ROOT)/publicFuncs.o \
	$(MATRIX_ROOT)/countSize.o $(MATRIX_ROOT)/tool.o $(MATRIX_ROOT)/diaME.o $(MATRIX_ROOT)/dME.o $(MATRIX_ROOT)/tME.o $(MATRIX_ROOT)/tMETool.o $(MATRIX_ROOT)/dMETool.o $(MATRIX_ROOT)/publicFuncs.o \
	$(ED_ROOT)/publicFuncs.o
objectsA = $(ANALYSIS_ROOT)/nameFileTool.o $(ANALYSIS_ROOT)/input.o $(ANALYSIS_ROOT)/compare.o $(ANALYSIS_ROOT)/newForm.o $(ANALYSIS_ROOT)/output.o $(ANALYSIS_ROOT)/publicFuncs.o

all : basisMake itrMake matrixMake EDMake analysisMake try.o try diskTry.o diskTry TCTP.o TCTP TCTPHPC.o TCTPHPC dipolar.o dipolar analyzeTCTP.o analyzeTCTP analyzeDipolar.o analyzeDipolar
.PHONY : all

.PHONY: basisMake
basisMake:
	make -C $(BASIS_ROOT)

.PHONY: itrMake
itrMake:
	make -C $(ITR_ROOT)

.PHONY: matrixMake
matrixMake:
	make -C $(MATRIX_ROOT)

.PHONY: EDMake
EDMake:
	make -C $(ED_ROOT)

.PHONY: analysisMake
analysisMake:
	make -C $(ANALYSIS_ROOT)

try.o : try.cpp $(BASIS_ROOT)/basis.h $(ITR_ROOT)/interaction.h $(MATRIX_ROOT)/matrix.h $(ED_ROOT)/ED.h
	$(CPP) $(CFLAGS) -c try.cpp

try : try.o $(objects)
	$(CPP) $(CFLAGS) $(OMP) $(objects) try.o -o try $(ALL_GSL_LIBS) $(SUPERLU_LIB) $(ALL_ED_LIBS)

diskTry.o : diskTry.cpp $(BASIS_ROOT)/basis.h $(ITR_ROOT)/interaction.h $(MATRIX_ROOT)/matrix.h $(ED_ROOT)/ED.h
	$(CPP) $(CFLAGS) -c diskTry.cpp

diskTry : diskTry.o $(objects)
	$(CPP) $(CFLAGS) $(OMP) $(objects) diskTry.o -o diskTry $(ALL_GSL_LIBS) $(SUPERLU_LIB) $(ALL_ED_LIBS)

TCTP.o : TCTP.cpp $(BASIS_ROOT)/basis.h $(ITR_ROOT)/interaction.h $(MATRIX_ROOT)/matrix.h $(ED_ROOT)/ED.h
	$(CPP) $(CFLAGS) -c TCTP.cpp

TCTP : TCTP.o $(objects)
	$(CPP) $(CFLAGS) $(OMP) $(objects) TCTP.o -o TCTP $(ALL_GSL_LIBS) $(SUPERLU_LIB) $(ALL_ED_LIBS)

TCTPHPC.o : TCTPHPC.cpp $(BASIS_ROOT)/basis.h $(ITR_ROOT)/interaction.h $(MATRIX_ROOT)/matrix.h $(ED_ROOT)/ED.h
	$(CPP) $(CFLAGS) -c TCTPHPC.cpp

TCTPHPC : TCTPHPC.o $(objects)
	$(CPP) $(CFLAGS) $(OMP) $(objects) TCTPHPC.o -o TCTPHPC $(ALL_GSL_LIBS) $(SUPERLU_LIB) $(ALL_ED_LIBS)

dipolar.o : dipolar.cpp $(BASIS_ROOT)/basis.h $(ITR_ROOT)/interaction.h $(MATRIX_ROOT)/matrix.h $(ED_ROOT)/ED.h
	$(CPP) $(CFLAGS) -c dipolar.cpp

dipolar : dipolar.o $(objects)
	$(CPP) $(CFLAGS) $(OMP) $(objects) dipolar.o -o dipolar $(ALL_GSL_LIBS) $(SUPERLU_LIB) $(ALL_ED_LIBS)

analyzeTCTP.o : analyzeTCTP.cpp $(ANALYSIS_ROOT)/analysis.h
	$(CPP) $(CFLAGS) -c analyzeTCTP.cpp

analyzeTCTP : analyzeTCTP.o $(objectsA)
	$(CPP) $(CFLAGS) $(objectsA) analyzeTCTP.o -o analyzeTCTP $(ALL_GSL_LIBS) 

analyzeDipolar.o : analyzeDipolar.cpp $(ANALYSIS_ROOT)/analysis.h
	$(CPP) $(CFLAGS) -c analyzeDipolar.cpp

analyzeDipolar : analyzeDipolar.o $(objectsA)
	$(CPP) $(CFLAGS) $(objectsA) analyzeDipolar.o -o analyzeDipolar $(ALL_GSL_LIBS) 

.PHONY : clean
clean :
	make -C $(BASIS_ROOT) clean
	make -C $(ITR_ROOT) clean
	make -C $(MATRIX_ROOT) clean
	make -C $(ED_ROOT) clean
	make -C $(ANALYSIS_ROOT) clean
	rm try.o try
	rm diskTry.o diskTry
	rm TCTP.o TCTP	
	rm TCTPHPC.o TCTPHPC	
	rm dipolar.o dipolar	
	rm analyzeTCTP.o analyzeTCTP
	rm analyzeDipolar.o analyzeDipolar