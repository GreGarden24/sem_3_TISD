# Компилятор
CC := gcc
RM := rm -rf

# Директории файлов
OBJ_DIR := ./out
SRC_DIR := ./src
INC_DIR := ./inc
UNIT_DIR = ./unit_tests


# Опции компиляции
CFLAGS := -std=gnu99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -I $(INC_DIR)


# Опции сборки
OFLAGS := -lm -I $(INC_DIR)
#UFLAGS := -lcheck -pthread -lrt -lm -I $(INC_DIR)
#ifeq ($(shell uname), Linux)
#UFLAGS += -lsubunit
#endif

# Файлы
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRCS_UNIT = $(wildcard $(UNIT_DIR)/*.c)
OBJS_UNIT := $(OBJS)
OBJS_UNIT += $(SRCS_UNIT:$(UNIT_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_UNIT := $(filter-out $(OBJ_DIR)/main.o, $(OBJS_UNIT))

# Моды запуска
debug: CFLAGS += -ggdb
debug: .debugmode | app.exe

release: CFLAGS += -DNDEBUG -O2
release: .releasemode | app.exe

gcov: CFLAGS += --coverage -O0
gcov: OFLAGS += --coverage -O0
gcov: .gcovmode | app.exe

.debugmode:
	touch .debugmode
	$(RM) $(OBJ_DIR) .releasemode .gcovmode

.releasemode:
	touch .releasemode
	$(RM) $(OBJ_DIR) .debugmode .gcovmode

.gcovmode:
	touch .gcovmode
	$(RM) $(OBJ_DIR) .releasemode .debugmode



# Правила сборки
app.exe : $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(OFLAGS) -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@


unit_tests.exe : $(OBJ_DIR) $(OBJS_UNIT)
	$(CC) $(OBJS_UNIT) -lcheck -pthread -lrt -lm -I $(INC_DIR) -o $@

$(OBJ_DIR)/%.o : $(UNIT_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@


$(OBJ_DIR) :
	mkdir $@

# Фиктивные функции 
.PHONY : clean check func colcov unit

clean : 
	$(RM) *.exe ./func_tests/scripts/program_output.txt $(OBJ_DIR) .releasemode .debugmode .gcovmode

check : 
	shellcheck ./func_tests/scripts/*.sh
 
func : 
	make debug
	cd ./func_tests/scripts/ && ./func_tests.sh

colcov :  
	make gcov
	cd ./func_tests/scripts/ && ./func_tests.sh
	cd $(OBJ_DIR) && gcov main.c

unit : unit_tests.exe
	./unit_tests.exe
