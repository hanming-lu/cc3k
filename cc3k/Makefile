CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -Werror=vla -MMD
EXEC=cc3k
OBJECTS=main.o TextDisplay.o Floor.o Direction.o Info.o Base.o Character.o PC.o Troll.o Vampire.o Shade.o Goblin.o Drow.o SuperMan.o Enemy.o Elf.o Dwarf.o Halfling.o Orc.o Human.o Merchant.o Dragon.o Item.o Potion.o BA.o WA.o BD.o WD.o RH.o PH.o Treasure.o Small.o Normal.o MerchantHoard.o DragonHoard.o Type.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lncurses

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
