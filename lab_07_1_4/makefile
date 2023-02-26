CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -I inc/
UFLAGS := -lcheck -lpthread -lrt -lm

C_DIR := ./src
H_DIR := ./inc
O_DIR := ./out
U_DIR := ./unit_tests
SCRIPTS_DIR := ./func_tests/scripts

CFILES := $(wildcard $(C_DIR)/*.c)
INC := $(wildcard $(H_DIR)/*.h)
OBJ := $(CFILES:$(C_DIR)/%.c=$(O_DIR)/%.o)

UNITS := $(wildcard $(U_DIR)/*.c)
U_OBJ := $(UNITS:$(U_DIR)/%.c=$(O_DIR)/%.o)
U_OBJ += $(O_DIR)/sort.o
U_OBJ += $(O_DIR)/filter.o

release: CFLAGS += -DNDEBUG -g0
release: app.exe

debug: CFLAGS += -g3
debug: app.exe

app.exe: $(OBJ)
	$(CC) $^ -o $@

unit_tests.exe: $(U_OBJ)
	$(CC) -o $@ $^ $(UFLAGS)

$(O_DIR)/%.o: $(C_DIR)/%.c $(INC) $(O_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $@

$(O_DIR)/%.o: $(U_DIR)/%.c $(INC) $(O_DIR)
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