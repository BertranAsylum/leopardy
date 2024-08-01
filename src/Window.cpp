#include "Window.h"
#include "direct/Canvas.h"
#include "utils/MonitorInfo.h"

#include <windowsx.h>
#include <cwctype>

// TODO: Refactor, add global event loop
static std::mutex guiMutex;

Window::~Window()
{}

Window::Window(int width, int height, int frameRate, const std::wstring &title) :
    m_title(title),
    m_frameDuration(1000ms / frameRate)
{
    setGeometry({.x = 0, .y = 0, .width = width, .height = height});
    if (!init()) {
        abort();
    }
}

void Window::show(int cmd) const
{
    SetWindowPos(m_handle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    ShowWindow(m_handle, cmd);
}

int Window::exec()
{
    m_running = true;
    while (m_running) {
        std::lock_guard lock(guiMutex);
        if (m_timer.elapsed() >= m_frameDuration) {
            onPaint(m_canvas.get());
            m_timer.reset();
        }
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}

std::mutex &Window::mutex()
{
    return guiMutex;
}

void Window::onPaint(Canvas *canvas)
{
    canvas->begin();
    canvas->clear({0.2f, 0.2f, 0.2f});
    Widget::onPaint(canvas);
    canvas->end();
}

bool Window::init()
{
    if (!registerClass()) {
        return false;
    }

    DWORD winStyles = WS_VISIBLE | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CAPTION | WS_MINIMIZEBOX;
    RECT boundingBox = {0, 0, width(), height()};
    AdjustWindowRect(&boundingBox, winStyles, false);

    int fullWidth = boundingBox.right - boundingBox.left;
    int fullHeight = boundingBox.bottom - boundingBox.top;

    MonitorInfo monitorInfo;
    int x = (monitorInfo.width() - width()) / 2;
    int y = (monitorInfo.height() - height()) / 2;

    m_handle = CreateWindow(
        m_title.c_str(),
        m_title.c_str(),
        winStyles,
        x,
        y,
        fullWidth,
        fullHeight,
        NULL,
        NULL,
        GetModuleHandle(nullptr),
        this);

    if (!m_handle) {
        return false;
    }

    m_canvas = std::make_shared<Canvas>();
    if (!m_canvas->init(this)) {
        m_canvas.reset();
        return false;
    }

    return true;
}

bool Window::registerClass()
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &Window::onEvent;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = m_title.c_str();

    return RegisterClassExW(&wcex);
}

HWND Window::handle() const
{
    return m_handle;
}

LRESULT CALLBACK Window::onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CREATE) {
        LONG_PTR window = reinterpret_cast<LONG_PTR>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetWindowLongPtr(handle, GWLP_USERDATA, window);
    }

    Window *window = handle ? reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA)) : nullptr;
    if (window) {
        switch (message) {
            case WM_MOUSEMOVE:
                window->onMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam & MK_LBUTTON);
                break;

            case WM_LBUTTONDOWN:
                SetCapture(window->m_handle);
                window->onMousePress(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                break;

            case WM_LBUTTONUP:
                ReleaseCapture();
                window->onMouseRelease(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                break;

            case WM_CHAR:
                if (std::iswprint(static_cast<wchar_t>(wParam))) {
                    window->onCharInput(static_cast<wchar_t>(wParam));
                }
                break;

            case WM_KEYDOWN:
            case WM_SYSKEYDOWN: {
                const WORD keyFlags = HIWORD(lParam);
                const BOOL isExtendedKey = (keyFlags & KF_EXTENDED) == KF_EXTENDED;
                WORD vkCode = LOWORD(wParam);
                WORD scanCode = LOBYTE(keyFlags);

                if (isExtendedKey) {
                    scanCode = MAKEWORD(scanCode, 0xE0);
                }

                switch (vkCode) {
                    case VK_SHIFT:
                    case VK_CONTROL:
                    case VK_MENU:
                        vkCode = LOWORD(MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX));
                        break;
                    default:
                        break;
                }

                window->onKeyboardInput(vkCode, scanCode);
                break;
            }

            case WM_DESTROY:
                window->m_running = false;
                PostQuitMessage(0);
                return 0;
        }
    }

    return DefWindowProc(handle, message, wParam, lParam);
}
