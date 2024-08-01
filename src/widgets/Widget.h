#pragma once

#include <functional>
#include <string>
#include <memory>
#include <vector>

class Window;
class Canvas;

class Widget {
public:
    using MouseMoveCallback = std::function<void(int x, int y, bool pressed)>;
    using MouseEnterCallback = std::function<void(int x, int y, bool pressed)>;
    using MouseLeaveCallback = std::function<void(int x, int y, bool pressed)>;
    using MousePressCallback = std::function<void(int x, int y)>;
    using MouseReleaseCallback = std::function<void(int x, int y)>;
    using KeyboardInputCallback = std::function<void(uint16_t keyCode, uint16_t scanCode)>;
    using CharInputCallback = std::function<void(wchar_t character)>;

    struct Geometry {
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
    };

    virtual ~Widget() = default;
    explicit Widget() = default;

    void setId(const std::wstring &id);
    void setParent(Widget *widget);
    void addChild(Widget *widget);
    void removeChild(const std::wstring &id);
    void removeChild(Widget *widget);
    void clearChildren();

    std::wstring id() const;
    Widget *parent() const;
    Widget *child(const std::wstring &id) const;
    std::vector<Widget*> children() const;
    int childrenCount() const;

    Widget *nextSibling() const;
    Widget *previousSibling() const;

    void setMouseTransparent(bool transparent);
    bool mouseTransparent() const;

    void setEnabled(bool enabled);
    void enable();
    void disable();
    bool enabled() const;
    bool disabled() const;

    void setVisible(bool visible);
    void show();
    void hide();
    bool visible() const;

    void setPos(int x, int y);
    void setSize(int width, int height);
    void setGeometry(const Geometry &geometry);

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    Geometry geometry() const;

    void onMouseMove(const MouseMoveCallback &callback);
    void onMouseEnter(const MouseEnterCallback &callback);
    void onMouseLeave(const MouseLeaveCallback &callback);
    void onMousePress(const MousePressCallback &callback);
    void onMouseRelease(const MouseReleaseCallback &callback);
    void onKeyboardInput(const KeyboardInputCallback &callback);
    void onCharInput(const CharInputCallback &callback);

    bool contains(int x, int y) const;

protected:
    virtual void onPaint(Canvas *canvas);
    virtual void onMouseMove(int x, int y, bool pressed);
    virtual void onMouseEnter(int x, int y, bool pressed);
    virtual void onMouseLeave(int x, int y, bool pressed);
    virtual void onMousePress(int x, int y);
    virtual void onMouseRelease(int x, int y);
    virtual void onKeyboardInput(uint16_t keyCode, uint16_t scanCode);
    virtual void onCharInput(wchar_t character);

    bool focused() const;
    bool hovered() const;
    bool pressed() const;

    static void setFocus(Widget *widget);

private:
    std::wstring m_id;
    Widget *m_parent = nullptr;
    std::vector<std::shared_ptr<Widget>> m_children;

    Geometry m_geometry;
    MouseMoveCallback m_mouseMoveCallback;
    MouseEnterCallback m_mouseEnterCallback;
    MouseLeaveCallback m_mouseLeaveCallback;
    MousePressCallback m_mousePressCallback;
    MouseReleaseCallback m_mouseReleaseCallback;
    KeyboardInputCallback m_keyboardInputCallback;
    CharInputCallback m_charInputCallback;

    bool m_mouseTransparent = false;
    bool m_visible = true;
    bool m_enabled = true;
    bool m_hovered = false;
    bool m_pressed = false;
};
