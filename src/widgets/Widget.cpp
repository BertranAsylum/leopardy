#include "Widget.h"

#include <assert.h>
#include <direct/Canvas.h>

static Widget *focusedWidget = nullptr;

void Widget::setId(const std::wstring &id)
{
    m_id = id;
}

void Widget::setParent(Widget *widget)
{
    m_parent = widget;
    if (widget) {
        widget->addChild(this);
    }
}

void Widget::addChild(Widget *widget)
{
    if (widget) {
        assert(!widget->id().empty());
        widget->m_parent = this;
        m_children.push_back(std::shared_ptr<Widget>(widget));
    }
}

void Widget::removeChild(const std::wstring &id)
{
    const auto cit = std::find_if(m_children.cbegin(), m_children.cend(),
                                  [id](const auto &widget) { return widget->id() == id; });
    m_children.erase(cit);
}

void Widget::removeChild(Widget *widget)
{
    if (widget) {
        removeChild(widget->id());
    }
}

void Widget::clearChildren()
{
    m_children.clear();
}

std::wstring Widget::id() const
{
    return m_id;
}

Widget *Widget::parent() const
{
    return m_parent;
}

Widget *Widget::child(const std::wstring &id) const
{
    const auto cit = std::find_if(m_children.cbegin(), m_children.cend(),
                                  [id](const auto &widget) { return widget->id() == id; });
    if (cit != m_children.end()) {
        return cit->get();
    }
    return nullptr;
}

std::vector<Widget*> Widget::children() const
{
    std::vector<Widget*> cs;
    for (const auto &c : m_children) {
        cs.push_back(c.get());
    }
    return cs;
}

int Widget::childrenCount() const
{
    return m_children.size();
}

Widget *Widget::nextSibling() const
{
    if (m_parent) {
        for (auto it = m_parent->m_children.begin(), ite = m_parent->m_children.end(); it != ite; ++it) {
            if (it != (ite - 1) && it->get() == this) {
                return (it + 1)->get();
            }
        }
    }
    return nullptr;
}

Widget *Widget::previousSibling() const
{
    if (m_parent) {
        for (auto it = m_parent->m_children.begin(), ite = m_parent->m_children.end(); it != ite; ++it) {
            if (it != m_parent->m_children.begin() && it->get() == this) {
                return (it - 1)->get();
            }
        }
    }
    return nullptr;
}

void Widget::setMouseTransparent(bool transparent)
{
    m_mouseTransparent = transparent;
}

bool Widget::mouseTransparent() const
{
    return m_mouseTransparent;
}

void Widget::setEnabled(bool enabled)
{
    if (!(m_enabled = enabled)) {
        m_hovered = false;
        m_pressed = false;
    }
    for (auto &c : m_children) {
        c->setEnabled(enabled);
    }
}

void Widget::enable()
{
    setEnabled(true);
}

void Widget::disable()
{
    setEnabled(false);
}

bool Widget::enabled() const
{
    return m_enabled;
}

bool Widget::disabled() const
{
    return !m_enabled;
}

void Widget::setVisible(bool visible)
{
    if (!(m_visible = visible)) {
        m_hovered = false;
        m_pressed = false;
    }
}

void Widget::show()
{
    setVisible(true);
}

void Widget::hide()
{
    setVisible(false);
}

bool Widget::visible() const
{
    return m_visible;
}

void Widget::setPos(int x, int y)
{
    m_geometry.x = x;
    m_geometry.y = y;
}

void Widget::setSize(int width, int height)
{
    m_geometry.width = width;
    m_geometry.height = height;
}

void Widget::setGeometry(const Geometry &geometry)
{
    m_geometry = geometry;
}

int Widget::x() const
{
    return m_geometry.x;
}

int Widget::y() const
{
    return m_geometry.y;
}

int Widget::width() const
{
    return m_geometry.width;
}

int Widget::height() const
{
    return m_geometry.height;
}

Widget::Geometry Widget::geometry() const
{
    return m_geometry;
}

void Widget::onMouseMove(const MouseMoveCallback &callback)
{
    m_mouseMoveCallback = callback;
}

void Widget::onMouseEnter(const MouseEnterCallback &callback)
{
    m_mouseEnterCallback = callback;
}

