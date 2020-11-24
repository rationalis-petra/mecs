#ifndef __INFO_H
#define __INFO_H

#include <string>

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
class Info {
public:
  static unsigned type_idx;
  
  std::string name;    ///< The name is not to be used as an identifier in-program, merely as a "pretty-id" for the player
  enum Tag tags; ///< The see tags enum for more data.

  Info();
  Info(std::string, Tag);
  ~Info();
};


///@}
#endif
