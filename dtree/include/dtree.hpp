#pragma once

#include <vector>

#include "cls_sample.hpp"
#include "func.hpp"


namespace dt{


enum node_type : bool {
    BRANCH,
    LEAF
};


struct decision_tree_node {
    node_type                           type;         // type of node
    std::size_t                         i_feat;       // index of feature to consider
    std::size_t                         prediction;   // prediction (class_id) if it is a LEAF node
    std::vector<decision_tree_node *>   branches;     // branches corresponding to each group
};


struct decision_tree{

    decision_tree_node * root;


    /*
        default constructor
    */
    decision_tree()
    :   root {nullptr}
    {}


    /*
        builds a decision tree given a dataset (vector of cls_samples)
    */
    template <typename feat_t, std::size_t n_feat>
    void fit(const std::vector<cls_sample<feat_t, n_feat>> & ds){

    }


    /*
        returns predicted class_id
    */
    template <typename feat_t, std::size_t n_feat>
    std::size_t predict(const cls_sample<feat_t, n_feat> & sample){

    }


};


}  // namespace dt