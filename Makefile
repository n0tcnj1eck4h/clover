SOURCES = $(wildcard src/*.cpp)

DEPFLAGS = -MT $@ -MMD -MP -MF deps/$*.d 
DEPFILES := $(SOURCES:src/%.cpp=deps/%.d) 

CFLAGS :=-Wall -Wextra -pedantic -g -Iinclude -DDEBUG -std=c++20

OBJS = $(patsubst src/%.cpp, obj/%.o, $(SOURCES))

.PHONY: all build clean run

all: build
build: build/out

build/out: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

run: build/out
	build/out

clean:
	$(RM) build/out
	$(RM) obj/*.o
	$(RM) deps/*.d

obj/%.o: src/%.cpp deps/%.d
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(DEPFILES):
include $(wildcard $(DEPFILES))
