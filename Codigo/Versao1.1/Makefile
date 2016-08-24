LIBPATH = $(OPENROBOTINOAPI_DIR)/1/lib/linux
LIBPATH2 = $(OPENROBOTINOAPI_DIR)/share/lib/linux
INCPATH = $(OPENROBOTINOAPI_DIR)/1/include
INCPATH2 = $(OPENROBOTINOAPI_DIR)/share/include

NOME_EXECUTAVEL = pertinencia
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CXXFLAGS = -O2 -g -Wall -std=c++0x -I$(INCPATH) -I$(INCPATH2) 

SOURCE = src
BUILD = build

LIBS = -I includes/ `pkg-config --libs opencv`

CFLAGS = -Dlinux32 -Wall -I$(INCPATH) -I$(INCPATH2) `pkg-config --cflags opencv`
LDFLAGS += -Wl,-rpath,$(LIBPATH),-rpath,$(LIBPATH2) -L$(LIBPATH) -L$(LIBPATH2) -lrec_robotino_com -lrec_core_lt
CC = g++
OBJ = main.o

TARGET = $(BUILD)/$(NOME_EXECUTAVEL)

all: $(TARGET)

clean :
	rm -f $(OBJ_FILES) $(TARGET)
	rm -r -f $(BUILD)
	rm -r -f obj

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) $(LDFLAGS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBS)
