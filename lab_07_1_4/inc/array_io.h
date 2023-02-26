#ifndef __ARRAY_IO_H__
#define __ARRAY_IO_H__

#include <stdio.h>
#include "errors.h"

/**
 * Запись массива в файл
 * \param [in]  file_name Имя файла
 * \param [in] pb Указатель на начало массива
 * \param [in] pe Указатель за последний элемент массива
 * \return Код ошибки
 */
int array_write(char *file_name, int *pb, int *pe);

/**
 * Запись массива в файл
 * \param [in] f Файловая переменная, куда записывать массив
 * \param [in] pb Указатель на начало массива
 * \param [in] pe Указатель за последний элемент массива
 * \return Код ошибки
 */
int print(FILE *f, int *pb, int *pe);

/**
 * Чтение массива из файла
 * \param [in] file_name Имя файла
 * \param [out] arr Указатель на указатель на массив
 * \param [out] n Количество элементов массива
 * \return Код ошибки
 */
int array_read(char *file_name, int **arr, size_t *n);

/**
 * Заполнение массива значениями из файла
 * \param [in] f Файловая переменная, откуда нужно считать значения
 * \param [in] pb Указатель на начало массива
 * \param [in] pe Указатель за последний элемент массива
 */
void array_fill(FILE *f, int *pb, int *pe);

/**
 * Подсчет количества элементов в файле
 * \param [in] f Файловая переменная
 * \param [in] n Количество элементов
 * \return Код ошибки
 */
int elem_count(FILE *f, size_t *n);

#endif
