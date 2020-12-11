SrcFiles=$(wildcard ./src/*.c)
DirFiles=$(notdir ${SrcFiles})
ObjFiles=$(patsubst %.c,./obj/%.o,${DirFiles})
BinFiles=$(patsubst %.c,./bin/%,${DirFiles})
#BinFiles=$(basename ${DirFiles})

echo:
	@echo $(SrcFiles)
	@echo ${DirFiles}
	@echo ${ObjFiles}
	@echo ${BinFiles}
	@echo "done"

all:${BinFiles}

${BinFiles}:./bin/%:./obj/%.o
	gcc -o $@ -I ./inc $<

${ObjFiles}:./obj/%.o:./src/%.c
	gcc -c -I ./inc $< -o $@

.PHONY:clean all
	
clean:
	rm -f ./obj/*.o
	rm -f ./bin/*
