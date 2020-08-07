#ifndef __ATTACHMENT_H_
#define __ATTACHMENT_H_

#include "engine.h"

///@addtogroup Components
///@{

/** @brief The attachment componet represents physical connections between entities
 *
 * @details The attachment component represents a /physical attachment/ to something,
 *          and is stored as a tuple containing an ID and a vector, which represents
 *          the ideal displacement between the two objects. Because multiple attachments
 *          can be on one element, these tuples are stored in a list;
 */

typedef struct {
    GenIndex id;
    Vec3f displacement;
} AttachmentElement;

typedef GenList AttachmentList;

void* new_attachment(void);

void delete_attachment(void* attachment);

///@}
#endif // __ATTACHMENT_H_
