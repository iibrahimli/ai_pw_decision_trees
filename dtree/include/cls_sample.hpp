#pragma once

#include <string>
#include <array>
#include <map>


namespace dt{


// map from class ids to class names
// easier to let the parser generate it from a file
using label_map = std::map<unsigned int, std::string>;


/*
    data sample (for classification = has a class label)

    n_feat:    number of features
    feat_t:    type of features (default float)
*/
template <typename feat_t, std::size_t n_feat>
struct cls_sample {

    // array of features
    std::array<feat_t, n_feat>  _features;

    // class label (id)
    unsigned int                _label_id;



    // default: all features and class_id initialized to zero
    cls_sample()
        :   _features{0},
            _label_id{0}
    {}


    // brace initializer list
    cls_sample(std::array<feat_t, n_feat> features, unsigned int label_id)
        :   _features{features},
            _label_id{label_id}
    {}


    // for ease of use of vector of samples like a matrix
    feat_t & operator [](std::size_t index){
        return _features.at(index);
    }


    // access (get or set) a feature
    feat_t & feat(std::size_t index)
    {
        return _features.at(index);
    }


    // access (get or set) label id
    unsigned int & label_id()
    {
        return _label_id;
    }


    // get class label as a string (decode using dict)
    std::string label(const label_map & dict)
    {
        return dict.at(_label_id);
    }

};


} // namespace dt