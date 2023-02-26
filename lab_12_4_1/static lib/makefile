CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -I lib/ -I inc/
UFLAGS := -lcheck -lpthread -lrt -lm

C_DIR := ./src
H_DIR := ./inc
O_DIR := ./out
U_DIR := ./unit_tests
LIB_DIR := ./lib
SCRIPTS_DIR := ./func_tests/scripts

CFILES := $(wildcard $(C_DIR)/*.c)
INC := $(wildcard $(H_DIR)/*.h)
LIB := $(wildcard $(LIB_DIR)/*.c)
OBJ := $(CFILES:$(C_DIR)/%.c=$(O_DIR)/%.o)
OBJ += $(LIB:$(LIB_DIR)/%.c=$(O_DIR)/%.o)

UNITS := $(wildcard $(U_DIR)/*.c)
U_OBJ := $(UNITS:$(U_DIR)/%.c=$(O_DIR)/%.o)

LIB_A := libarr.a

release: CFLAGS += -DNDEBUG -g0
release: app.exe

debug: CFLAGS += -g3
debug: app.exe

app.exe: $(OBJ) $(LIB_A)
	$(CC) $^ -o $@

unit_tests.exe: $(U_OBJ) $(LIB_A)
	$(CC) -o $@ $^ $(UFLAGS)

$(LIB_A): $(O_DIR)/lib_arr.o
	ar rc $@ $^
	ranlib $@

$(O_DIR)/%.o: $(C_DIR)/%.c $(INC) $(O_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $@

$(O_DIR)/%.o: $(U_DIR)/%.c $(INC) $(O_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : run unit clean func

func: app.exe
	cd $(SCRIPTS_DIR); ./func_tests.sh

run: app.exe
	./$^

unit: unit_tests.exe
	./$^

clean:
	$(RM) $(O_DIR)/*.o $(O_DIR)/*.txt *.exe
	$(RM) $(SCRIPTS_DIR)/*.txt
	$(RM) *.a