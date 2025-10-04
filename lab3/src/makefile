CC=gcc
CFLAGS=-I.

# Target для сборки программ
all: sequential_min_max parallel_min_max launch_sequential

# Targetы для сборки
sequential_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o sequential_min_max find_min_max.o utils.o sequential_min_max.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

launch_sequential : sequential_min_max
	$(CC) -o launch_sequential launch_sequential.c $(CFLAGS)

# Компиляция utils.c
utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

# Компиляция find_min_max.c
find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

# Очистка скомпилированных файлов
clean :
	rm -f utils.o find_min_max.o sequential_min_max parallel_min_max launch_sequential