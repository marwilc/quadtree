CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		quadtree.o

LIBS = nodeQ.h quadTree.h

TARGET =	quadtree

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
