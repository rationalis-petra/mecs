#ifndef TEMPLATE_H
#define TEMPLATE_H

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
  int num_components;
  void** components;
} Template;

void delete_template(Template* template);

///@}
#endif
