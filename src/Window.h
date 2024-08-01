#pragma once

#include "Application.h"
#include "utils/Timer.h"
#include "widgets/Widget.h"

#include <Windows.h>
#include <string>
#include <memory>
#include <mutex>

class Widget;

class Window : public Application, public Widget {
    friend class Canvas;

public:
    ~Window() override;
    Window(int width, int height, int frameRate, const std::wstring &title);

    void show(int cmd = SW_SHOWNORMAL) const;

protected:
    void loop() override;
    void onPaint(Canvas *canvas) override;

private:
    bool init();
    bool registerClass();
    HWND handle() const;
    static LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
    HWND m_handle = 0;
    std::wstring m_title;

    Timer m_timer;
    std::chrono::duration<double, std::milli> m_frameDuration;
    std::shared_ptr<Canvas> m_canvas;
};
