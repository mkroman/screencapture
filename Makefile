CXX = g++
CXXFLAGS = -Wall -g -I/usr/local/include -I/usr/include
LDFLAGS = -L/usr/local/lib -L /usr/lib -lgiblib -lImlib2 -lfreetype -lz -lX11 -lXext -ldl -lm
SOURCES = src/Screencapture.cpp src/ScreenshotManager.cpp src/Screenshot.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = screencapture

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS) $(LDFLAGS) -o $@
