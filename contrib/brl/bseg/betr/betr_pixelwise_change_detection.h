#ifndef betr_pixelwise_change_detection_h_
#define betr_pixelwise_change_detection_h_
//:
// \file
// \brief Change detection using pixel-wise methods from baml
// \author Tom Pollard
// \date October 12, 2016
//

#include <string>

#include <baml/baml_detect_change.h>
#include "betr_algorithm.h"

class betr_pixelwise_change_detection : public betr_algorithm
{
public:

  betr_pixelwise_change_detection(): 
    betr_algorithm("pixelwise_change_detection"),
    avg_prob_(0.0), method_( CENSUS ),
    i_offset_(0), j_offset_(0), change_img_(VXL_NULLPTR){}

  //: select the pixelwise appearance metric
  inline void set_metric( baml_change_detection_method m ){
    method_ = m; }

  //: process change
  virtual bool process();

  //: resulting change probability
  virtual double prob_change() const{return avg_prob_;}

  //: image of pixel-wise census probabilities
  virtual vil_image_resource_sptr change_image(
    unsigned& i_offset, unsigned& j_offset) const{
      i_offset = i_offset_; j_offset = j_offset_; return change_img_;}

private:
  
   //:results
  double avg_prob_;

  //: parameters
  baml_change_detection_method method_;
  unsigned i_offset_;
  unsigned j_offset_;
  vil_image_resource_sptr change_img_;
};
#endif   // DO NOT ADD CODE AFTER THIS LINE! END OF DEFINITION FOR CLASS betr_pixelwise_change_detection.
