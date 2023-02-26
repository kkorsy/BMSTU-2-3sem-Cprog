#ifndef __STR_H__
#define __STR_H__

#include <stdio.h>

/**
 * \brief Записывает строку в буфер
 * \param [in] num Размер буфера
 * \param [in] substr Строка, которую нужно записать в буфер
 * \param [out] buf Строка, в которую будет записано число
 * \return Количество символов, которые можно было бы записать, если бы размер буфера был достаточным
 */
int write_str(char *buf, size_t num, char *substr);

/**
 * \brief Записывает восьмеричное число в буфер
 * \param [in] num Размер буфера
 * \param [in] oct Число в восьмеричной СС
 * \param [out] buf Строка, в которую будет записано число
 * \return Количество символов, которые можно было бы записать, если бы размер буфера был достаточнымКоличество
 */
int write_oct(char *buf, size_t num, unsigned long int oct);

/**
 * \brief Переводит число в восьмеричную СС
 * \param [in] num Число в десятичной СС
 * \return Число в восьмеричной СС
 */
unsigned long int convert_to_oct(unsigned int num);

/**
 * \brief Переводит целый тип в символьный
 * \param [in] x Цифра
 * \return Символьное представление цифры
 */
char int_to_char(int x);

/**
 * \brief Подсчитывает количество цифр в числе
 * \param [in] num Число, для которого нужно посчитать длину
 * \return Количество цифр
 */
int num_len(unsigned long int num);

#endif