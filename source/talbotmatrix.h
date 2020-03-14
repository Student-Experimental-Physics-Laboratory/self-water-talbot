#ifndef TALBOTMATRIX_H
#define TALBOTMATRIX_H

#include <vector>
#include <QPixmap>

using namespace std;

class TalbotMatrix : public QPixmap
{
private:
	vector<vector<unsigned short>> matrix;

	bool generated;
	unsigned int width;
	unsigned int height;
	// остальные параметры ковра (прокомментировать)

	// Количество источников
	unsigned int sources_quantity;

    // Амплитуда колебаний источника
    int max_amplitude;

	// Фаза волны
	double phase;

	// Длина волны
	double wave_len;

    // Крутость волны (крутость откоса)
    double wave_slope;

	// ****************************************
	// переменные всякие дополнительные
    // функции всякие дополнительные
	// ****************************************

    // Функция размещения источников на генерируемой плоскости
    vector<pair<unsigned int, unsigned int>> placeSources(void);

    // Функция рассчёта амплитуды волны
    float amplitudeFunction(int x, int y, size_t time);

	// генерирует необходимую матрицу и сохраняет результат в matrix (без аргументов)
	// присваивает generated true;
	void generateMatrix(void);

public:
	TalbotMatrix();
	TalbotMatrix(unsigned int _width, unsigned int _height); // добавь в аргументы остальные параметры ковра

	void updateParams(void); // добавь в аргументы остальные параметры ковра
	void updateSize(unsigned int _width, unsigned int _height); // обновляет размер окна
	void updateSources(unsigned int sources_quantity); //

	vector<vector<unsigned short> > getMatrix(); // генерирует картинку с помощью generateMatrix и возвращает матрицу

	~TalbotMatrix();
};

#endif // TALBOTMATRIX_H
