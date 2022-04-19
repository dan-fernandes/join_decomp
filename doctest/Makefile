DOCTEST_SRCS = $(wildcard ./*.cpp)
DOCTEST_LIBS = $(wildcard ./*.h)
DOCTEST_LIBS_DIR = -I./
DOCTEST_OBJS =


JD_SRCS = $(wildcard ../src/joindecomp/*.cpp)
JD_LIBS = $(wildcard ../include/joindecomp/*.h)
JD_LIBS_DIR = -I../include/joindecomp/
JD_OBJS = CSPConstraint.o CSPVariable.o JoinBinaryNode.o JoinDecomp.o JoinDecompBuilder.o

XCSP3_PARSER_SRCS = $(wildcard ../src/xcsp3-cpp-parser/*.cc)
XCSP3_PARSER_LIBS = $(wildcard ../include/xcsp3-cpp-parser/*.h)
XCSP3_PARSER_LIBS_DIR = -I../include/xcsp3-cpp-parser/
XCSP3_PARSER_OBJS = UTF8String.o XCSP3Code.o XCSP3CoreParser.o XCSP3Manager.o XCSP3Tree.o XCSP3TreeNode.o XMLParser.o XMLParserTags.o XCSP3JoinDecompCallbacks.o

#LIBXML_DIRS = $(shell pkg-config libxml-2.0 --cflags --libs)
LIBXML_CFLAGS = $(shell pkg-config libxml-2.0 --cflags)
LIBXML_LIBS = $(shell pkg-config libxml-2.0 --libs)
LIBXML_EXTRA_LIB = $(LIBXML_CFLAGS)/libxml

CFLAGS = -g -I -Wall -c $(LIBXML_CFLAGS)


test.out:  $(DOCTEST_SRCS) $(DOCTEST_LIBS) $(DOCTEST_SRCS) $(JD_OBJS) $(XCSP3_PARSER_OBJS)
	$(CXX)  -o test.out $(DOCTEST_SRCS) $(JD_OBJS) $(XCSP3_PARSER_OBJS) $(DOCTEST_LIBS_DIR) $(XCSP3_PARSER_LIBS_DIR) $(JD_LIBS_DIR) $(LIBXML_CFLAGS) $(LIBXML_LIBS)

$(JD_OBJS): $(JD_SRCS) $(JD_LIBS)
	$(CXX) $(CFLAGS) $(JD_SRCS) $(JD_LIBS_DIR) $(XCSP3_PARSER_LIBS_DIR)

$(XCSP3_PARSER_OBJS): $(XCSP3_PARSER_SRCS) $(XCSP3_PARSER_LIBS)
	$(CXX) $(CFLAGS) $(XCSP3_PARSER_SRCS) $(XCSP3_PARSER_LIBS_DIR) $(LIBXML_LIBS)

clean:
	rm $(wildcard ./*.o) ./test.out
