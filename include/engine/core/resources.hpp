#ifndef __RESOURCE_HPP
#define __RESOURCE_HPP


#include <string>

#include "world.hpp"


template <typename T> T* Resource::value() {
  return (T*) world.resources[T::type_id][idx];
}

template <typename T> void Resource::remove() {
  T* resource_val = (T*) world.resources[T::type_id][idx];
  world.resources[T::type_id].remove(idx);
  delete resource_val;
}


///@}
#endif
