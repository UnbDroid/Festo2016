NOME_EXECUTAVEL = pertinencia
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CXXFLAGS = -O2 -g -Wall -std=c++0x
SOURCE = src
BUILD = build
LIBS = -I includes/
TARGET = $(BUILD)/$(NOME_EXECUTAVEL)


all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

clean :
	rm -f $(OBJ_FILES) $(TARGET)
	rm -r -f $(BUILD)
	rm -r -f obj

obj/%.o: src/%.cpp
	@mkdir -p obj
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBS)