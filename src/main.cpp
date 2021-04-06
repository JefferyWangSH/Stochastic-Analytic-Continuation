#include <boost/program_options.hpp>
#include <iostream>

#include "sac.h"

#include <ctime>


/** The main program */
int main(int argc, char *argv[]) {

    /* default SAC parameters */
    int lt = 80;
    double beta = 4.0;
    int nOmega = 50;
    double omegaMin = 0.0, omegaMax = 5.0;

    std::string input_filename = "../results/benchmark_g.txt";
    std::string output_filename = "../results/output.txt";

    /* read params from command line */
    boost::program_options::options_description opts("Program options");
    boost::program_options::variables_map vm;

    opts.add_options()
            ("help,h", "display this information")
            ("lt,t", boost::program_options::value<int>(&lt), "imaginary-time lattice size of QMC simulation, default: 80")
            ("beta,b", boost::program_options::value<double>(&beta), "inverse temperature of quantum system, default: 4.0")
            ("nOmega,n", boost::program_options::value<int>(&nOmega), "number of slices in frequency space, default: 50")
            ("omegaMin", boost::program_options::value<double>(&omegaMin), "lower bound of frequency space, default: 0.0")
            ("omegaMax", boost::program_options::value<double>(&omegaMax), "upper bound of frequency space, default: 5.0")
            ("infile,i", boost::program_options::value<std::string>(&input_filename), "input filename, default: ../results/benchmark_g.txt")
            ("outfile,o", boost::program_options::value<std::string>(&output_filename), "output filename, default: ../results/output.txt");

    try {
        boost::program_options::store(parse_command_line(argc, argv, opts), vm);
    }
    catch (...) {
        std::cerr << "Undefined options got from command line."<< std::endl;
        exit(1);
    }

    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cerr << argv[0] << std::endl;
        std::cerr << opts << std::endl;
        exit(1);
    }


    /* start SAC process */
    SAC sac;

    sac.set_SAC_params(lt, beta, nOmega, omegaMin, omegaMax);

    sac.initialSAC();

    sac.read_QMC_data(input_filename);

    time_t begin_t = clock(), end_t;

    for (int n = 0; n < pow(10, 5); ++n) {
        sac.Metropolis_update_1step();
    }

    end_t = clock();
    std::cout << "Time cost: " << (double)(end_t - begin_t) / CLOCKS_PER_SEC <<std::endl;

    std::cout << std::endl;

    std::cout << sac.A_omega << std::endl;

    return 0;
}