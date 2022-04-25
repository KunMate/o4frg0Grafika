#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    for(int i = 0; i < BRICKNUMBER; i++) {
        load_model(&(scene->cube[i]), "assets/models/pillar.obj");
    }
    load_model(&(scene->power), "assets/models/powerup.obj");
    scene->powerup = load_texture("assets/textures/powerup.png");
    scene->otexture = load_texture("assets/textures/brick2.jpg");
    load_model(&(scene->cube2), "assets/models/terrain.obj");
    scene->texture_id = load_texture("assets/textures/ground.jpg");
    load_model(&(scene->sky), "assets/models/sky.obj");
    scene->skybox = load_texture("assets/textures/sky.jpg");

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    scene->power_rotation.x = 0.0;
    scene->power_rotation.y = 0.0;
    scene->power_rotation.z = 45;
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 60.0;
}

void set_lighting()
{
    Light light;
    light.ambient[0] = 0.5f;
    light.ambient[1] = 0.7f;
    light.ambient[2] = 0.9f;
    float ambient_light[] = { 0.3f, 0.4f, 0.3f, 0.3f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 50.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, Camera* camera, double time)
{
    scene->power_rotation.z += 2;
    int collected = 0;
    double dt = 0;
    //itt kell csinalni az ugrast meg az utkozes vizsgalatot is
    //1
    if(camera->position.x > 11.5 && camera->position.x < 12.5 && camera->position.y > 1.5 && camera->position.y < 2.4 && camera->position.z > 2.44 && camera->position.z < 2.5)
    {
        camera->speed.z = 0;
        dt = 0;
    }//2
    else if(camera->position.x > 9.5 && camera->position.x < 10.5 && camera->position.y > 4.5 && camera->position.y < 5.5 && camera->position.z > 2.44 && camera->position.z < 2.5)
    {
        camera->speed.z = 0;
        dt = 0;
    }//3
    else if(camera->position.x > 4.4 && camera->position.x < 5.4 && camera->position.y > 1.5 && camera->position.y < 2.5 && camera->position.z > 2.54 && camera->position.z < 2.6)
    {

        camera->speed.z = 0;
        dt = 0;
    }//4
    else if(camera->position.x > 5 && camera->position.x < 6 && camera->position.y > 8 && camera->position.y < 9 && camera->position.z > 2.34 && camera->position.z < 2.4)
    {
        camera->speed.z = 0;
        dt = 0;
    }//5
    else if(camera->position.x > -0.4 && camera->position.x < 0.4 && camera->position.y > 4.5 && camera->position.y < 5.5 && camera->position.z > 2.84 && camera->position.z < 2.9)
    {
        camera->speed.z = 0;
        dt = 0;
    }//6
    else if(camera->position.x > -6.5 && camera->position.x < -5.5 && camera->position.y > 0.5 && camera->position.y < 1.5 && camera->position.z > 2.54 && camera->position.z < 2.6)
    {
        camera->speed.z = 0;
        dt = 0;
    }//7
    else if(camera->position.x > -13.5 && camera->position.x < -12.5 && camera->position.y > 1.5 && camera->position.y < 2.5 && camera->position.z > 2.34 && camera->position.z < 2.4)
    {
        camera->speed.z = 0;
        dt = 0;
    }//8
    else if(camera->position.x > -15 && camera->position.x < -14 && camera->position.y > -7.5 && camera->position.y < -6.5 && camera->position.z > 2.14 && camera->position.z < 2.2)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(dt < 5) {
        dt += time*1.06;
        camera->speed.z -= dt;
        if(camera->position.z < 1.2){
            camera->position.x = 12;
            camera->position.y = 2;
            camera->position.z = 3;
            camera->speed.z = 0;
                camera->speed.x = 0;
                camera->speed.y = 0;
        }
    }

}
void reset_camera(Camera* camera){
    camera->position.x = 12;
    camera->position.y = 2;
    camera->position.z = 3;
    camera->speed.z = 0;
    camera->speed.x = 0;
    camera->speed.y = 0;
}
void render_scene(const Scene* scene, Camera* camera)
{
    set_material(&(scene->material));
    set_lighting();
    glBindTexture(GL_TEXTURE_2D, scene->skybox);
    draw_model(&(scene->sky));
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    draw_model(&(scene->cube2));
    //draw_origin();
    //p1
    glPushMatrix();
    glTranslatef(12, 2, 0);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[0]));
    glPopMatrix();
    //p2
    glPushMatrix();
    glTranslatef(10, 5, -0.20);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[1]));
    glPopMatrix();
    //p3
    glPushMatrix();
    glTranslatef(5.5, 8.5, -0.14);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[2]));
    glPopMatrix();
    //p4
    glPushMatrix();
    glTranslatef(5, 2, 0);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[3]));
    glPopMatrix();
    //p5
    glPushMatrix();
    glTranslatef(0, 5, -1.5);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[4]));
    glPopMatrix();
    //p6
    glPushMatrix();
    glTranslatef(0, 5, 0.25);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[5]));
    glPopMatrix();
   // p7
    glPushMatrix();
    glTranslatef(-6, 1, -0.2);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[6]));
    glPopMatrix();
    //p8
    glPushMatrix();
    glTranslatef(-13, 2, -0.16);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[7]));
    glPopMatrix();
    //p9
    glPushMatrix();
    glTranslatef(-14.5, -7, -0.5);
    glBindTexture(GL_TEXTURE_2D, scene->otexture);
    draw_model(&(scene->cube[8]));
    glPopMatrix();
    //powerup
    glPushMatrix();
    glTranslatef(5, 2, 2.4);
    glRotatef(scene->power_rotation.z, 0,0,1);
    if(camera->position.x > 4.4 && camera->position.x < 5.4 && camera->position.y > 1.5 && camera->position.y < 2.5 && camera->position.z > 2 && camera->position.z < 3.5)
    {
        glTranslatef(0,0,-5);
    }
    glBindTexture(GL_TEXTURE_2D, scene->powerup);
    draw_model(&(scene->power));

    glPopMatrix();

}

void set_camera_jump_speed(Camera* camera, double speed)
{
    if(camera->speed.z == 0){
    camera->speed.z = speed;
    }else return;
}
