# Introduction

## The Game
## The Engine
The engine is based around an *Entity Component System* (ECS), and allows queries loosely inspired by relational 
database systems. There are several important concepts in the engine:

### Components
A component in the system is a *data structure*, which captures some information about an /entity/ (see below). Often,
components are a part of many entities. Consider the example of a goblin enemy - it may contain the following components:
    + Kinematic - storing the position and velocity of the goblin
    + Creature - a standard stat-block: stores health, dexterity, etc.
    + Inventory - a standard data-structure which describes what a creature is holding (and where)
    + AI - describes variables which effect the behaviour of our entity.
    
This would likely be a subset of all possible components an entity could have, e.g. there may also be **Material**, 
**Abilities** and **Memories**. In this case, an enemy would be a record with NULL entries in those locations.
Because components are user-defined, we use the `register_component` method. It is important to note that we
*must* register all components before use else undefined behaviour ensues. Attempting to do this returns an error if
the DEBUG variable is defined. 

### Entities
An entity is 

### Systems