void Widget::onMouseLeave(const MouseLeaveCallback &callback)
{
    m_mouseLeaveCallback = callback;
}

void Widget::onMousePress(const MousePressCallback &callback)
{
    m_mousePressCallback = callback;
}

void Widget::onMouseRelease(const MouseReleaseCallback &callback)
{
    m_mouseReleaseCallback = callback;
}

void Widget::onKeyboardInput(const KeyboardInputCallback &callback)
{
    m_keyboardInputCallback = callback;
}

void Widget::onCharInput(const CharInputCallback &callback)
{
    m_charInputCallback = callback;
}

bool Widget::contains(int x, int y) const
{
    return (x >= m_geometry.x && x <= (m_geometry.x + m_geometry.width)) &&
        (y >= m_geometry.y && y <= (m_geometry.y + m_geometry.height));
}

void Widget::onPaint(Canvas *canvas)
{
    for (const auto &c : m_children) {
        if (c->visible()) {
            c->onPaint(canvas);
        }
    }
}

void Widget::onMouseMove(int x, int y, bool pressed)
{
    for (const auto &c : m_children) {
        if (!c->mouseTransparent() && c->enabled() && c->visible()) {
            c->onMouseMove(x, y, pressed);
            if (c->contains(x, y)) {
                if (!c->hovered()) {
                    c->onMouseEnter(x, y, pressed);
                }
            }
            else {
                if (c->hovered()) {
                    c->onMouseLeave(x, y, pressed);
                }
            }
        }
    }

    if (m_mouseMoveCallback) {
        m_mouseMoveCallback(x, y, pressed);
    }
}

void Widget::onMouseEnter(int x, int y, bool pressed)
{
    if (m_enabled && m_visible) {
        m_hovered = true;
        if (m_mouseEnterCallback) {
            m_mouseEnterCallback(x, y, pressed);
        }
    }
}

void Widget::onMouseLeave(int x, int y, bool pressed)
{
    if (m_enabled && m_visible) {
        m_hovered = false;
        m_pressed = false;
        if (m_mouseLeaveCallback) {
            m_mouseLeaveCallback(x, y, pressed);
        }
    }
}

void Widget::onMousePress(int x, int y)
{
    for (const auto &c : m_children) {
        if (!c->mouseTransparent()
            && c->enabled()
            && c->visible()
            && c->contains(x, y)) {
            c->onMousePress(x, y);
            return;
        }
    }

    m_pressed = true;
    if (m_mousePressCallback) {
        m_mousePressCallback(x, y);
    }
}

void Widget::onMouseRelease(int x, int y)
{
    for (const auto &c : m_children) {
        if (!c->mouseTransparent()
            && c->enabled()
            && c->visible()
            && c->contains(x, y)) {
            c->onMouseRelease(x, y);
            return;
        }
    }

    setFocus(this);
    m_pressed = false;
    if (m_mouseReleaseCallback) {
        m_mouseReleaseCallback(x, y);
    }
}

void Widget::onKeyboardInput(uint16_t keyCode, uint16_t scanCode)
{
    Widget *focusedChild = nullptr;
    for (const auto &c : m_children) {
        if (c->focused()) {
            focusedChild = c.get();
        }
        if (c->enabled()
            && c->visible()) {
            c->onKeyboardInput(keyCode, scanCode);
        }
    }

    if (focusedChild && (keyCode == VK_TAB || keyCode == VK_RETURN)) {
        setFocus(focusedChild->nextSibling());
    }

    if (m_keyboardInputCallback && focused()) {
        m_keyboardInputCallback(keyCode, scanCode);
    }
}

void Widget::onCharInput(wchar_t character)
{
    for (const auto &c : m_children) {
        if (c->enabled()
            && c->visible()) {
            c->onCharInput(character);
        }
    }

    if (m_charInputCallback && focused()) {
        m_charInputCallback(character);
    }
}

bool Widget::focused() const
{
    return (focusedWidget == this);
}

bool Widget::hovered() const
{
    return m_hovered;
}

bool Widget::pressed() const
{
    return m_pressed;
}

void Widget::setFocus(Widget *widget)
{
    focusedWidget = widget;
}
