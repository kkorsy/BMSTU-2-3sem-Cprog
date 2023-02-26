#ifndef __MATRIX_ALLOC_H__
#define __MATRIX_ALLOC_H__

#include <stdio.h>
#include <stdlib.h>

/**
 * Освобождает память из-под матрицы
 * \param [in] data Массив указателей на строки матрицы
 */
void matrix_free(double **data, size_t n);

/**
 * Выделяет память под матрицу размерами n x m
 * \param [in] n Количество строк
 * \param [in] m Количество столбцов
 * \return Массив указателей на строки матрицы
 */
double **matrix_alloc(size_t n, size_t m);

#endif
