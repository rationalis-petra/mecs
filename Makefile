debug_flags = -Wall -g -DDEBUG
libs = -lm -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

dirs = components systems templates engine engine/core engine/graphics engine/math 
obj_dir = $(addprefix build/,$(dirs))
src_dir = $(addprefix src/,$(dirs))

src = $(foreach dir,$(src_dir),$(wildcard $(dir)/*.c))
build = $(addprefix src,$(dirs))

debug_objects = $(src:.c=.od)
debug_objects := $(subst src/,build/,$(debug_objects))
debug_objects += build/main.od
debug_objects += build/libs/glad.od

include = -I include/ -I libs/include

.PHONY: debug run clean docs memcheck


debug: build/enigma_d

build/enigma_d: $(debug_objects)
	cc $(debug_flags) -o $@ $^ $(include) $(libs)

build/engine/core/base.od : src/engine/core/base.c
build/engine/core/query.od : src/engine/core/query.c
build/engine/core/template.od : src/engine/core/template.c

build/engine/math/vecmath.od : src/engine/math/vecmath.c

build/engine/graphics/window.od : src/engine/graphics/window.c
build/engine/graphics/shader.od : src/engine/graphics/shader.c

build/components/creature.od : src/components/creature.c
build/components/info.od : src/components/info.c
build/components/transform.od : src/components/transform.c

build/templates/enemy_template.od : src/templates/enemy_template.c
build/templates/player_template.od : src/templates/player_template.c

build/systems/utils.od : src/systems/utils.c
build/systems/enemy_system.od : src/systems/enemy_system.c
build/systems/input_system.od : src/systems/input_system.c
build/systems/render_system.od : src/systems/render_system.c

build/libs/glad.od : libs/src/glad.c

build/main.od : src/main.c

$(debug_objects): 
	cc -c $(debug_flags) -o $@ $^ $(include) $(libs)

run : debug
	build/enigma_d

clean:
	find . -name '*.od' -delete

docs :
	doxygen doxy_config

memcheck :
	valgrind --track-origins=yes ./build/enigma_d
