JC =javac
.SUFFIXES:.java .class
target:
	$(JC) $(CLASSES)

CLASSES = \
	Main.java\
	Matriz.java\
	Multithread.java\
	ReadText.java

default:CLASSES

classes:$(CLASSES:.java=.class)

clean:\
	$(RM) *.class