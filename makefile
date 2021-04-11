CC = g++
CV = -std=c++11
CFLAGS = -g -c $(CV)
LFLAGS = -g $(CV)
GLFLAGS = -lglut -lGL -lGLU

EXEC = nurbs
BUILD = build/
SRC = src/
OBJS=$(patsubst $(SRC)%.cpp, $(BUILD)%.o, $(wildcard $(SRC)*.cpp))

all: $(OBJS) dir
	$(CC) $(LFLAGS) $(OBJS) -o $(BUILD)$(EXEC) $(GLFLAGS)

$(BUILD)%.o: $(SRC)%.cpp dir
	$(CC) $(CFLAGS) $< -o $@

dir:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
