#Добавлять ли отладочные символы
DEBUG ?= 0
#Название выходного файла
OUTPUT_NAME ?= area_calculator
#Стандарт C
C_STANDARD ?= c99


#Названия, используемые при сборке бинарников
PROG_NAME = $(OUTPUT_NAME)

#Используемые директории
OBJECT_DIR = objects
BIN_DIR = binary
TESTS_DIR = tests

#Команды компиляции и очистки
CC = gcc
STRIP = strip
CLEAN = rm -rf

#Списки задействуемых файлов
SOURCES = $(sort $(wildcard src/*.c))
OBJECTS = $(sort $(patsubst %.c, $(OBJECT_DIR)/%.o, $(SOURCES)))
DEPENDS = $(sort $(patsubst %.c, $(OBJECT_DIR)/%.d, $(SOURCES)))

#Флаги компиляции
FLAGS = -Wall -MMD -MP -std=$(C_STANDARD)
LIBS = -lm
INCLUDES = -I src/

#Обработка флагов сборки
ifeq ($(DEBUG), 1)
	FLAGS +=  -g3
endif

#Цель по умолчанию, создающая необходимые директории и производящая сборку
all: makedirs $(PROG_NAME)

#Сборка целевого бинарника
$(PROG_NAME): $(OBJECTS)
	$(CC) $^ $(LIBS) -o $(BIN_DIR)/$@
	if [ $(DEBUG) = 0 ]; then $(STRIP) $(BIN_DIR)/$@; fi

#Отслеживание зависимостей
-include $(DEPENDS)

#Сборка объектных файлов из .c
$(OBJECT_DIR)/%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(OBJECT_DIR)/$*.o

#Создание директорий для бинарников и объектных файлов
makedirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJECT_DIR)
	mkdir -p $(OBJECT_DIR)/src/

#Очистка проекта
cl: clean
clean:
	$(CLEAN) $(BIN_DIR)/
	$(CLEAN) $(OBJECT_DIR)/
