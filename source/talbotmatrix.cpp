#include "talbotmatrix.h"

#include <cmath>
#include <algorithm>

#define DEFAULT_SCALE 1

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

using namespace std;

TalbotMatrix::TalbotMatrix()
{
    this->width		= DEFAULT_WIDTH;
    this->height	= DEFAULT_HEIGHT;
	this->generated = false;
}

TalbotMatrix::TalbotMatrix(unsigned int _width, unsigned int _height)
: TalbotMatrix()
{
    this->width	 = _width;
    this->height = _height;
	this->generateMatrix();
}

vector<pair<unsigned int, unsigned int>> TalbotMatrix::placeSources(void)
{
    vector<pair<unsigned int, unsigned int>> sources;
    if (this->sources_quantity > 0)
    {
        size_t placed = 0;
        double step	  = this->height / (this->sources_quantity + 1);
        for (double iteration = 0; iteration < this->height; iteration += step)
        {
            if (placed == this->sources_quantity)
                break;
            sources.push_back({ 0, iteration });
            placed++;
        }
    }
    return sources;
}

float TalbotMatrix::amplitudeFunction(int x, int y, size_t time)
{
    float distance		 = sqrt(pow(x, 2) + pow(y, 2)) + time;
    float function_value = this->max_amplitude * pow((sin(distance) + 1) / 2, this->wave_slope);
    return function_value;
}

void TalbotMatrix::generateMatrix()
{
	if (this->generated)
		return;

    auto sources = this->placeSources();

    unsigned int wave_distance
        = max(this->height, this->width);  //Дистанция, на которую волна распространяется

    for (auto& i : sources)
    {
        for (int i = 0 - wave_distance; i < this->height + wave_distance; i++)
        {
            for (int j = 0; j < this->width; i++)
            {
                auto current_amplitude = this->amplitudeFunction()
            }
        }
    }
}
