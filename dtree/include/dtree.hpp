#pragma once

#include <vector>

#include "cls_sample.hpp"
#include "func.hpp"


namespace dt{


enum node_type {
    BRANCH,
    LEAF
};


struct decision_tree_node {

    node_type                           type;         // type of node
    std::size_t                         feat_id;      // index of feature to consider
    std::size_t                         group_id;     // group in i_feat to consider
    std::size_t                         pred;         // prediction (class_id) if it is a LEAF node
    std::vector<decision_tree_node *>   branches;     // branches corresponding to each group


    decision_tree_node()
        :   type     {LEAF},
            feat_id  {0},
            group_id {0},
            pred     {0}
    {}


    decision_tree_node(node_type tp, std::size_t feat_i = 0, std::size_t group_i = 0, std::size_t prediction = 0)
        :   type     {tp},
            feat_id  {feat_i},
            group_id {group_i},
            pred     {prediction}
    {}

};


struct decision_tree{

private:

    // root node
    decision_tree_node * root;

    // number of groups for all features (assumend to be the same)
    std::size_t          n_groups;


    // stopping condition threshold
    float                sc_threshold;



    /*
        is it time to stop?
        evaluates stopping condition on a GROUP (give it a group NOT the whole dataset)
    */
    template <typename feat_t, std::size_t n_feat>
    float eval_sc(const std::vector<cls_sample<feat_t, n_feat>> & dataset){
        
        auto [mj_label, ratio] = majority_label(dataset);
        
        return ratio;
    }


    /*
        ??? split and add nodes ???
    */
    template <typename feat_t, std::size_t n_feat>
    void split(){

    }


public:

    /*
        default constructor
        threshold: stopping condition threshold
                   default sc is (#majority_label / #group_size) > threshold
    */
    decision_tree(float threshold = 0.95)
        :   root         {nullptr},
            n_groups     {0},
            sc_threshold {threshold}
    {}


    /*
        builds a decision tree given a dataset (vector of cls_samples)
    */
    template <typename feat_t, std::size_t n_feat>
    void fit(const std::vector<cls_sample<feat_t, n_feat>> & dataset){

        auto ds = dataset;
        std::vector<float> feat_disc(n_feat, 0);
        
        // ASSUMING NUMBER OF GROUPS IS SAME FOR ALL FEATURES
        n_groups = num_groups(ds, 0);
        
        // compute discriminative power for each feature
        for(auto ftr = 0lu; ftr < n_feat; ++ftr)
            feat_disc[ftr] = disc(ds, ftr);
        
        // make list of features from most disc to least
        std::vector<std::size_t> features;
        std::size_t              current_feature_idx = 0;
        auto                     feat_tmp = feat_disc;

        // sort features
        for(int i = 0; i < feat_tmp.size(); ++i){
            std::size_t max_index = std::distance(feat_tmp.begin(), std::max_element(feat_tmp.begin(), feat_tmp.end()));
            features.emplace_back(max_index);
            feat_tmp[max_index] = 0;
        }

        // --- SPLITTING ---

        root = new decision_tree_node(BRANCH);

        // add branches for each group (case)
        for(auto grp_id = 0; grp_id < n_groups; ++grp_id){

            auto grp_ds = get_group_as_ds(ds, features[current_feature_idx], grp_id);
            
            // check stopping condition
            if(eval_sc(grp_ds) > sc_threshold){
                // time to stop

                auto [ml, _] = majority_label(grp_ds);

                // add a leaf node
                root->branches.emplace_back(
                    new decision_tree_node(
                        LEAF,
                        features[current_feature_idx],
                        grp_id,
                        ml
                    )
                );

                // update current feature
                ++current_feature_idx;
            }
            else{
                // split by current best feature



                std::cout << "split by current best feature" << std::endl;
            }
        }

    }


    /*
        returns predicted class_id
    */
    template <typename feat_t, std::size_t n_feat>
    std::size_t predict(const cls_sample<feat_t, n_feat> & sample){

    }


    /*
        builds a decision tree given a dataset (vector of cls_samples)
    */
    template <typename feat_t, std::size_t n_feat>
    void evaluate(const std::vector<cls_sample<feat_t, n_feat>> & dataset){



    }


};


}  // namespace dt