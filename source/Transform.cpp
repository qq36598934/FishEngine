#include "Transform.hpp"
#include "GameObject.hpp"
#include "Debug.hpp"
#include <imgui/imgui.h>

FishEngine::Transform::Transform() : m_localPosition(0, 0, 0), m_localScale(1, 1, 1), m_localRotation(1, 0, 0, 0)
{

}

FishEngine::Transform::~Transform()
{
    Debug::Log("~Transform");
    SetParent(nullptr);
    for (auto child : m_children) {
        //Scene::des
    }
}

void FishEngine::Transform::OnEditorGUI()
{
    if (ImGui::InputFloat3("Position", glm::value_ptr(m_localPosition))) {
        //m_isDirty = true;
    }
    if (ImGui::InputFloat3("Rotation", glm::value_ptr(m_localEulerAngles))) {
        m_localRotation = glm::quat(glm::radians((m_localEulerAngles)));
        //m_isDirty = true;
    }
    if (ImGui::InputFloat3("Scale", glm::value_ptr(m_localScale))) {
        //m_isDirty = true;
    }
}

void FishEngine::Transform::Update() const
{
    //        if (!m_isDirty)
    //            return;
    m_localEulerAngles = glm::degrees(glm::eulerAngles(m_localRotation));
    m_localToWorldMatrix = glm::scale(glm::translate(glm::mat4(1.0f), m_localPosition) * glm::mat4_cast(m_localRotation), m_localScale);
    if (m_parent != nullptr)
        m_localToWorldMatrix = m_parent->localToWorldMatrix() * m_localToWorldMatrix;
    m_worldToLocalMatrix = glm::inverse(m_localToWorldMatrix);
}

void FishEngine::Transform::LookAt(const Vector3& target, const Vector3& worldUp /*= Vector3(0, 1, 0)*/)
{
    m_worldToLocalMatrix = glm::lookAt(m_localPosition, target, worldUp);
    m_localToWorldMatrix = glm::inverse(m_worldToLocalMatrix);
    m_localRotation = glm::quat_cast(m_localToWorldMatrix);
    //m_isDirty = true;
}

FishEngine::Vector3 FishEngine::Transform::TransformDirection(const Vector3& direction) const
{
    return m_localToWorldMatrix * Vector4(direction, 0);
}

void FishEngine::Transform::Translate(const Vector3& translation, Space relativeTo /*= Space::Self*/)
{
    if (relativeTo == Space::World)
        m_localPosition += translation;
    else
        m_localPosition += TransformDirection(translation);
    //m_isDirty = true;
}

void FishEngine::Transform::Rotate(Vector3 eulerAngles, Space relativeTo /*= Space::Self*/)
{
    Update();
    Quaternion lhs(glm::radians(eulerAngles));
    if (Space::Self == relativeTo) {
        auto r = this->rotation();
        m_localRotation = glm::inverse(r) * lhs * r * m_localRotation;
    }
    else {
        m_localRotation = lhs * m_localRotation;
    }
    //        m_isDirty = true;
}

void FishEngine::Transform::RotateAround(const Vector3& point, const Vector3& axis, float angle)
{
    auto rotation = angleAxis(angle, axis);
    m_localPosition = point + rotation * (m_localPosition - point);
    LookAt(point);
}

void FishEngine::Transform::SetParent(Transform* parent)
{
    if (parent == m_parent) {
        return;
    }
    // remove from old parent
    if (m_parent != nullptr) {
        m_parent->m_children.remove(this);
    }

    m_parent = parent;
    if (parent == nullptr) {
        return;
    }
    m_parent->m_children.push_back(this);
    //m_isDirty = true;
}

NAMESPACE_FISHENGINE_BEGIN

Transform* Transform::GetChild(const int index) {
    if (index < -0 || index >= m_children.size()) {
        Debug::LogWarning("%s %d %s index out of range", __FILE__, __LINE__, __FUNCTION__);
        return nullptr;
    }
    
    auto p = m_children.begin();
    for (int i = 0; i < index; ++i) {
        p++;
    }
    return *p;
}

NAMESPACE_FISHENGINE_END
