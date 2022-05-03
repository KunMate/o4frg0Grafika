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
    scene->light.ambient[0] = 0.3f;
    scene->light.ambient[1] = 0.3f;
    scene->light.ambient[2] = 0.3f;
    scene->light.ambient[3] = 1.0f;

    scene->power_rotation.x = 0.0;
    scene->power_rotation.y = 0.0;
    scene->power_rotation.z = 0.0;
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

    scene->helpstate = 0;
    
    //scene->wint = load_texture("assets/textures/winner.jpg");
}

void set_lighting(Scene* scene)
{
    float ambient_light[] = { scene->light.ambient[0], scene->light.ambient[1], scene->light.ambient[2], scene->light.ambient[3] };
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
    double dt = 0;
    //itt kell csinalni az ugrast meg az utkozes vizsgalatot is
    //1
    if(camera->position.x > 11.5 && camera->position.x < 12.5 && camera->position.y > 1.5 && camera->position.y < 2.4 && camera->position.z > 2.3 && camera->position.z < 2.5)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > 11.35 && camera->position.x < 12.6 && camera->position.y > 1.35 && camera->position.y < 2.6 && camera->position.z < 2.3){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    //2
    else if(camera->position.x > 9.5 && camera->position.x < 10.5 && camera->position.y > 4.5 && camera->position.y < 5.5 && camera->position.z > 2.35 && camera->position.z < 2.5)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > 9.3 && camera->position.x < 10.65 && camera->position.y > 4.35 && camera->position.y < 5.6 && camera->position.z < 2.35){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    //3
    else if(camera->position.x > 4.4 && camera->position.x < 5.4 && camera->position.y > 1.5 && camera->position.y < 2.5 && camera->position.z > 2.4 && camera->position.z < 2.6)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > 4.2 && camera->position.x < 5.6 && camera->position.y > 1.3 && camera->position.y < 2.65 && camera->position.z < 2.4){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    //4
    else if(camera->position.x > 5 && camera->position.x < 6 && camera->position.y > 8 && camera->position.y < 9 && camera->position.z > 2.2 && camera->position.z < 2.4)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > 4.65 && camera->position.x < 6.25 && camera->position.y > 7.5 && camera->position.y < 8.75 && camera->position.z < 2.2){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    //5
    else if(camera->position.x > -0.4 && camera->position.x < 0.4 && camera->position.y > 4.5 && camera->position.y < 5.5 && camera->position.z > 2.7 && camera->position.z < 2.9)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > -0.6 && camera->position.x < 0.6 && camera->position.y > 4.3 && camera->position.y < 5.7 && camera->position.z < 2.7){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    //6
    else if(camera->position.x > -6.5 && camera->position.x < -5.5 && camera->position.y > 0.5 && camera->position.y < 1.5 && camera->position.z > 2.4 && camera->position.z < 2.6)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > -6.7 && camera->position.x < -5.3 && camera->position.y > 0.3 && camera->position.y < 1.7 && camera->position.z < 2.4){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    //7
    else if(camera->position.x > -13.5 && camera->position.x < -12.5 && camera->position.y > 1.5 && camera->position.y < 2.5 && camera->position.z > 2.2 && camera->position.z < 2.4)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > -13.7 && camera->position.x < -12.3 && camera->position.y > 1.3 && camera->position.y < 2.7 && camera->position.z < 2.2){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    //8
    else if(camera->position.x > -15 && camera->position.x < -14 && camera->position.y > -7.5 && camera->position.y < -6.5 && camera->position.z > 2.05 && camera->position.z < 2.2)
    {
        camera->speed.z = 0;
        dt = 0;
    }
    else if(camera->position.x > -15.2 && camera->position.x < -13.8 && camera->position.y > -7.7 && camera->position.y < -6.3 && camera->position.z < 2.05){
        camera->speed.x=0;
        camera->speed.y=0;
    }
    else if(dt < 5) {
        dt += time*1.5;
        camera->speed.z -= dt;
    }

    for(int i=0; i<4; i++){
        scene->light.ambient[i] += scene->light.speed * time;
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
    set_lighting(scene);
    if(scene->helpstate == 1){
        //glBindTexture(GL_TEXTURE_2D, scene->helptexture);
        draw_help(scene, scene->helptexture);
    }
    if(camera->position.x > -15 && camera->position.x < -14 && camera->position.y > -7.5 && camera->position.y < -6.5 && camera->position.z > 2.05 && camera->position.z < 2.2)
    {
        draw_win(scene, scene->helptexture);
    }
    /*if(scene->win == 1){
        glBindTexture(GL_TEXTURE_2D, scene->wint);
        draw_win(scene->wint);
    }*/
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
        glRotatef(scene->power_rotation.z, 0, 0, 1);
        if (camera->position.x > 4.4 && camera->position.x < 5.4 && camera->position.y > 1.5 &&
            camera->position.y < 2.5 && camera->position.z > 2 && camera->position.z < 3.5) {
            glTranslatef(0, 0, -5);
        }
        glBindTexture(GL_TEXTURE_2D, scene->powerup);
        draw_model(&(scene->power));
    glPopMatrix();


}
void draw_help(Scene* scene, GLuint helptexture){

        scene->helptexture = load_texture("assets/textures/help.jpg");
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, helptexture);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3d(-3, 2, -4);
        glTexCoord2f(1, 0);
        glVertex3d(3, 2, -4);

        glTexCoord2f(1, 1);
        glVertex3d(3, -2, -4);

        glTexCoord2f(0, 1);
        glVertex3d(-3, -2, -4);
        glEnd();

}
void draw_win(Scene* scene, GLuint helptexture){
    scene->helptexture = load_texture("assets/textures/winner.jpg");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, helptexture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-3, 2, -4);
    glTexCoord2f(1, 0);
    glVertex3d(3, 2, -4);

    glTexCoord2f(1, 1);
    glVertex3d(3, -2, -4);

    glTexCoord2f(0, 1);
    glVertex3d(-3, -2, -4);
    glEnd();

}
void set_camera_jump_speed(Camera* camera, double speed)
{
    if(camera->speed.z == 0){
    camera->speed.z = speed;
    }else return;
}
void set_light_speed(Scene *scene, float speed){
    scene->light.speed = speed;
}
