#ifndef INFO_H
#define INFO_H

/**@file 
 * @brief the info component stores useful yet miscellaneous information
 *
 * @details The info component is (hopefully) a temporary component which
 *          currently stores an entity's name and any relevant tags
 */

///@addtogroup Components
///@{

/**@brief The tag enum is a definition of flags which are bit-aligned
 */
enum Tag {  
	  PlayerTag = 1,
	  EnemyTag = 2,
	  FriendlyTag = 4,
};

/**@brief The info struct stored miscellaneous information about an entity
 */
typedef struct Info {
  char* name;    ///< The name is not to be used as an identifier in-program, merely as a "pretty-id" for the player
  enum Tag tags; ///< The see tags enum for more data.
} Info;

void* new_info();

void delete_info(void* info);

///@}
#endif
