#include "app/App.h"

int main() {
    App *app = new App("Name", 800, 600);

    if (app->getWindow() == nullptr) {
        return -1;
    }

    app->loop();

    delete app;
}
