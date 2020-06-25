#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "components/creature.h"
#include "components/info.h"
#include "components/transform.h"
#include "components/camera.h"
#include "components/rigidbody.h"

#ifndef NDEBUG
#include <stdio.h>
#endif

/**@defgroup Components
 * @brief Components are data structures which store information relating to a
 *        specific behaviour(s)
 *
 * @details Components are one of the core parts of the ECS, although they are
 *          completely defined by the user, exisiting only as void* in the 
 *          engine itself. The components module contains all user-defined types
 *          as well as an enum indexing them all. To see details on accessing
 *          components, see @link Query @endlink
 */

///@addtogroup Components
enum ComponentType {
		 TransformType,
		 InfoType,
		 CreatureType,
		 CameraType,
		 RigidBodyType,
};


#endif
