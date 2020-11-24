#ifndef __TYPES_H
#define __TYPES_H

///@addtogroup Base
///@{

/**@brief A struct for containing intermediate results of a new entity
 *
 * @details The template struct stores an array of pointers to copmonets
 *          the engine uses the array to load the different components 
 *          into the correct entity slots. The num_components variable
 *          is set in the new_template function to the current number of
 *          components in the system.
 */
class Template{
public:
  void** components;

  ~Template();
};


struct GenIndex {
  unsigned int index;
  unsigned int generation;
};

typedef GenIndex EntityID;
typedef GenIndex ResourceID;

/** @brief Contains potentially useful update arguments, which are most often useful in
 *
 */
class UpdateArgs {
public:
  float dt;  ///< The time since the last frame was called
};
///@}



#endif
