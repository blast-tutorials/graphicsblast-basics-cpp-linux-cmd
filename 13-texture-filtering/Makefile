CC = g++

OBJS = main.cpp shader.cpp texture.cpp

LIBRARIES = -lSDL3 -lSDL3_image -lGL -lGLEW

FLAGS = -Wall

OBJ_NAME = 13-Texture-Filtering

all : $(OBJS)
	$(CC) $(OBJS) $(LIBRARIES) $(FLAGS) -o $(OBJ_NAME)

clean :
	rm -f $(OBJ_NAME)
