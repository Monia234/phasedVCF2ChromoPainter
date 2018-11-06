
CXX      = g++   
LIBGAB   = /home/gabriel/lib/libgab/

CXXFLAGS = -Wall -lm -O3 -lz -I${LIBGAB} -I${LIBGAB}/gzstream/  -c
LDFLAGS  = -lz


all: phasedVCF2ChromoPainter 

phasedVCF2ChromoPainter.o:	phasedVCF2ChromoPainter.cpp
	${CXX} ${CXXFLAGS} phasedVCF2ChromoPainter.cpp


phasedVCF2ChromoPainter:	phasedVCF2ChromoPainter.o ${LIBGAB}utils.o  ${LIBGAB}gzstream/libgzstream.a
	${CXX} -o $@ $^ $(LDLIBS) $(LDFLAGS)

clean :
	rm -f phasedVCF2ChromoPainter.o phasedVCF2ChromoPainter

