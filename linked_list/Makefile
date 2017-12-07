TARGET = main
FILENAME= main.c
all: $(TARGET)
$(TARGET).o: $(FILENAME)
	gcc -c -o $(TARGET).o $(FILENAME)
$(TARGET): $(TARGET).o
	gcc -o $(TARGET) $(FILENAME)
clean:
	rm -rf *.o $(TARGET)
