#ifndef __FILTER_H__
#define __FILTER_H__

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

/**
 * Фильтрация массива
 * \param [in] pb_src Указатель на начало первого массива
 * \param [in] pe_src Указатель за последний элемент первого массива
 * \param [in] pb_dst Указатель на указатель на начало второго массива
 * \param [in] pe_dsr Указатель на указатель за последний элемент второго массива
 * \return Код ошибки
 */
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

/**
 * Копирование элементов, больших среднего арифметического, из первого массива во второй
 * \param [in] pb_src Указатель на начало первого массива
 * \param [in] pe_src Указатель за последний элемент первого массива
 * \param [in] pb_dst Указатель на начало второго массива
 * \param [in] avg Среднее арифметическое
 */
void copy(const int *pb_src, const int *pe_src, int *const pb_dst, double avg);

/**
 * Подсчет количества элементов, больших среднего арифметического
 * \param [in] pb Указатель на начало массива
 * \param [in] pe Указатель за последний элемент массива
 * \param [in] avg Среднее арифметическое
 * \return Количество элементов
 */
int num_count(const int *pb, const int *pe, double avg);

/**
 * Вычисляет среднее арифметическое элементов массива
 * \param [in] pb Указатель на начало массива
 * \param [in] pe Указатель за последний элемент массива
 * \return Среднее арифметическое
 */
double average(const int *pb, const int *pe);

#endif
