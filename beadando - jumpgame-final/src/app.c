#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "o4frg0 JumpGame",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 3000
    );
}
void handle_app_events(App* app)
{
    SDL_Event event;
    if(app->camera.position.x > 4.4 && app->camera.position.x < 5.4 && app->camera.position.y > 1.5 && app->camera.position.y < 2.5 && app->camera.position.z > 2.54 && app->camera.position.z < 2.6){
        app->collected = 1;
    }
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    float curspeed;
    int y;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                    break;
                case SDL_SCANCODE_F1:
                    if(app->scene.helpstate == 0) {
                        app->scene.helpstate = 1;
                    }
                    else {
                        app->scene.helpstate = 0;
                    }
                    break;
                case SDL_SCANCODE_R:
                    app->collected = 0;
                    reset_camera(&(app->camera));
                    break;
                case SDL_SCANCODE_W:
                    set_camera_speed(&(app->camera), 2.000000000);
                    break;
                case SDL_SCANCODE_LSHIFT:
                if(app->collected == 1) {
                    if (app->camera.speed.y < 3.000000000) {
                        set_camera_speed(&(app->camera), app->camera.speed.y * 1.8);
                    }
                }
                    break;
                case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1);
                break;
                case SDL_SCANCODE_A:
                    set_camera_side_speed(&(app->camera), 1);
                    break;
                case SDL_SCANCODE_D:
                    set_camera_side_speed(&(app->camera), -1);
                    break;
                case SDL_SCANCODE_F7:
                    set_light_speed(&(app->scene), -0.1);
                    break;
                case SDL_SCANCODE_F8:
                    set_light_speed(&(app->scene), 0.1);
                    break;
                case SDL_SCANCODE_J:
                    rotate_camera(&(app->camera), 1, 0);
                    break;
                case SDL_SCANCODE_K:
                    rotate_camera(&(app->camera), -1, 0);
                    break;
                case SDL_SCANCODE_SPACE:
                    if(app->camera.speed.z == 0) {
                        set_camera_jump_speed(&(app->camera), 2.05);
                    }
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_LSHIFT:
                        curspeed = app->camera.speed.y;
                        if(app->camera.speed.y != 2.0) {
                            set_camera_speed(&(app->camera), 2);
                        }
                    break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0.0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
			case SDL_SCANCODE_J:
			case SDL_SCANCODE_K:
				rotate_camera(&(app->camera), 0, 0);
				break;
			case SDL_SCANCODE_Q:
			case SDL_SCANCODE_E:
				set_camera_height_speed(&(app->camera), 0);
				break;
                case SDL_SCANCODE_F7:
                case SDL_SCANCODE_F8:
                    set_light_speed(&(app->scene), 0);
                    break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (!is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
    if(app->camera.position.z < 1.2){
        app->collected = 0;
        app->camera.position.x = 12;
        app->camera.position.y = 2;
        app->camera.position.z = 3;
        app->camera.speed.z = 0;
        app->camera.speed.x = 0;
        app->camera.speed.y = 0;
    }
}
void update_app(App* app)
{
    double current_time;
    double elapsed_time;
    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;
    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene),&(app->camera), elapsed_time);

   // SDL_WarpMouseInWindow(app->window, 300,300);
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene), &(app->camera));
    glPopMatrix();

    if (app->camera.is_preview_visible) {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}
