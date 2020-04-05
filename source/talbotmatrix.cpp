#include "talbotmatrix.h"

#include <cmath>
#include <iostream>
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
    this->sources_quantity = 1;
    this->is_reflectible = true;
    this->max_amplitude = this->countAmplitude();
    this->phase = 0;
    this->wave_len = 10;
    this->wave_slope = 1;
    this->viscosity = 1000;
}

TalbotMatrix::TalbotMatrix(int _width, int _height)
: TalbotMatrix()
{
    this->width	 = _width;
    this->height = _height;
}

double TalbotMatrix::countAmplitude(void)
{
    return 128 / this->sources_quantity / (this->is_reflectible ? 2.5 : 1);
}

void TalbotMatrix::updateParams(double _phase,
                                double _wave_len,
                                double _wave_slope,
                                double _viscosity)
{
    this->phase			= _phase;
    this->wave_len		= _wave_len;
    this->wave_slope	= _wave_slope;
    this->viscosity = _viscosity;
    this->generated		= false;
}

void TalbotMatrix::updateSources(int _sources_quantity, bool _is_reflectible)
{
    this->sources_quantity = _sources_quantity;
    this->is_reflectible = _is_reflectible;
    this->max_amplitude = this->countAmplitude();
    this->generated		   = false;
}

vector<pair<unsigned int, unsigned int>> TalbotMatrix::placeSources(void)
{
    vector<pair<unsigned int, unsigned int>> sources;
    if (this->sources_quantity > 0)
    {
        int	   placed = 0;
        double step	  = this->height / (this->sources_quantity + 1);
        for (double iteration = step; iteration < this->height; iteration += step)
        {
            if (placed == this->sources_quantity)
                break;
            sources.push_back({ 0, iteration });
            placed++;
        }
    }
    return sources;
}

int TalbotMatrix::amplitudeFunction(int d_x, int d_y)
{
    double distance		  = sqrt(pow(d_x, 2) + pow(d_y, 2)) + phase;
    int	   function_value = (int) (this->max_amplitude * pow((sin(distance / this->wave_len) + 1) / 2, this->wave_slope)) * exp(-distance * this->viscosity / 1000);
    return function_value;
}

vector<vector<unsigned int>> TalbotMatrix::getMatrix()
{
    this->generateMatrix();
    return this->matrix;
}

void TalbotMatrix::generateMatrix()
{
	if (this->generated)
		return;

    this->matrix.clear();
    this->matrix
        = vector<vector<unsigned int>>(this->height, vector<unsigned int>(this->width, 128));

    vector<pair<unsigned int, unsigned int>> sources = this->placeSources();

    unsigned int wave_distance
        = max(this->height, this->width);  //Дистанция, на которую волна распространяется

    auto target_height = (int) this->height + (int) (this->is_reflectible ? wave_distance : 0) - 1;

    for (auto& source : sources)
    {
        for (int i = 0 - (this->is_reflectible ? wave_distance : 0) + 1; i < target_height; i++)
        {
            for (int j = 0; j < (int) this->width; j++)
            {
                int current_amplitude
                    = this->amplitudeFunction(source.first - j, source.second - i);
                int i_modified = i;
                if (i == (int) this->height)
                {
                    continue;
                }
                else if (i_modified < 0)
                {
                    i_modified *= -1;
                }
                else if (i_modified > (int) this->height)
                {
                    i_modified = 2 * (int) this->height - i_modified;
                }
                this->matrix[i_modified][j] += current_amplitude;
            }
        }
    }
}

TalbotMatrix::~TalbotMatrix() { this->matrix.clear(); }
