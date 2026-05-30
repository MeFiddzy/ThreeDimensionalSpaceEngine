#include "app/App.h"

int main() {
    App *app = new App("Name", 1600, 800);

    if (app->getWindow() == nullptr) {
        return -1;
    }

    app->loop();

    delete app;
}
