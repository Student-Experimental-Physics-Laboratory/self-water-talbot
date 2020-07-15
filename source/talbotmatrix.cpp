#include "talbotmatrix.h"

#include <cmath>
#include <iostream>
#include <algorithm>

#define DEFAULT_SCALE 1

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

using namespace std;

double countAmplitude(int n_sources, bool reflectible)
{
    return 128 / n_sources / (reflectible ? 2.5 : 1);
}

TalbotParams::TalbotParams(int n_sources,
    double phase,
    double wave_len,
    double wave_slope,
    bool reflectible,
    double viscosity)
{
    this->n_sources = n_sources;
    this->max_amp = countAmplitude(this->n_sources, this->reflectible);
    this->phase = phase;
    this->wave_len = wave_len;
    this->wave_slope = wave_slope;
    this->reflectible = reflectible;
    this->viscosity = viscosity;
}

TalbotMatrix::TalbotMatrix()
{
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->generated = false;
    this->params = TalbotParams();
}

TalbotMatrix::TalbotMatrix(int _width, int _height)
    : TalbotMatrix()
{
    this->width = _width;
    this->height = _height;
}

void TalbotMatrix::updateParams(TalbotParams new_params)
{
    this->params = new_params;
}

vector<pair<unsigned int, unsigned int>> TalbotMatrix::placeSources(void)
{
    vector<pair<unsigned int, unsigned int>> sources;
    if (this->params.n_sources > 0)
    {
        int	   placed = 0;
        double step = this->height / (this->params.n_sources + 1);
        for (double iteration = step; iteration < this->height; iteration += step)
        {
            if (placed == this->params.n_sources)
                break;
            sources.push_back({ 0, iteration });
            placed++;
        }
    }
    return sources;
}

int TalbotMatrix::amplitudeFunction(int d_x, int d_y)
{
    double distance = sqrt(pow(d_x, 2) + pow(d_y, 2)) + this->params.phase;
    int	function_value = 0;
    function_value += this->params.max_amp;
    function_value *= pow((sin(distance / this->params.wave_len) + 1) / 2, this->params.wave_slope);
    function_value *= exp(-distance * this->params.viscosity / 1000);
    //(int)(this->params.max_amp * pow((sin(distance / this->params.wave_len) + 1) / 2, this->params.wave_slope)) * exp(-distance * this->params.viscosity / 1000);
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

    auto reflection_distance = (int) (this->params.reflectible ? wave_distance : 0);
    auto lower_border = -reflection_distance;
    auto higher_border = ((int) this->height - 1) + reflection_distance;

    for (auto& source : sources)
    {
        for (int i = lower_border; i < higher_border; i++)
        {
            for (int j = 0; j < (int) this->width; j++)
            {
                int current_amplitude
                    = this->amplitudeFunction(source.first - j, source.second - i);

                int ix = i;
                while (ix < 0 || ix >= (int) this->height)
                {
                    if (ix < 0)
                    {
                        ix *= -1;
                    }
                    if (ix >= (int) this->height)
                    {
                        ix = 2 * (int) this->height - ix - 1;
                    }
                }

                this->matrix[ix][j] += current_amplitude;
            }
            cout << i << endl;
        }
    }
}

TalbotMatrix::~TalbotMatrix() { this->matrix.clear(); }
