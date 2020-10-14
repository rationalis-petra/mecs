#ifndef __GEN_DICT_H
#define __GEN_DICT_H

#include "engine/core/types.h"

typedef struct GenDict GenDict;

/** @brief creates a new dictionary
 */
GenDict* new_dict();

/** @brief deletes a dictionary
 */
void delete_dict(GenDict* tree);

/** @brief inserts a key, value pair into a dictionary
 *
 * @details Will search through the dictionary. If it finds a value
 * already existing for the given key, then it will replace the old
 * value with the new
 *
 * @param[in] dictionary: A pointer to a dictionary - as created with new_dict()
 *
 * @param[in] key: a (string) key value that we wish to make the key for this value
 *
 * @param[in] value: A generational index to store in the dictionary
 */
void dict_insert(GenDict* dictionary, char* key, GenIndex value);

/** @brief retrieves a value with a given key,
 *
 * @param[in] dictionary
 *
 * @param[in] key
 *
 * @param[out] value. A pointer to generational index, which will be assigned to
 * the generational index in the tree. (will not be a copy, *do not free* as will
 * cause undefined behaviour.
 *
 * @returns Error code: true if resource could not be found
 */
int dict_get(GenDict* dictionary, char* key, GenIndex* value);

/** @brief deletes the value corresponding to a given key
 *
 * @details: Will look for item in tree using the key. If it finds
 * the item, it will remove it, returning 0. Otherwise, it will
 * return 1.
 *
 * @param[in]
 *
 * @returns Error code: true if resource could not be found
 */
int dict_delete(GenDict* dictionary, char* key);

#endif
