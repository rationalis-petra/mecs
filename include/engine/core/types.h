#ifndef TYPES_H
#define TYPES_H

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
typedef struct Template {
  void** components;
} Template;

void delete_template(Template* template);

typedef struct GenIndex {
  unsigned int index;
  unsigned int generation;
} GenIndex;

typedef struct IntList {
  int element;
  struct IntLIst* next;
} IntList;


/** @brief Contains potentially useful update arguments, which are most often useful in
 *
 */
typedef struct UpdateArgs {
  float dt;  ///< The time since the last frame was called
} UpdateArgs;

///@}
#endif
