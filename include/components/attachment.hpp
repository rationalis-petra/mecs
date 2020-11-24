#ifndef __ATTACHMENT_HPP_
#define __ATTACHMENT_HPP_

#include "engine.hpp"

///@addtogroup Components
///@{

/** @brief The attachment componet represents physical connections between entities
 *
 * @details The attachment component represents a /physical attachment/ to something,
 *          and is stored as a tuple containing an ID and a vector, which represents
 *          the ideal displacement between the two objects. Because multiple attachments
 *          can be on one element, these tuples are stored in a list;
 */

class AttachmentElement : public Component {
public:
  static unsigned int type_idx;
  Entity id;
  Vec3f displacement;

  AttachmentElement();
  ~AttachmentElement();
};


///@}
#endif // __ATTACHMENT_H_
