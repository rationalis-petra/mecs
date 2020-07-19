#ifndef __RESOURCES_H
#define __RESOURCES_H

#include "types.h"

/** @file
 *
 * @brief Resource management facilities - allows registering, loading and destruction of resources.
 */

///@addtogroup Resources
///@{

/** @brief creates a new resource type, assigning a type id and a program to load types of that resource
 *
 * @details This creates an array of void*, which will store pointers to that resource type. Further, it allows
 *          creation of new resources of that type, via the resource_loader function.
 *
 * @param[in] resource_loader: a function which will take a path and a string containing any additional information,
 *            and return a pointer to a loaded resource
 * @param[in] resource_destructor: a function which will delete a resource
 */
int register_resource_type(void* (resource_loader)(char* path), void (resource_destructor)(void* resource));

/** @brief looks for a resource which was loaded with the path given. If no such resource can be located, will load
 *
 *
 * @details This will take a resource type, path and optional arguments, and call the correct resource_loader function,
 *          storing the result for use as a shared resource. it will return a index to use.
 *
 * @param[in] type: the type of the resource to be loaded, as returned by register_resource_type
 *
 * @param[in] path: the path of the resource to be loaded
 *
 * @param[in] args: any additional arguments to provide to the resource loader
 */
GenIndex get_index(int type, char* path);

void* get_resource(int type, GenIndex resource_id);

/** @brief deletes a resource with a given id
 *
 * @details This will attempt to delete a resource of the given type, and do nothing if it is already deleted.
 *
 * @param[in] resource_id: a generational index describing which resource to delete
 */
void delete_resource(int type, GenIndex resource_id);

void delete_resource_named(int type, char* path);

///@}
#endif
