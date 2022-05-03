#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>
#define BRICKNUMBER 10

typedef struct Light {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float speed;
} Light;

typedef struct Scene
{
    Light light;
    Model cube[BRICKNUMBER];
    Model cube2;
    Model power;
    vec3 power_rotation;
    Model sky;
    Material material;
    GLuint texture_id;
    GLuint otexture;
    GLuint powerup;
    GLuint skybox;
    GLuint helptexture;
    //GLuint wint;
    //int win;
    int helpstate;
} Scene;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, Camera* camera, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene, Camera* camera);

/**
 * Draw the origin of the world coordinate system.
 */
void set_camera_jump_speed(Camera* camera, double speed);
void reset_camera(Camera* camera);
void set_light_speed(Scene *scene, float speed);
void draw_help(Scene* scene, GLuint helptexture);
#endif /* SCENE_H */
