#ifndef STOCHASTIC_ANALYTIC_CONTINUATION_MEASURE_H
#define STOCHASTIC_ANALYTIC_CONTINUATION_MEASURE_H
#pragma once

/*
 *  This head file includes Measure class to obtain spectrum functions of statistical significance
 *  from weight configurations generated by SAC.
 */

#include <ctime>

#include "sac.h"


class Measure {

public:
    // measuring parameters
    int nbin = 20;
    int nBetweenBins = 5;
    int nstep = 100;
    int nwarm = (int)pow(10, 5);

    // SAC class and sampling parameters
    SAC sac;
    double theta = exp(7);
    int nCst = 4;

    // input/output filename
    std::string infilename = "../results/benchmark_g.txt";
    bool is_data_read = false;

    // record cpu time
    time_t begin_t = clock(), end_t = clock();

    // measuring quantities
    std::vector<double> binEntropy;
    double meanEntropy = 0.0;
    double errEntropy = 0.0;

    std::vector<double> binChi2;
    double meanChi2 = 0.0;
    double errChi2 = 0.0;


    Measure() = default;

    /* set parameters */
    void set_SAC_params(int lt, double beta, int nOmega, double omegaMin, double omegaMax);

    void set_meas_params(int nbin, int nBetweenBins, int nstep, int nwarm);

    void set_sampling_params(const double &theta, const int &nCst);

    void set_input_file(const std::string &infilename);

    /* prepare for measuring
     * once input file was changed, prepare operation is needed before measuring. todo: check is_data_read. */
    void prepare();

    void measure(bool bool_display_process);

    void print_Stats() const;

    void output_Stats(const std::string &outfilename);

    void clear_Stats();

    void calculate_Entropy();

private:


};

#endif //STOCHASTIC_ANALYTIC_CONTINUATION_MEASURE_H
