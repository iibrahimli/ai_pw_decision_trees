#include <string>
#include <iostream>
#include <iomanip>

#include "parser.hpp"
#include "dtree.hpp"

#define N_ARGS 1


using std::cout;
using std::endl;
using dt::cls_sample;
using dt::parser;
// using dt::dtree;


int main(int argc, char * argv[]){

    if(argc != N_ARGS + 1){
        cout << "Usage: " << argv[0] << " path/to/data_file.csv" << endl;
        return 1;
    }

    std::string data_filename = argv[1];

    parser ps;
    auto [dataset, id_to_label] = ps.parse_csv<float, 4>(data_filename);

    // print class labels
    for(auto [id, name] : id_to_label) cout << id << ": " << name << endl;

    return 0;
}