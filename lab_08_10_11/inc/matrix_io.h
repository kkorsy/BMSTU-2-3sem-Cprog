#ifndef __MATRIX_IO_H__
#define __MATRIX_IO_H__

#include <stdio.h>
#include "errors.h"

/**
 * Считывает матрицу из файла
 * \param [in] f Файловая переменная, откуда нужно считать матрицу
 * \param [in] n Количество строк
 * \param [in] m Количество столбцов
 * \param [out] data Массив указателей на строки матрицы
 * \return Код ошибки
 */
int matrix_read(FILE *f, double **data, size_t n, size_t m);

/**
 * Создает матрицу: выделяет память, считывает из файла
 * \param [in] filename Имя файла
 * \param [in] n Указатель на количество строк
 * \param [in] m Указатель на количество столбцов
 * \param [out] data Указатель на массив указателей на строки матрицы
 * \return Код ошибки
 */
int matrix_create(char *filename, double ***data, size_t *n, size_t *m);

/**
 * Записывает матрицу в файл
 * \param [in] filename Имя файла
 * \param [in] data Массив указателей на строки матрицы
 * \param [in] n Количество строк
 * \param [in] m Количество столбцов
 * \return Код ошибки
 */
int matrix_print(char *filename, double **data, size_t n, size_t m);

#endif