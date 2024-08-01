#include "Window.h"
#include "Game.h"

#include <locale>

int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR lpCmdLine,
                      int nCmdShow)
{
    std::locale::global(std::locale(".1251"));

    Window window(640, 960, 60, L"Jeopardy");
    Game game(&window);

    window.show(nCmdShow);
    return window.exec();
}
