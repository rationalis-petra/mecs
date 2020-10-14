#ifndef __GEN_LIST_H_
#define __GEN_LIST_H_

// GenList = Generic List
typedef struct GenList GenList;

/**@brief Creates a new Generic List
 */
GenList* new_genlist(void);

/**@brief Deletes a dlist
 *
 * @details Frees all elements and removes the information the pointers point to
 */
void delete_genlist(GenList* list);

/**@brief Adds an element to the list, consuming the value given to it (i.e. modifying
 *        the element pointed to will modify the list element)
 */
void genlist_push(GenList* list, void* val);

/**@brief Removes the first element from the list, returning the pointer to the
 *        head's contents*/
int genlist_pop(GenList* list, void** val);

/**@brief Inspect the head element
 */
int genlist_head(GenList* list, void* val);

/**@brief Inspect the tail, as a list
 */
//int genlist_tail(GenList* list, GenList* val);

/**@brief Insert an element at a specific location via index
 */
//int genlist_insert(GenList* list, void* val, int index);

#endif // __GEN_LIST_H_
