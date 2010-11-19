#ifndef boxm2_sio_mgr_h_
#define boxm2_sio_mgr_h_
//:
// \file
#include <boxm2/boxm2_block.h>
#include <boxm2/boxm2_block_id.h>
#include <boxm2/boxm2_data_traits.h>
#include <boxm2/boxm2_data.h>

#include <vcl_iostream.h>

//: disk level storage class.
//  handles all of the synchronous IO read and write requests
class boxm2_sio_mgr
{
  public:

    //: loads block from disk
    static boxm2_block*   load_block(vcl_string dir, boxm2_block_id block_id); 
    
    //: saves block to disk
    static void           save_block(vcl_string dir, boxm2_block* block );

    //: load data from disk
    template <boxm2_data_type data_type> 
    static boxm2_data_base *  load_block_data(vcl_string dir, boxm2_block_id block_id); 
    
    //: saves data to disk
    template <boxm2_data_type data_type> 
    static void save_block_data(vcl_string dir, boxm2_block_id block_id, boxm2_data<data_type> * block_data );

    //TODO create data load and save functions

};
template <boxm2_data_type data_type> 
boxm2_data_base *  boxm2_sio_mgr::load_block_data(vcl_string dir, boxm2_block_id block_id)
{
    vcl_ostringstream ns;  // Declare an output string stream.
    ns << dir << boxm2_data_traits<data_type>::prefix() << block_id << ".bin";
    vcl_string filename = ns.str();

    //get file size
    unsigned long numBytes=vul_file::size(filename);

    //Read bytes into stream
    char * bytes = new char[numBytes]; 
    vcl_ifstream myFile (filename.c_str(), vcl_ios::in | vcl_ios::binary);
    myFile.read(bytes, numBytes);
    if (!myFile)
        vcl_cerr<<"boxm2_sio_mgr:: cannot read file "<<dir<<vcl_endl;

    //instantiate new block
    return new boxm2_data<data_type>(bytes,numBytes,block_id); 
}

//: saves block to disk
template <boxm2_data_type data_type> 
void boxm2_sio_mgr::save_block_data(vcl_string dir, boxm2_block_id block_id, boxm2_data<data_type> * block_data )
{
    vcl_ostringstream ns;  // Declare an output string stream.
    ns << dir << boxm2_data_traits<data_type>::prefix() << block_id << ".bin";
    vcl_string filename = ns.str();
  
    char * bytes = block_data->data_buffer(); 
    vcl_ofstream myFile (filename.c_str(), vcl_ios::out | vcl_ios::binary);
    myFile.write(bytes, block_data->buffer_length());  
    myFile.close();
    return;

}

#endif // boxm2_sio_mgr_h_
