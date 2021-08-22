#include <iostream>
#include <fstream>
#include <iomanip>

#include <boost/program_options.hpp>

#include "SAC.h"

#include <chrono>


/**
 *  TODO:
 *   1. Optimize random module (missing)
 *   2. ...
 */


/** The main program */
int main(int argc, char *argv[]) {

    int lt = 101;
    double beta = 4.0;
    int nbin = 1000;
    int rebin_pace = 1;
    int num_boostrap = 5000;

    double grid_interval = 1e-5;
    double spec_interval = 1e-2;
    double omega_min = -10.0;
    double omega_max = +10.0;

    int ndelta = 1000;
    double theta = 100.0;

    std::chrono::steady_clock::time_point begin_t{}, end_t{};
    begin_t = std::chrono::steady_clock::now();

//    ReadInModule read_in;

//    read_in.set_params(lt, beta, nbin, rebin_pace, num_boostrap);
//    read_in.read_tau_from_file("../input/benchmark/tgrid.dat");
//    read_in.read_corr_from_file("../input/benchmark/cor.dat");
//    read_in.analyse_corr();
//    read_in.discard_and_rotate();
//    read_in.deallocate_memory();

//    std::cout << read_in.lt << std::endl;
//    std::cout << read_in.tau_seq << std::endl;
//
//    std::cout << read_in.nbin << std::endl;
//    std::cout << read_in.nbin_total << std::endl;
//
//    for (int l = 0; l < read_in.lt; ++l) {
//        std::cout << read_in.corr_tau_bin[0][l] << std::endl;
//    }
//

//    for (int i = 0; i < read_in.cov_mat_dim; ++i) {
//        std::cout << read_in.tau_seq[i] << "     "
//                  << read_in.corr_mean_seq[i] << "     "
//                  << read_in.corr_err_seq[i] << std::endl;
//    }
//    std::cout << read_in.tau_seq << std::endl << std::endl;
//    std::cout << read_in.corr_mean_seq << std::endl << std::endl;
//    std::cout << read_in.corr_err_seq << std::endl;

//    for (auto i = 0; i < read_in.cov_eig.size(); ++i) {
//        read_in.cov_eig[i] = sqrt(read_in.cov_eig[i]/num_boostrap);
//    }
//
//    std::cout << read_in.cov_eig << std::endl;
//    std::cout << read_in.cov_eig.size() << std::endl;
//    std::cout << read_in.rotate_mat << std::endl;

//    std::cout << (read_in.cov_mat - read_in.cov_mat.transpose()).maxCoeff() << std::endl;
//    std::cout << ( read_in.rotate_mat.transpose() * read_in.cov_eig.asDiagonal() * read_in.rotate_mat - read_in.cov_mat ).maxCoeff() << std::endl;
//


    SAC *sac = new SAC();

    sac->set_read_in_params(lt, beta, nbin, rebin_pace, num_boostrap);
    sac->set_filename_tau("../input/benchmark/tgrid.dat");
    sac->set_filename_corr("../input/benchmark/cor.dat");
    sac->set_griding_params(grid_interval, spec_interval, omega_min, omega_max);
    sac->set_sampling_params(ndelta, theta);

    sac->init();

    end_t = std::chrono::steady_clock::now();
    std::cout << "total cost "
              << (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_t-begin_t).count()/1000
              << "s." << std::endl;

    delete sac;
    return 0;
}