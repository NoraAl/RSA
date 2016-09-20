all: 
%.o: %.cc
	g++ -c -O2 -Wall

library-objects = \
	BigUnsigned.o \
	BigInteger.o \
	BigIntegerAlgorithms.o \
	BigUnsignedInABase.o \
	BigIntegerUtils.o \
	RSA.o \

library-headers = \
	NumberlikeArray.hpp \
	BigUnsigned.hpp \
	BigInteger.hpp \
	BigIntegerAlgorithms.hpp \
	BigUnsignedInABase.hpp \
	BigIntegerLibrary.hpp \
	RSA.hpp \

library: $(library-objects)
$(library-objects): $(library-headers)

program = main
program-object = main.o


$(program-object) : $(library-headers)
$(program) : $(program-object) $(library-objects)
	@g++ $^ -o $@

clean :
	@rm -f $(library-objects) $(program-object) $(program)


all : library $(program)