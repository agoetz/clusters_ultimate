#include <cmath>
#include <cassert>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

#include "io_tools/read_nrg.h"
#include "io_tools/write_nrg.h"

#include "bblock/system.h"

namespace {

static std::vector<bblock::System> systems;

} // namespace

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{

  if (argc != 2) {
    std::cerr << "usage: energy h2o_ion.nrg"
              << std::endl;
    return 0;
  }

  try {
    std::ifstream ifs(argv[1]);

    if (!ifs){
      throw std::runtime_error("could not open the NRG file");
    }

    tools::ReadNrg(argv[1], systems);
  } catch (const std::exception& e) {
    std::cerr << " ** Error ** : " << e.what() << std::endl;
    return 1;
  }

  std::cout << "Energies without gradients:" << std::endl;
  std::vector<double> g;
  for (size_t i = 0; i < systems.size(); i++) {
    double energy = systems[i].Energy(g,false);
    std::cout << std::setprecision(10) << std::scientific
              << "system["  << std::setfill('.')
              << std::setw(5) << i << "]= " << std::setfill(' ')
              << std::setw(20) << std::right << energy 
              << std::setw(12) << std::right << " kcal/mol" << std::endl;          
  }
  return 0;
}
