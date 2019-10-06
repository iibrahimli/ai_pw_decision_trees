#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "parser.hpp"
#include "dtree.hpp"

#define N_ARGS 1

using namespace std;
using namespace dt;


int main(int argc, char * argv[]){

    if(argc != N_ARGS + 1){
        cout << "Usage: " << argv[0] << " path/to/data_file.csv" << endl;
        return 1;
    }

    std::string data_filename = argv[1];


    // read and parse data

    auto t1 = std::chrono::high_resolution_clock::now();

    parser ps;
    auto [dataset, id_to_label] = ps.parse_csv<float, 4>(data_filename);

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    // print class labels
    for(auto [id, name] : id_to_label) cout << id << ": " << name << endl;

    cout << endl << dataset.size() << " samples parsed in " << fixed << setprecision(2) << (float) duration / 1000 << " ms" << endl;


    // DEBUG
    cout << endl;
    cout << "# of labels: " << num_labels(dataset) << endl;
    cout << "# of samples per label: " << num_per_label(dataset) << endl;
    cout << "dataset entropy: " << dataset_entropy(dataset) << endl;


    // build decision tree
    


    return 0;
}