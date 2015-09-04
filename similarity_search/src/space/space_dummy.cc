/**
 * Non-metric Space Library
 *
 * Authors: Bilegsaikhan Naidan (https://github.com/bileg), Leonid Boytsov (http://boytsov.info).
 * With contributions from Lawrence Cayton (http://lcayton.com/) and others.
 *
 * For the complete list of contributors and further details see:
 * https://github.com/searchivarius/NonMetricSpaceLib 
 * 
 * Copyright (c) 2014
 *
 * This code is released under the
 * Apache License Version 2.0 http://www.apache.org/licenses/.
 *
 */

#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

#include "space/space_dummy.h"
#include "experimentconf.h"

namespace similarity {

template <typename dist_t>
dist_t SpaceDummy<dist_t>::HiddenDistance(const Object* obj1, const Object* obj2) const {
  LOG(LIB_INFO) << "Calculating the distance between objects: " << obj1->id() << " and " << obj2->id() << endl;
  CHECK(obj1->datalength() > 0);
  CHECK(obj1->datalength() == obj2->datalength());
  /* 
   * Data in the object is accessed using functions:
   * obj1->datalength()
   * obj1->data();
   * obj2->datalength()
   * obj2->data();
   */
  return static_cast<dist_t>(0);

} 

/** Sample standard functions to read/write/create objects */ 

template <typename dist_t>
unique_ptr<DataFileInputState> SpaceDummy<dist_t>::OpenReadFileHeader(const string& inpFileName) const {
  return unique_ptr<DataFileInputState>(new DataFileInputState(inpFileName));
}

template <typename dist_t>
unique_ptr<DataFileOutputState> SpaceDummy<dist_t>::OpenWriteFileHeader(const string& outFileName) const {
  return unique_ptr<DataFileOutputState>(new DataFileOutputState(outFileName));
}

template <typename dist_t>
unique_ptr<Object> 
SpaceDummy<dist_t>::CreateObjFromStr(IdType id, LabelType label, const string& s,
                                            DataFileInputState* pInpStateBase) const {
  // Object that stores the string
  return unique_ptr<Object>(new Object(id, label, s.size(), s.data())); 
}

template <typename dist_t>
string SpaceDummy<dist_t>::CreateStrFromObj(const Object* pObj) const {
  return "";
}

template <typename dist_t>
bool SpaceDummy<dist_t>::ReadNextObjStr(DataFileInputState &inpState, string& strObj, LabelType& label) const {
  if (!inpState.inp_file_) return false;
  if (!getline(inpState.inp_file_, strObj)) return false;
  inpState.line_num_++;
  return true;
}

template <typename dist_t>
void SpaceDummy<dist_t>::WriteNextObj(const Object& obj, DataFileOutputState &outState) const {
  string s = CreateStrFromObj(&obj);
  outState.out_file_ << s << endl;
}
/** End of standard functions to read/write/create objects */ 

 

template class SpaceDummy<int>;
template class SpaceDummy<float>;
template class SpaceDummy<double>;

}  // namespace similarity
