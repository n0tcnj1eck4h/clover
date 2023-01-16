SOURCES = $(wildcard src/*.cpp)

DEPFLAGS = -MT $@ -MMD -MP -MF deps/$*.d 
DEPFILES := $(SOURCES:src/%.cpp=deps/%.d) 

CFLAGS := -Wall -O0 -Wextra -pedantic -g -Iinclude -DDEBUG -std=c++20

OBJS = $(patsubst src/%.cpp, obj/%.o, $(SOURCES))

.PHONY: all build clean run

all: build
build: interpreter

interpreter: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

run: interpreter
	@./interpreter

clean:
	$(RM) interpreter
	$(RM) obj/*.o
	$(RM) deps/*.d

obj/%.o obj/%.o: src/%.cpp deps/%.d
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(DEPFILES):
include $(wildcard $(DEPFILES))
