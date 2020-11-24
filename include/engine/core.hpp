/** @defgroup Core
 *
 * @{
 * @defgroup Base
 * @brief The basic functions for interfacing with the ECS
 * 
 * @defgroup Query
 * @brief Functions for accessing components based on conditions
 * 
 * @details The functinos in query are deisgned primarily for defining and
 * programming a system. They provide a variety of ways to access the 
 * components in the underlying ECS;
 *
 * @defgroup State
 * @brief The state header contains access to the system state - for internal use only
 *
 * @}
 */

#include "engine/core/world.hpp"
#include "engine/core/entity.hpp"
#include "engine/core/component.hpp"
#include "engine/core/types.hpp"
#include "engine/core/resources.hpp"

