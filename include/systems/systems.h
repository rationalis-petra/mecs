#ifndef SYSTEMS_H
#define SYSTEMS_H

void input_system(void);
void input_init(void);
void input_clean(void);

void enemy_system(void);
void enemy_init(void);
void enemy_clean(void);

void combat_system(void);
void combat_init(void);
void combat_clean(void);

void render_system(void);
void render_init(void);
void render_clean(void);

void physics_system(void);
void physics_init(void);
void physics_clean(void);

void ai_system(void);
void ai_init(void);
void ai_clean(void);
#endif
