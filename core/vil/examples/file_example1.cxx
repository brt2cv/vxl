//:
// \file
// \brief Example of creating and using an image data object
// \author Ian Scott

#include <iostream>
#ifdef _MSC_VER
#  include "vcl_msvc_warnings.h"
#endif
#include "vil/vil_load.h"
#include "vil/vil_image_view.h"
#include "vil/vil_print.h"

int
main(int argc, char ** argv)
{
  if (argc < 2)
  {
    std::cerr << "Specify an image filename\n";
    return 3;
  }

  std::cout << "Load " << argv[1] << " into an image data object\n";


  // This is how we initialise an image data object.

  vil_image_resource_sptr data = vil_load_image_resource(argv[1]);

  if (!data)
  {
    std::cerr << "Couldn't load " << argv[1] << std::endl;
    return 3;
  }

  // This is how we get some image pixels from it.

  vil_image_view<unsigned char> uc_view = data->get_view(0, data->ni(), 0, data->nj());

  vil_print_all(std::cout, uc_view);

  return 0;
}
