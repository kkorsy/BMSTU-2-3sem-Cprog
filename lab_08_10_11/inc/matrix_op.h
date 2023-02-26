#ifndef __MATRIX_OP_H__
#define __MATRIX_OP_H__

#include <stdio.h>
#include "errors.h"

/**
 * Выполняет решение СЛАУ методом Гаусса с выбором ведущего элемента по строке
 * \param [in] data Массив указателей на строки матрицы
 * \param [in] n Количество строк
 * \param [in] m Количество столбцов
 * \param [out] res_col Указатель на столбец-результат
 * \return Код ошибки
 */
int gauss_solving(double **data, size_t n, size_t m, double ***res_col);

/**
 * Проверяет, является ли строка нулевой
 * \param [in] line Строка матрицы
 * \param [in] n Количество элементов
 * \return Результат проверки
 */
int check_zero_line(double *line, size_t n);

/**
 * Меняет столбцы матрицы местами
 * \param [in] data Массив указателей на строки матрицы
 * \param [in] index Массив идексов столбцов матрицы
 * \param [in] n Количество строк матрицы
 * \param [in] l Индекс первого столбца, которого нужно поменять
 * \param [in] r Индекс второго столбца, которого нужно поменять
 */
void swap_cols(double **data, int *index, size_t n, size_t l, size_t r);

/**
 * Выполняет поиск максимального элемента в строке матрицы
 * \param [in] data Строка матрицы
 * \param [in] m Количество элементов
 * \param [in] start Индекс, с которого начинается поиск
 * \return Индекс максимального элемента
 */
size_t find_max(double *data, size_t m, size_t start);

/**
 * Выполняет сложение матриц
 * \param [in] a Массив указателей на строки первой матрицы
 * \param [in] a_n Количество строк первой матрицы
 * \param [in] a_m Количество столбцов первой матрицы
 * \param [in] b Массив указателей на строки второй матрицы
 * \param [in] b_n Количество строк второй матрицы
 * \param [in] b_m Количество столбцов второй матрицы
 * \param [out] c Указатель на массив указателей на строки итоговой матрицы
 * \param [out] c_n Указатель на количество строк итоговой матрицы
 * \param [out] c_m Указатель на количество столбцов итоговой матрицы
 * \return Код ошибки
 */
int matrix_sum(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m);

/**
 * Выполняет умножение матриц
 * \param [in] a Массив указателей на строки первой матрицы
 * \param [in] a_n Количество строк первой матрицы
 * \param [in] a_m Количество столбцов первой матрицы
 * \param [in] b Массив указателей на строки второй матрицы
 * \param [in] b_n Количество строк второй матрицы
 * \param [in] b_m Количество столбцов второй матрицы
 * \param [out] c Указатель на массив указателей на строки итоговой матрицы
 * \param [out] c_n Указатель на количество строк итоговой матрицы
 * \param [out] c_m Указатель на количество столбцов итоговой матрицы
 * \return Код ошибки
 */
int matrix_mult(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m);

#endif