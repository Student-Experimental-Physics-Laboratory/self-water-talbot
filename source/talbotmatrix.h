#ifndef TALBOTMATRIX_H
#define TALBOTMATRIX_H

#include <QImage>

#include <vector>

double countAmplitude(int n_sources, bool reflectible);

struct TalbotParams
{
    TalbotParams(int n_sources = 1,
        double phase = 0,
        double wave_len = 10,
        double wave_slope = 1,
        bool reflectible = true,
        double viscosity = 1);

    // Количество источников
    int n_sources;

    // Амплитуда колебаний источника
    double max_amp;

    // Фаза волны
    double phase;

    // Длина волны
    double wave_len;

    // Крутость волны (крутость откоса)
    double wave_slope;

    // Отражения
    bool reflectible;

    // Вязкость
    double viscosity;
};

class TalbotMatrix
{
private:
    std::vector<std::vector<unsigned int>> matrix;
    // остальные параметры ковра (прокомментировать)

    TalbotParams params;

    // ****************************************
    // переменные всякие дополнительные
    // функции всякие дополнительные
    // ****************************************

    // Функция размещения источников на генерируемой плоскости
    std::vector<std::pair<unsigned int, unsigned int>> placeSources(int width, int height);

    // Функция рассчёта амплитуды волны
    int amplitudeFunction(int x, int y);

    // генерирует необходимую матрицу и сохраняет результат в matrix (без аргументов)
    // присваивает generated true;
    void updateMatrix(int width, int height);

    // генерирует картинку с помощью generateMatrix и возвращает матрицу
    std::vector<std::vector<unsigned int>> getMatrix(int width, int height);

public:
    TalbotMatrix();

    void updateParams(TalbotParams new_params);	// добавь в аргументы остальные параметры ковра

    QImage drawTalbot(int width, int height);

    ~TalbotMatrix();
};

#endif	// TALBOTMATRIX_H
