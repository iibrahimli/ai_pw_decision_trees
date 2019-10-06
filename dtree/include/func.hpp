/*
    functions used in decision trees
*/

#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include "cls_sample.hpp"
#include "parser.hpp"



/*
    printing a vector of primitives lmao
*/
template <typename T>
std::ostream & operator << (std::ostream & out, std::vector<T> vec){
    
    out << "[ ";
    for(auto i = 0; i < vec.size(); ++i)
        out << vec[i] << ", ";
    out << "]";
    
    return out;
}


/*
    number of labels for a dataset (max_label_id + 1)
*/
template <typename feat_t, std::size_t n_feat>
unsigned int num_labels(std::vector<dt::cls_sample<feat_t, n_feat>> & dataset){
    
    unsigned int num_lbl = 0;

    for(auto & s : dataset){
        if(s.label_id() > num_lbl)
            num_lbl = s.label_id();
    }

    return num_lbl + 1;
}


/*
    returns a vector of number of samples belonging to each label
*/
template <typename feat_t, std::size_t n_feat>
std::vector<unsigned int> num_per_label(std::vector<dt::cls_sample<feat_t, n_feat>> & dataset){
    
    unsigned int num_lbl = num_labels(dataset);
    std::vector<unsigned int> lbl_count(num_lbl, 0);

    for(auto i = 0; i < dataset.size(); ++i){
        ++lbl_count[dataset[i].label_id()];
    }

    return lbl_count;
}


/*
    Shannon entropy of a dataset
*/
template <typename feat_t, std::size_t n_feat>
float dataset_entropy(std::vector<dt::cls_sample<feat_t, n_feat>> & dataset){
    
    float h = 0;
    float prob;

    auto total = dataset.size();
    auto counts = num_per_label(dataset);

    for(auto i = 0; i < counts.size(); ++i){
        if(counts[i] == 0) continue;
        prob = (float) counts[i] / total;
        h -= prob * std::log2(prob);
    }

    return h;
}