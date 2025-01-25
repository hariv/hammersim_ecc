CXX = g++
CXXFLAGS = -g -Wall -Werror

TARGET = hammersim_ecc
SRC = ecc.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
