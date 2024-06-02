# Nombre del compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -std=c++11 -pthread

# Archivos fuente
SERVER_SRC = servidor.cpp
CLIENT_SRC = cliente.cpp

# Archivos objeto
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)

# Ejecutables
SERVER_EXE = servidor
CLIENT_EXE = cliente

# Reglas para compilar todo
all: $(SERVER_EXE) $(CLIENT_EXE)

# Regla para compilar el servidor
$(SERVER_EXE): $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar el cliente
$(CLIENT_EXE): $(CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar los archivos objeto del servidor
$(SERVER_OBJ): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -c $<

# Regla para compilar los archivos objeto del cliente
$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -c $<

# Regla para limpiar los archivos objeto y ejecutables
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_EXE) $(CLIENT_EXE)

# Regla para limpiar sólo los ejecutables
clean_exe:
	rm -f $(SERVER_EXE) $(CLIENT_EXE)
