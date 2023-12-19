CC = g++
CXXFLAGS = -std=c++11

SRC = prueba.cpp leerMapa.cpp bootstraps.cpp entregarPaquete.cpp  # Add entregarPaquete.cpp to the list
OBJ = $(SRC:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	del $(OBJ) $(TARGET).exe
