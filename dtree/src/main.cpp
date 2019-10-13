#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "parser.hpp"
#include "dtree.hpp"

#define N_ARGS      1
#define N_FEATURES  4
#define N_GROUPS    3


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
    auto [dataset, id_to_label] = ps.parse_csv<float, N_FEATURES>(data_filename);

    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    // print class labels
    cout << "Classes:" << endl;
    for(auto [id, name] : id_to_label) cout << "  " << id << ": " << name << endl;

    auto seconds = (int) std::round(duration / 1000000);
    auto millis  = (float) (duration % 1000000) / 1000;

    cout << endl << dataset.size() << " samples parsed in " << fixed << setprecision(2) << seconds << " s " << millis << " ms" << endl;


    // DEBUG
    cout << endl;
    cout << "# of labels: " << num_labels(dataset) << endl;
    cout << "# of samples per label: " << num_per_label(dataset) << endl;
    cout << "dataset entropy: " << dataset_entropy(dataset) << endl;


    // group the features
    auto ds = discretize_dataset(dataset, N_GROUPS);

    cout << "entropy of group 0 of attribute 0: " << group_entropy(ds, 0, 0) << endl;
    cout << "entropy of group 1 of attribute 0: " << group_entropy(ds, 0, 1) << endl;
    cout << "entropy of group 2 of attribute 0: " << group_entropy(ds, 0, 2) << endl;

    cout << "discriminative power of attribute 0: " << disc(ds, 0) << endl;
    cout << "discriminative power of attribute 1: " << disc(ds, 1) << endl;
    cout << "discriminative power of attribute 2: " << disc(ds, 2) << endl;
    cout << "discriminative power of attribute 3: " << disc(ds, 3) << endl;

    // split dataset into training and testing
    auto [train_ds, test_ds] = split_dataset(ds, 0.8, true);

    // build decision tree
    decision_tree tree;
    tree.fit(train_ds);

    // evaluate decision tree
    auto res = tree.predict(test_ds[0]);
    cout << "predicted: " << res << "  ground truth: " << test_ds[0].label_id() << endl;

    return 0;
}