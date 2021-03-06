#ifndef SYS_TOOLS_H
#define SYS_TOOLS_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <algorithm>

#include "nanoflann.hpp"
#include "kdtree_utils.h"
#include "tools/definitions.h"

#include "potential/1b/ps.h"
#include "tools/constants.h"

namespace systools {

// Function that given the monomers, modifies the ordered monomer list
// in mon, and the original order in the vector original_order
// taking sites into account, while original_order_realSites only takes
// into account real sites
std::vector<std::pair<std::string,size_t>> OrderMonomers
         (std::vector<std::string> &mon,
          std::vector<size_t> sites,
          std::vector<size_t> nats,
          std::vector<std::pair<size_t,size_t> > &original_order,
          std::vector<std::pair<size_t,size_t> > &original_order_realSites);

// Function that sets up initial charges, pols, polfacs, number of sites
// number of atoms and first index. Returns the total number of sites
size_t SetUpMonomers(std::vector<std::string> mon, std::vector<size_t> &sites,
                     std::vector<size_t> &nat, std::vector<size_t> &fi_at);

// Makes sure that all the atoms of the monomers are together in space
void FixMonomerCoordinates(std::vector<double> &xyz,
                           std::vector<double> box,
                           std::vector<size_t> nat,
                           std::vector<size_t> first_index);                           

// Puts the two monomers of a dimer together for a given set of xyz
void GetCloseDimerImage(std::vector<double> box,
                        size_t nat1, size_t nat2, size_t nd,
                        double * xyz1, double * xyz2);

// Puts the three monomers of a trimer together for a given set of xyz
void GetCloseTrimerImage(std::vector<double> box,
                        size_t nat1, size_t nat2, size_t nat3, size_t nt,
                        double * xyz1, double * xyz2, double * xyz3);

// Given ifnormation of the system, this subroutine fills up the dimers and 
// trimers of the system.
void AddClusters(size_t n_max, double cutoff, size_t istart, size_t iend,
                 size_t nmon, bool use_pbc, 
                 std::vector<double> box,
                 std::vector<double> xyz_orig, 
                 std::vector<size_t> first_index,
                 std::vector<size_t> &dimers, 
                 std::vector<size_t> &trimers); 

// Fills up the excluded set pairs for a given monomer
void GetExcluded(std::string mon, 
                 excluded_set_type &exc12,
                 excluded_set_type &exc13,
                 excluded_set_type &exc14);

// Returns if a pair a,b (or b,a) is in the excluded set exc
bool IsExcluded(excluded_set_type exc, size_t a, size_t b);

// Returns the proper aDD value for the electrostatics
double GetAdd(bool is12, bool is13, bool is14, std::string mon);

// Reorders the gradients or coordinates to the original order
std::vector<double> ResetOrder(std::vector<double> coords,
    std::vector<std::pair<size_t,size_t> > original_order, 
    std::vector<size_t> first_index,
    std::vector<size_t> sites);

// Reorders the gradients or coordinates to the original order
// only taking into account real sites. 
std::vector<double> ResetOrder(std::vector<double> coords,
    std::vector<std::pair<size_t,size_t> > original_order,
    size_t numats,
    std::vector<size_t> first_index,
    std::vector<size_t> nats);

// Reorders the atom names to the original order
std::vector<std::string> ResetOrder(std::vector<std::string> at_names,
    std::vector<std::pair<size_t,size_t> > original_order, 
    std::vector<size_t> first_index,
    std::vector<size_t> sites);

// Calculates the coordinates of the virtual site of a monomer when
// given the coordinates of the other sites
void SetVSites(std::vector<double> &xyz, std::string mon_id,
               size_t n_mon, size_t nsites, size_t fst_ind);

// Calculates the charges of all the sites in a monomer using its xyz
// coordinates
void SetCharges(std::vector<double> xyz, std::vector<double> &charges,
                std::string mon_id, size_t n_mon, size_t nsites, 
                size_t fst_ind, std::vector<double> &chg_der);
void SetPolfac (std::vector<double> &polfac, std::string mon_id,
                size_t n_mon, size_t nsites, size_t fst_ind);
// FIXME polfac here should not be necessary (we are only setting pols
void SetPol (std::vector<double> &pol, 
             std::string mon_id, size_t n_mon, size_t nsites, size_t fst_ind);

void RedistributeVirtGrads2Real(const std::string mon, const size_t nmon,
        const size_t fi_crd, std::vector<double> &grad);

void ChargeDerivativeForce(const std::string mon, const size_t nmon,
        const size_t fi_crd, const size_t fi_sites,
        const std::vector<double> phi, std::vector<double> &grad,
        const std::vector<double> chg_grad); 

} // systools
#endif // SYS_TOOLS_H
