CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -I lib/ -I inc/
LINKFLAGS := -ldl
UFLAGS := -lcheck -lpthread -lrt -lm -lsubunit

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
LIB_OBJ := $(LIB:$(LIB_DIR)/%.c=$(O_DIR)/%.o)

UNITS := $(wildcard $(U_DIR)/*.c)
U_OBJ := $(UNITS:$(U_DIR)/%.c=$(O_DIR)/%.o)

LIB_SO := libarr.so

release: CFLAGS += -DNDEBUG -g0
release: app.exe

debug: CFLAGS += -g3
debug: app.exe

app.exe: $(OBJ) $(LIB_SO)
	$(CC) $^ -o $@

unit_tests.exe: $(U_OBJ) $(LIB_SO)
	$(CC) -o $@ $^ $(UFLAGS)

$(LIB_SO): $(LIB_OBJ)
	$(CC) -shared $< $(LINKFLAGS) -o $(LIB_SO)

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
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.; \
	cd $(SCRIPTS_DIR); ./func_tests.sh

run: app.exe
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.; \
	./$^

unit: unit_tests.exe
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.; \
	./$^

clean:
	$(RM) $(O_DIR)/*.o $(O_DIR)/*.txt *.exe
	$(RM) $(SCRIPTS_DIR)/*.txt
	$(RM) *.so