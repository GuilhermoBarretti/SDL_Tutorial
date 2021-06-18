SRC_PATH=./src/
FILE_WITH_PATH=$(wildcard $(SRC_PATH)*.cpp)
HEADER_WITH_PATH=$(wildcard $(SRC_PATH)*.hpp)
FILE_WITHOUT_PATH=$(notdir $(FILE_WITH_PATH))
FILE=$(FILE_WITHOUT_PATH:%.cpp=%)
CC=cl.exe
SRCS1=$(addprefix ./src/, $(FILE))
SRC=$(FILE_WITH_PATH)
OBJ=$(addsuffix .obj, $(FILE))
LDFLAGS=/LIBPATH:./lib/ SDL2.lib SDL2main.lib SDL2_image.lib
INCL=/I./include/
CFLAGS=/std:c++17
EXE=game.exe

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	LINK $(OBJ) $(LDFLAGS) /OUT:$(EXE)

%.obj: ./src/%.cpp $(HEADER_WITH_PATH)
	$(CC) $(CFLAGS) /c $< $(INCL)

link:
	LINK $(OBJ) $(LDFLAGS) /OUT:$(EXE)

clean:
	rm -f *.obj