#-------------------------------------------------------------------------------
#	AUTOR
#	Aurea Desarrollo Tecnológico.
#	FECHA
#	Notas:
#-------------------------------------------------------------------------------
APPNAME = tcpSocket
#Compiler:
	CC=g++

#Compiler flags
	CFLAGS=-c -g -Wall
	INCLUIDES=$(shell pkg-config --cflags gtk+-2.0 libgnomeui-2.0)
	LIBS=$(shell pkg-config --libs gtk+-2.0 libgnomeui-2.0)
#Directories
	DIRlib= /usr/local/lib	
	incDIR= /usr/local/include
	libADT= /home/mchc/aurea/cpp/programs/ADTlib-0.0.1
#main function
	mainP= main
	callbacks = My_callbacks
	guiClass = My_guiClass
#-------------------------------------------------------------------------------
all: Project

Project: mainP.o guiClass.o callbacks.o ADT_TCPSocket.o ADT_GTK.o
	$(CC) -export-dynamic -o $(APPNAME) \
	$(LIBS) \
	$(mainP).o \
	$(guiClass).o \
	$(callbacks).o \
	ADT_TCPSocket.o \
	ADT_GTK.o 	


	
mainP.o: $(mainP).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(mainP).cpp
	
guiClass.o: $(guiClass).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(guiClass).cpp 

callbacks.o: $(callbacks).cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	$(callbacks).cpp 
	
ADT_TCPSocket.o: ADT_TCPSocket.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_TCPSocket.cpp 
	
ADT_GTK.o: ADT_GTK.cpp
	$(CC) $(INCLUIDES) $(CFLAGS) \
	ADT_GTK.cpp 
	
	
