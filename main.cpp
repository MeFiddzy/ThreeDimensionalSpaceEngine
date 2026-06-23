#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "app/App.h"

int main() {
    auto *app = new App(1600, 800);

    if (app->getWindow() == nullptr) {
        return -1;
    }

    app->loop();

    delete app;
}
