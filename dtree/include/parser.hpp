#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "cls_sample.hpp"


namespace dt {


template <std::size_t n_feat, typename feat_t>
using dataset = std::vector<cls_sample>;


/*
    parses a file (for now) into a vector of cls_samples
*/
class parser {

private:




public:

    // default constructor
    parser() = default;


    // filename must be csv (no checks though)
    // parser(const std::string & filename);


    // parse csv file
    // ignore_first_col: pass true if the csv contains column names in the first row
    dataset parse_csv(const std::string & filename, bool ignore_first_col = false);

};


} // namespace dt