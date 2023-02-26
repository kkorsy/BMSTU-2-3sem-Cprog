CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -I lib/ -I inc/
LINKFLAGS := -ldl
UFLAGS := -lcheck -lpthread -lrt -lm -lsubunit

LIB_DIR := ./lib
U_DIR := ./unit_tests
O_DIR := ./out

LIB_SO := libarr.so

LIB_FILES := $(wildcard $(LIB)*.c)
UNITS := $(wildcard $(U_DIR)/*.c)

OBJ := $(LIB_FILES:$(LIB_DIR)/%.c=$(O_DIR)/%.o)
U_OBJ := $(UNITS:$(U_DIR)/%.c=$(O_DIR)/%.o)

run: script.py $(LIB_SO)
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.; \
	python3 $<

$(LIB_SO): $(O_DIR)/arr_lib.o
	$(CC) -shared $^ $(LINKFLAGS) -o $@

$(O_DIR)/arr_lib.o: $(LIB_DIR)/arr_lib.c
	$(CC) $(CFLAGS) -c $^ -o $@

unit_tests.exe: $(U_OBJ) $(LIB_SO)
	$(CC) -o $@ $^ $(UFLAGS)

$(O_DIR)/%.o: $(U_DIR)/%.c $(O_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(O_DIR):
	@mkdir -p $@

unit: unit_tests.exe
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.; \
	./$^

clean:
	rm -f $(O_DIR)/*.o $(O_DIR)/*.txt *.exe *.so