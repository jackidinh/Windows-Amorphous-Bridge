
#ifndef example_GENERATED_FastDDSTOFB_H_
#define example_GENERATED_FastDDSTOFB_H_

#include "example_reader.h"
#include "example_builder.h"
#include "Person.hpp"

#ifndef example_FastDDS_TYPES_DEFINED
//Leaving out for now
//#include "exampleTypeSupport.hh"
#endif
//Leaving out for now
//#include "FACEBridgeClasses.h"


  
namespace test_msgs_pkg {
namespace msg{
 


inline static void CreatePersonFromFastDDS(flatcc_builder_t* _fbb, Person _o)
{
	example_Person_id_add(_fbb, _o.id());
	if (_o.name().size() > 0) example_Person_name_create_str(_fbb, _o.name().c_str());

} 

inline static void CreateFastDDSFromPerson(const example_Person_table_t root, Person& o_)
{
    size_t len = 0;
	size_t slen = len;
	len = slen;

    //o_.clear();

	o_.id(example_Person_id(root));
  	//slen = example_Person_name_is_present(root) ? strlen(example_Person_name(root)) + 1 : 0;
	//if (slen)
	//{
	    //o_.name = new char[slen];
		//memcpy(o_.name, example_Person_name(root), slen);
	//}

	if(example_Person_name_is_present(root)){
		o_.name(example_Person_name(root));
	}
}

} // msg
}//test_msgs_pkg


#endif  //FLATBUFFERS_GENERATED_example_FastDDSTOFB_H_