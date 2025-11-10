//
// Created by Coline Constantinian on 09/11/2025.
//

#include <minigl/Input.h>

void mngl::Input::UpdateKey(EKeyCode _key, EKeyStatus _status) {
    m_statusKey[_key] =_status;
}

void mngl::Input::UpdateMouse(EKeyMouseCode _key, EKeyStatus _status) {
    m_statusMouse[_key] =_status;
}

void mngl::Input::Update(GLFWwindow* _win) {
    for (auto kv: m_statusKey) {
        if (kv.second == JUST_RELEASED) {
            m_statusKey[kv.first] = RELEASED;
        }
    }
    for (auto kv: m_statusKey) {
        if (kv.second == JUST_PRESSED) {
            m_statusKey[kv.first] = PRESSED;
        }
    }
    for (auto kv: m_statusMouse) {
        if (kv.second == JUST_RELEASED) {
            m_statusMouse[kv.first] = RELEASED;
        }
    }
    for (auto kv: m_statusMouse) {
        if (kv.second == JUST_PRESSED) {
            m_statusMouse[kv.first] = PRESSED;
        }
    }
    double posx = m_mousePosX;
    double posy = m_mousePosY;
    glfwGetCursorPos(_win, &m_mousePosX, &m_mousePosY);
    if (m_init) {
        m_deltaMousePosX = m_mousePosX - posx;
        m_deltaMousePosY = m_mousePosY - posy;
    }
    m_init = true;
}

bool mngl::Input::IsKeyPressed(EKeyCode _key) {
    if (m_statusKey.contains(_key)) {
        return m_statusKey[_key] > JUST_RELEASED ;
    }
    return false;
}

bool mngl::Input::IsKeyJustPressed(EKeyCode _key) {
    if (m_statusKey.contains(_key)) {
        return m_statusKey[_key] == JUST_PRESSED ;
    }
    return false;
}

bool mngl::Input::IsKeyJustReleased(EKeyCode _key) {
    if (m_statusKey.contains(_key)) {
        return m_statusKey[_key] == JUST_RELEASED ;
    }
    return false;
}

mngl::Input::EKeyStatus mngl::Input::GetKeyStatus(EKeyCode _key) {
    if (m_statusKey.contains(_key)) {
        return m_statusKey[_key];
    }
    return RELEASED;
}


bool mngl::Input::IsMouseButtonPressed(EKeyMouseCode _key) {
    if (m_statusMouse.contains(_key)) {
        return m_statusMouse[_key] > JUST_RELEASED ;
    }
    return false;
}

bool mngl::Input::IsMouseButtonJustPressed(EKeyMouseCode _key) {
    if (m_statusMouse.contains(_key)) {
        return m_statusMouse[_key] == JUST_PRESSED ;
    }
    return false;
}

bool mngl::Input::IsMouseButtonJustReleased(EKeyMouseCode _key) {
    if (m_statusMouse.contains(_key)) {
        return m_statusMouse[_key] == JUST_RELEASED ;
    }
    return false;
}

mngl::Input::EKeyStatus mngl::Input::GetMouseButtonStatus(EKeyMouseCode _key) {
    if (m_statusMouse.contains(_key)) {
        return m_statusMouse[_key];
    }
    return RELEASED;
}

glm::dvec2 mngl::Input::GetMousePosition() const {
    return {m_mousePosX, m_mousePosY};
}

glm::dvec2 mngl::Input::GetDeltaMousePosition() const {
    return {m_deltaMousePosX, m_deltaMousePosY};
}

