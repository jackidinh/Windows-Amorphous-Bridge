 

#ifndef example_GENERATED_PBTOFB_H_
#define example_GENERATED_PBTOFB_H_

#include "example_reader.h"
#include "example_builder.h"
#include "example.pb.h" //FIXED
//Don't know if needed
//#include "FACE/DM/example/tss_types.h"

  

//Leaving out for now
//namespace FACE {
//namespace DM {

 
namespace example {
inline static void CreatePersonFromPB(flatcc_builder_t* _fbb, const example::Person& _o)
{

example_Person_id_add(_fbb, _o.id());


//if (_o.name.buffer()) example_Person_name_create_str(_fbb, _o.name.buffer());

if(!_o.name().empty()){ //FIXED 
   auto name_ref = flatbuffers_string_create_str(_fbb, _o.name().c_str());
   example_Person_name_add(_fbb, name_ref);
}

} 


inline static void CreatePBFromPerson(const example_Person_table_t root, example::Person& o_)
{


 


	o_.set_id(example_Person_id(root)); //FIXED
	


  	//slen = example_Person_name_is_present(root) ? (FACE::UnsignedLong)strlen(example_Person_name(root)) + 1 : 0;
	//o_.name.resize(slen);
	if (example_Person_name_is_present(root))
	{
		o_.set_name(example_Person_name(root));
	}
	else
	{
	o_.clear_name();
	}


};

} // namespace example

//} // namespace DM
//} // namespace FACE

#endif  //FLATBUFFERS_GENERATED_example_PBTOFB_H_