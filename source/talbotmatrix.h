#ifndef TALBOTMATRIX_H
#define TALBOTMATRIX_H

#include <vector>
#include <QPixmap>
#include <map>

using namespace std;

class TalbotMatrix : public QPixmap
{
private:
    vector<vector<unsigned int>> matrix;

    bool generated;
    int	 width;
    int	 height;
	// остальные параметры ковра (прокомментировать)

	// Количество источников
    int sources_quantity;

    // Амплитуда колебаний источника
    double max_amplitude;

	// Фаза волны
	double phase;

	// Длина волны
	double wave_len;

    // Крутость волны (крутость откоса)
    double wave_slope;

    // Отражения
    bool is_reflectible;

    double viscosity;

	// ****************************************
	// переменные всякие дополнительные
    // функции всякие дополнительные
	// ****************************************

    // Функция размещения источников на генерируемой плоскости
    vector<pair<unsigned int, unsigned int>> placeSources(void);

    // Функция рассчёта амплитуды волны
    int amplitudeFunction(int x, int y);

	// генерирует необходимую матрицу и сохраняет результат в matrix (без аргументов)
	// присваивает generated true;
    void generateMatrix(void);

    double countAmplitude(void);

public:
	TalbotMatrix();
    TalbotMatrix(int _width,
                 int _height);	// добавь в аргументы остальные параметры ковра

    void updateParams(double _phase,
                      double _wave_len,
                      double _wave_slope,
                      double _viscosity);	// добавь в аргументы остальные параметры ковра
    void updateSize(int _width, int _height);	 // обновляет размер окна
    void updateSources(int _sources_quantity,
                       bool _is_reflectible);			 //

    vector<vector<unsigned int>>
    getMatrix();  // генерирует картинку с помощью generateMatrix и возвращает матрицу

	~TalbotMatrix();
};

#endif	// TALBOTMATRIX_H
