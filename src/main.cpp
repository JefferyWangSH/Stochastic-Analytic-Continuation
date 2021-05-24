#include <iostream>
#include <fstream>
#include <iomanip>

#include <boost/program_options.hpp>

#include "SAC.h"
#include "MonteCarloSAC.h"


/**
 *  TODO:
 *   1. Support reading configurations from file
 *   2. class AnalyseSAC to recover fermion spectrum from averaged configs n(x)
 *   3. update in parallel
 *   4. ...
 */


/** The main program */
int main(int argc, char *argv[]) {

    int lt = 80;
    double beta = 4;

    double omega_min = -5.0;
    double omega_max =  5.0;

    int nMoment = 1;
    int nalpha = 80;
    int nconfig = 50;

    int nbin = 100;
    int nstep_1bin = 200;
    int step_between_bins = 10;
    int nwarm = 1e6;
    int n_swap_pace = 50;


    /** Monte Carlo SAC */
    MonteCarloSAC sac;

    sac.set_SAC_params(lt, beta, nconfig, omega_min, omega_max, nMoment);

    sac.set_measure_params(nbin, nstep_1bin, step_between_bins, nwarm, n_swap_pace);

    sac.set_input_file("../results/data/gt_l4_lt80_u-4.0_b4.0_k_pi2pi2.txt");

    std::vector<double> alpha_list(nalpha);
    for (int n = 0; n < nalpha; ++n) {
        alpha_list[n] = ( n == 0 )? exp(-5.0) : alpha_list[n-1] * exp(0.1);
    }
    sac.set_tempering_profile(nalpha, alpha_list);

    sac.prepare();

    sac.run_Monte_Carlo();

    sac.output_stats("../results/h-alpha.txt");

    std::string filename = "../results/configs-alpha.txt";
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);

    for (int n = 0; n < nalpha; ++n) {
        for (int i = 0; i < nconfig; ++i) {
            outfile << std::setiosflags(std::ios::right)
                    << std::setw(15) << n
                    << std::setw(15) << 1.0 / (nconfig + 1) * (i + 1)
                    << std::setw(15) << sac.measure.n_x_alpha[n][i]
                    << std::setw(15) << sac.measure.err_n_x_alpha[n][i]
                    << std::endl;
        }
    }
    outfile.close();

    for (auto p : sac.p_list[10]) {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;

    sac.print_stats();

    return 0;
}