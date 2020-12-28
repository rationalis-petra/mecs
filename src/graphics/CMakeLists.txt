add_library(graphics OBJECT
                     render_system.cpp
                     shader.cpp
                     window.cpp

                     # components: for interacting with the ecs
                     camera.cpp
                     model.cpp

                     # Resource: contains loader/remover 
                     resources/mesh.cpp
                     resources/texture.cpp)
