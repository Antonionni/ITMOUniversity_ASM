TARGET = main
ADDED = LinkedList
all: $(TARGET)

$(TARGET).o: $(TARGET).c
	gcc -c -o $(TARGET).o $(TARGET).c
$(ADDED).o: $(ADDED).c
	gcc -c -o $(ADDED).o $(ADDED).c

$(TARGET): $(TARGET).o $(ADDED).o
	gcc -o $(TARGET) $(TARGET).o $(ADDED).o
clean:
	rm -rf *.o $(TARGET)
