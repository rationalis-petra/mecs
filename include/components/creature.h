#ifndef CREATURE_H
#define CREATURE_H

/** @file
 * @brief contains the creture struct
 */

///@addtogroup Components
///@{

/** @brief The creature struct contains the basic stat block for all creatures, and
 *         auxilliary information. 
 * 
 * @details Based off the standard D&D stat-block, contains basic informatino on 
 *           strength, dexterity, armour, health, etc.
 */
typedef struct Creature {
  int strength;       //!< The strength stat determines physical strength
  int dexterity;      //!< The dexterity stat determines physical finesse
  int constitution;   //!< The constitution state determines physical hardiness
  int intelligence;   //!< The intelligence stat determines ability to think & memorize
  int wisdom;         //!< The wisdom stat is a descriptor of worldly knowledge
  int charisma;       //!< The charisma stat is a descriptor of charm and force of will

  int health;
} Creature;

void* new_creature();

void delete_creature(void* creature);

///@}
#endif
