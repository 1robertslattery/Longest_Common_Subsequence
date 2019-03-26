CC=gcc
CXX=g++
RM=rm -f
CFLAGS += -g -O2 -Wall -W -pedantic
CXXFLAGS=$(CFLAGS) -std=c++11
SRC=main.cpp
OBJS=$(subst .cpp,.o,$(SRC))
TARGET=lcs

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	
$(TARGET).o: $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC)
	
clean:
	$(RM) $(OBJS)
	
distclean: clean
    $(RM) $(TARGET)
