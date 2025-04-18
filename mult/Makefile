CXX      = icpc

CXXFLAGS = -O3 -g
LDFLAGS = 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

all: mult_orig mult_opt

mult_orig: Makefile mult.cpp mult.h
	$(CXX) $(CXXFLAGS) -DORIGINAL $(LDFLAGS) -o $@ mult.cpp

mult_opt: Makefile mult.cpp mult.h
	$(CXX) $(CXXFLAGS) -DOPTIMISED $(LDFLAGS) -o $@ mult.cpp

clean:
	rm -f mult_opt mult_orig *.o *~ 

