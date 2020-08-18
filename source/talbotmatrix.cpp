#include "talbotmatrix.h"

#include <cmath>
#include <iostream>
#include <algorithm>

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
    this->params = TalbotParams();
}

void TalbotMatrix::updateParams(const TalbotParams &new_params)
{
    this->params = new_params;
}

void TalbotMatrix::drawTalbot(QImage &image)
{
    std::vector<std::vector<unsigned int>> matrix = this->getMatrix(image.height(), image.width());
    QRgb *pixels = (QRgb *) image.bits();
    for (int i = 0; i < image.height(); i++)
        for (int j = 0; j < image.width(); j++)
            pixels[i * image.width() + j] = QColor::fromRgb(matrix[j][i], matrix[j][i], matrix[j][i]).rgb();
}

std::vector<std::pair<unsigned int, unsigned int>> TalbotMatrix::placeSources(int width, int height)
{
    std::vector<std::pair<unsigned int, unsigned int>> sources;
    if (this->params.n_sources > 0)
    {
        int	   placed = 0;
        double step = height / (this->params.n_sources + 1);
        for (double iteration = step; iteration < height; iteration += step)
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
    return function_value;
}

std::vector<std::vector<unsigned int>> TalbotMatrix::getMatrix(int width, int height)
{
    this->updateMatrix(width, height);
    return this->matrix;
}

void TalbotMatrix::updateMatrix(int width, int height)
{
    this->matrix.clear();
    this->matrix
        = std::vector<std::vector<unsigned int>>(height, std::vector<unsigned int>(width, 128));

    std::vector<std::pair<unsigned int, unsigned int>> sources = this->placeSources(width, height);

    unsigned int wave_distance
        = std::max(height, width);  //Дистанция, на которую волна распространяется

    auto reflection_distance = (int) (this->params.reflectible ? wave_distance : 0);
    auto lower_border = -reflection_distance;
    auto higher_border = ((int) height - 1) + reflection_distance;

    for (auto& source : sources)
    {
        for (int i = lower_border; i < higher_border; i++)
        {
            for (int j = 0; j < (int) width; j++)
            {
                int current_amplitude
                    = this->amplitudeFunction(source.first - j, source.second - i);

                int ix = i;
                while (ix < 0 || ix >= (int) height)
                {
                    if (ix < 0)
                    {
                        ix *= -1;
                    }
                    if (ix >= (int) height)
                    {
                        ix = 2 * (int) height - ix - 1;
                    }
                }

                this->matrix[ix][j] += (current_amplitude);
            }
        }
    }
}

TalbotMatrix::~TalbotMatrix() { this->matrix.clear(); }
