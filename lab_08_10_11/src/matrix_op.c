#include "matrix_op.h"
#include "matrix_alloc.h"
#include <math.h>

#define EPS 1e-07

int gauss_solving(double **data, size_t n, size_t m, double ***res_coll)
{
    // Если размеры некорректные - выход из функции
    if (n != m - 1)
        return MATRIX_SIZE_ERROR;
    
    /*
    Выделение памяти под массив индексов, соответствующих первоначальному
    расположению столбцов
    */
    int *index = malloc(m * sizeof(int));
    if (index == NULL)
        return ALLOC_ERROR;

    // Выделение памяти под столбец-результат
    double **res = matrix_alloc(n, 1);
    if (res == NULL)
    {
        free(index);
        return ALLOC_ERROR;
    }
    
    // Заполнение массива индексов: нумерация столбцов по возрастанию
    for (size_t i = 0; i < m; i++)
        index[i] = i;
    
    int cr = OK;
    size_t ind_max;
    double k, calc;

    // Цикл по строкам до предпоследней включительно
    for (size_t t = 0; t < n - 1; t++)
    {
        // Поиск ведущего (максимального) элемента в строке
        ind_max = find_max(data[t], m - 1, t);

        /* 
        Меняем столбцы местами: на главную диагональ ставится столбец
        с найденным максимальным значением. Также меняются индексы в 
        массиве index, чтобы отследить перестановки столбцов
        */
        swap_cols(data, index, n, t, ind_max);
        
        // Цикл по всем строкам, начиная со "следующей" от внешнего цикла
        for (size_t i = t + 1; i < n; i++)
        {
            // Вычисление коэффициента для строки, чтобы обнулялись все
            // элементы под ведущим
            k = data[i][t] / data[t][t];

            //Вычитание строки с выбранным ведущим элементом из "текущей"
            for (size_t j = 0; j < m; j++)
                data[i][j] -= k * data[t][j];
        }
    }

    // Матрица приведена к верхнетреугольному виду
    
    // Считаем значения, начиная с конца матрицы
    for (size_t i = n - 1; !cr && i < n; i--)
    {
        // Инициализируем calc элементом, находящимся в столбце свободных членов
        calc = data[i][m - 1];

        /*
        Решаем как уравнение: из calc вычитаем коэффициент (data[i][j]), который 
        получился после выполнения преобразований, умноженный на уже 
        найденное значение переменной, записанной в столбце-результате
        */
        for (size_t j = m - 2; !cr && j > i; j--)
            calc -= data[i][j] * res[index[j]][0];
        
        // Проверка на бесконечное число решений: вся строка нулевая
        if (check_zero_line(data[i], m))
            cr = INF_SOLUTIONS;
        // Проверка на отсутствие решений: вся строка, кроме столбца свободных членов нулевая
        else if (check_zero_line(data[i], m - 1))
            cr = ZERO_SOLUTIONS;
        else
        /*
        В столбец результат записывается вычисленное значение, деленное на
        коэффициент, стоящий на главной диагонали. Найденное значение записывается
        в res на место, которое соответсвует его первоначальному положению в матрице
        */
            res[index[i]][0] = calc / data[i][i];
    }
    
    if (cr == OK)
        *res_coll = res;
    else
        matrix_free(res, n);
    free(index);

    return cr;
}

int check_zero_line(double *line, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (fabs(line[i]) > EPS)
            return 0;

    return 1;
}

void swap_cols(double **data, int *index, size_t n, size_t l, size_t r)
{
    double tmp;
    for (size_t i = 0; i < n; i++)
    {
        tmp = data[i][l];
        data[i][l] = data[i][r];
        data[i][r] = tmp;
    }

    int t;
    t = index[l];
    index[l] = index[r];
    index[r] = t;
}

size_t find_max(double *data, size_t m, size_t start)
{
    size_t max = start;
    for (size_t i = start; i < m; i++)
        if (data[max] < data[i])
            max = i;

    return max;
}

int matrix_sum(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m)
{
    if (a_n != b_n || a_m != b_m)
        return MATRIX_SIZE_ERROR;
    
    *c_n = a_n;
    *c_m = a_m;
    double **temp = matrix_alloc(*c_n, *c_m);
    if (temp == NULL)
        return ALLOC_ERROR;
    
    for (size_t i = 0; i < *c_n; i++)
        for (size_t j = 0; j < *c_m; j++)
            temp[i][j] = a[i][j] + b[i][j];
    *c = temp;
    
    return OK;
}

int matrix_mult(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m)
{
    if (a_m != b_n)
        return MATRIX_SIZE_ERROR;
    
    *c_n = a_n;
    *c_m = b_m;
    double **temp = matrix_alloc(*c_n, *c_m);
    if (temp == NULL)
        return ALLOC_ERROR;
    
    double t;
    for (size_t i = 0; i < *c_n; i++)
        for (size_t j = 0; j < *c_m; j++)
        {
            t = 0;
            for (size_t k = 0; k < a_m; k++)
                t += a[i][k] * b[k][j];
            temp[i][j] = t;
        }
    *c = temp;
    
    return OK;
}
