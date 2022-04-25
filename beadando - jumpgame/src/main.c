#include "app.h"

#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char* argv[])
{
    App app;
    int collected = 0;
    init_app(&app, 800, 600);
    while (app.is_running) {
        printf("collected: %d", collected);
        if(app.camera.position.x > 4.4 && app.camera.position.x < 5.4 && app.camera.position.y > 1.5 && app.camera.position.y < 2.5 && app.camera.position.z > 2.54 && app.camera.position.z < 2.6 && collected == 0){
            collected = 1;
        }
        SDL_ShowCursor(SDL_DISABLE);
        handle_app_events(&app, collected);
        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);

    return 0;
}
