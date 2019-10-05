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
    label_id:  class label id (used with a label_dict)
*/
template <std::size_t n_feat, typename feat_t = float>
struct cls_sample {

    // counter of class ids. used during parsing, after that stores number of classes
    static unsigned int         max_label_id = 0;

    // array of features
    std::array<feat_t, n_feat>  _features;

    // class label (id)
    unsigned int                _label_id;



    // default: all features and class_id initialized to zero
    cls_sample()
        :   _features{0},
            _label_id{0},
    {
    }


    // brace initializer list
    cls_sample(std::array<feat_t> features, unsigned int label_id)
        :   _features{features},
            _label_id{label_id}
    {
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