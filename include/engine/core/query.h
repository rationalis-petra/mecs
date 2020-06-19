#ifndef QUERY_H
#define QUERY_H
/** @file
 * Often, we want to ask the engine for a collection of entities matching
 * a certain criteria, e.g. all entities with a transform, or all entites
 * which are less than some distance from a point, etc. This kind of data
 * retreival can be done via a query on the engine. We have multiple 
 * functions to support this.
 */


///@addtogroup Query
///@{

#include <stdbool.h>

/** @brief The entity list datatype, which is used to store the output of a query
 * 
 * @details The entity list is essentially an array with two variables: the length
 *          (len) and array (entities). The entities array stores the integer ids
 *          which can be used to access the components of the entity via 
 *          get_component();
 */
typedef struct EntityList {
  int len;            ///< The number of entities in the list
  int* entities;      ///< An array of entity ids
} EntityList;


/** @brief Queries the system and returns a list of entities containing the provided components
 * 
 * @details A basic way to query information in the system. Gives only the entities which have
 *          the requested components, as represented by the input mask.
 *
 * @param[in] mask: A set of ComponentType enums which tell the query which components we want 
 *            the entities to have. 
 *
 * @return A list containing entities which have at least the desired components
 */

EntityList component_mask(int, ...);

/** @brief Queries the system to find entities which match some component function
 *
 * @details The function passed in itself takes in an integer representing an entity, which can
 *          be any 
 *          they appear in the mask. 
 *
 * @param[in] predicate: A function which returns some boolean value given an entity id.
 *            It is used to filter out all entities for which the predicate is false
 *
 * @return A list containing all entities which match the predicate
 */
EntityList predicate_mask(bool (*predicate)(int));

/** @brief Returns the first entity which matches some predicate function
 * 
 * @details To be used when you expect there to be only a single copy of an entity in the game.
 *          e.g. the player. Primarily exists to save efficiency, as the function can return the
 *          first hit. The engine iself makes no guarantee as to the uniqueness of the returned
 *          entity id
 *
 * @param[in] predicate: A function which returns some boolean value given an entity id.
 *            The function returns as soon as this value is true
 * 
 * @return an integer corresponding to the id of the first entity to match the predicate
 */
int first_match(bool (*predicate)(int));

///@}

#endif
