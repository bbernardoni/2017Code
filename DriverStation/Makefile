EXE = ds

OBJ_DIR = .objs
SRC_DIR = src

FILES = $(shell find $(SRC_DIR)/ -name '*.cpp')

CXX = g++
LD = g++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS	 = $(WARNINGS) -std=c++11 -MMD -MP -c
CXXFLAGS_DEBUG   = $(CXXFLAGS) -g -O0
CXXFLAGS_RELEASE = $(CXXFLAGS) 
LDFLAGS =  -lsfml-graphics -lsfml-window -lsfml-system

all: $(EXE)
debug: clean $(EXE)-debug

# Rules for executables
$(EXE): $(FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $^ $(LDFLAGS) -o $@
$(EXE)-debug: $(FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%-debug.o)
	$(LD) $^ $(LDFLAGS) -o $@

# Include automatically generated dependencies
-include $(OBJ_DIR)/*.d

# Pattern rules for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS_RELEASE) $< -o $@
$(OBJ_DIR)/%-debug.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS_DEBUG) $< -o $@

clean:
	rm -rf $(EXE) $(EXE)-debug $(OBJ_DIR)

.PHONY: all clean debug
