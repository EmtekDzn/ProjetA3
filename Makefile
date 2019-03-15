CFLAGS = -g -Wall -pedantic
LDFLAGS = ./ftd2xx.lib

SRC = $(wildcard *.c)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: ProjetA3.out

remake: clean ProjetA3.out

ProjetA3.out : $(OBJ)
	gcc obj/* $(LDFLAGS) -o $@ 

obj/%.o: %.c
	gcc -c -Iinclude $(CFLAGS) -o $@ $<

clean:
	rm obj/*.o *.out *.gch -f

clear:
	rm obj/*.o *.gch -f

zipsimu:
	zip simu.zip consigne.c consigne.h visualisationT.c visualisationT.h visualisationC.c visualisationC.h regulation.c regulation.h integration.c integration.h simulateur.c simulateur.h define.h

zipusb:
	zip usb.zip usb.c releve.c releve.h visualisationT.c visualisationT.h visualisationC.c visualisationC.h regulation.c regulation.h integration.c integration.h commande.c commande.h define.h