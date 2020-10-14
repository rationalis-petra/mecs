#ifndef __COMPONENTS_H
#define __COMPONENTS_H

#include "components/model.h"
#include "components/camera.h"

#include "components/rigidbody.h"
#include "components/attachment.h"

#include "components/sensor.h"
#include "components/actuator.h"
#include "components/agent.h"

#include "components/info.h"

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

extern int ModelType;
extern int CameraType;

extern int RigidBodyType;
extern int AttachmentType;

extern int SensorType;
extern int ActuatorType;
extern int AgentType;

extern int InfoType;

#endif
