#pragma once

#include "widgets/Widget.h"
#include "utils/Timer.h"

#include <Windows.h>
#include <string>
#include <memory>
#include <mutex>

class Window : public Widget {
    friend class Canvas;

public:
    ~Window() override;
    Window(int width, int height, int frameRate, const std::wstring &title);

    void show(int cmd = SW_SHOWNORMAL) const;
    int exec();

    static std::mutex &mutex();

protected:
    void onPaint(Canvas *canvas) override;

private:
    bool init();
    bool registerClass();
    HWND handle() const;
    static LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
    HWND m_handle = 0;
    bool m_running = false;
    std::wstring m_title;

    Timer m_timer;
    std::chrono::duration<double, std::milli> m_frameDuration;
    std::shared_ptr<Canvas> m_canvas;
};
