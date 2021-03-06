#ifndef mfpf_ssd_vec_cost_builder_h_
#define mfpf_ssd_vec_cost_builder_h_
//:
// \file
// \brief Builder for mfpf_ssd_vec_cost objects.
// \author Tim Cootes

#include <iostream>
#include <iosfwd>
#include <vector>
#include <mfpf/mfpf_vec_cost_builder.h>
#include <vnl/vnl_vector.h>
#ifdef _MSC_VER
#  include <vcl_msvc_warnings.h>
#endif

//: Builder for mfpf_ssd_vec_cost objects.
//  Computes mean and weights given the training data.
//  Currently uses the mean absolute difference to estimate the
//  weights (rather than variance, which is not so robust).
class mfpf_ssd_vec_cost_builder : public mfpf_vec_cost_builder
{
 private:
  //: Minimum variance allowed
  double min_var_;

  //: Space to record examples
  std::vector<vnl_vector<double> > data_;

  //: Define default values
  void set_defaults();
 public:

  // Dflt ctor
  mfpf_ssd_vec_cost_builder();

  // Destructor
  ~mfpf_ssd_vec_cost_builder() override;


  //: Create new mfpf_ssd_vec_cost on heap
  mfpf_vec_cost* new_cost() const override;

  //: Initialise building
  // Must be called before any calls to add_example(...)
  void clear(unsigned n_egs) override;

  //: Add one example to the model
  void add_example(const vnl_vector<double>& v) override;

  //: Build object from the data supplied in add_example()
  void build(mfpf_vec_cost&) override;

  //: Initialise from a string stream
  bool set_from_stream(std::istream &is) override;

  //: Name of the class
  std::string is_a() const override;

  //: Create a copy on the heap and return base class pointer
  mfpf_vec_cost_builder* clone() const override;

  //: Print class to os
  void print_summary(std::ostream& os) const override;

  //: Version number for I/O
  short version_no() const;

  //: Save class to binary file stream
  void b_write(vsl_b_ostream& bfs) const override;

  //: Load class from binary file stream
  void b_read(vsl_b_istream& bfs) override;
};

#endif // mfpf_ssd_vec_cost_builder_h_
