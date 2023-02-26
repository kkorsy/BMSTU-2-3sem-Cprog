#ifndef __SNPRINTF_H__
#define __SNPRINTF_H__

#include <stdio.h>

/**
 * \brief Записывает в буфер не более num символов в соответствии со строкой форматирования format
 * \param [in] num Размер буфера
 * \param [in] format Строка форматирования
 * \param [out] buf Буфер, в который помещается строка
 * \return Количество символов, которые можно было бы записать, если бы размер буфера был достаточным
 */
int my_snprintf(char *restrict buf, size_t num, const char *restrict format, ...);

#endif