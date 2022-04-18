PARSER_SRCS = $(wildcard src/xcsp3-cpp-parser/*.cc)
PARSER_LIBS = $(wildcard include/xcsp3-cpp-parser/*.h)
MAINS = $(wildcard Main/*.cpp)
LIBXML_DIRS = $(shell pkg-config libxml-2.0 --cflags --libs)


#I think some of these should technically be absolute filepaths:
out: $(PARSER_SRCS) $(PARSER_LIBS)
	$(CXX) $(MAINS) $(PARSER_SRCS) -Isrc/xcsp3-cpp-parser/ -Iinclude/xcsp3-cpp-parser/ -IMain/ $(LIBXML_DIRS)
