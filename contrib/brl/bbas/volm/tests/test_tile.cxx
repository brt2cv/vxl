#include <testlib/testlib_test.h>
#include <vcl_iostream.h>
#include <vpl/vpl.h>
#include <vsl/vsl_binary_io.h>
#include <bbas/volm/volm_tile.h>

static void test_tile()
{
  vcl_vector<volm_tile> tiles = volm_tile::generate_p1_wr1_tiles();
  TEST("tile 1", tiles[0].lat_, 37);

  double lat, lon, elev;
  tiles[0].cam_.lvcs()->get_origin(lat, lon, elev);

  double lat2, lon2;
  tiles[0].img_to_global(0, tiles[0].nj_, lon2, lat2);
  TEST_NEAR("tile 1 img to global", lat2, 37, 0.01);

  unsigned i, j;
  tiles[0].img_to_global(0, tiles[0].nj_-1, lon2, lat2);
  TEST("tile1 global to img", tiles[0].global_to_img(lon2, lat2, i, j), true);
  TEST("tile1 global to img", i == 0, true);
  TEST("tile1 global to img", j == tiles[0].nj_-1, true);

  TEST("tile1 global to img", tiles[0].global_to_img(lon2+5, lat2, i, j), false);

  volm_tile tt(37, -118, tiles[0].scale_i_, tiles[0].scale_j_, tiles[0].ni_, tiles[0].nj_);
  TEST("tt global to img", tt.global_to_img(lon2, lat2, i, j), true);
  TEST("tt global to img", i == 0, true);
  TEST("tt global to img", j == tt.nj_-1, true);

  //volm_tile ttt(37.622991f, 118.209999f, 'N', 'W', 1.108007f, 0.930012f, (unsigned)10000, (unsigned)10000);
  volm_tile ttt(37.622991f, 118.209999f, 'N', 'W', 1.0f, 0.9f, (unsigned)10000, (unsigned)10000);
  vcl_cout << "width is: " << ttt.calculate_width() << " meters = " << ttt.calculate_width()/1000.0 << " km..\n"
           << "height is: " << ttt.calculate_height() << " meters = " << ttt.calculate_height()/1000.0 << " km..\n"
           << "one pixel is: " << ttt.calculate_width()/ttt.ni_ << " meter.." << vcl_endl;
  ttt.write_kml("./t0.kml", 1000);

  vsl_b_ofstream ofs("test_tile.bin");
  tiles[0].b_write(ofs);
  ofs.close();

  vsl_b_ifstream ifs("test_tile.bin");
  volm_tile t;
  t.b_read(ifs);
  TEST("tile 2", t.lat_, 37);
  double lat3, lon3;
  t.img_to_global(0, t.nj_, lon3, lat3);
  TEST_NEAR("tile 2 img to global lat ", lat3, lat2, 0.01);
  TEST_NEAR("tile 2 img to global lon ", lon3, lon2, 0.01);
}


TESTMAIN(test_tile);
