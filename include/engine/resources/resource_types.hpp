#ifndef __RESOURCE_TYPES_H_
#define __RESOURCE_TYPES_H_
// texutre

extern int TextureType;

void* load_texture(const char* path);
void delete_texture(void* texture);

// Mesh

extern int MeshType;

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int num_triangles;
} Mesh;

void* load_mesh(const char* path);
void delete_mesh(void* mesh);

#endif
