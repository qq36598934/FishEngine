#include "GameObject.hpp"
#include "Scene.hpp"
#include "Gizmos.hpp"

namespace FishEngine
{
    //GameObject::PGameObject GameObject::m_root = std::make_shared<GameObject>("Root");

    bool FishEngine::GameObject::activeInHierarchy() const
    {
        if (m_activeSelf && m_transform->parent() != nullptr) {
            return m_transform->parent()->gameObject()->activeInHierarchy();
        }
        return m_activeSelf;
    }

    FishEngine::GameObject::GameObject(const std::string& name) : m_tag("Untagged")
    {
        //m_transform->m_gameObject = this;
        m_transform = std::make_shared<Transform>();
        m_name = name;
    }

    GameObject::PGameObject GameObject::Find(const std::string& name)
    {
        return Scene::Find(name);
    }

    void FishEngine::GameObject::Update()
    {
        m_transform->Update();
        for (auto& s : m_scripts) {
            s->Update();
        }

        for (auto& c : m_components) {
            c->Update();
        }
    }

    void FishEngine::GameObject::OnDrawGizmos()
    {
        for (auto& c : m_components) {
            c->OnDrawGizmos();
            Gizmos::setColor(Color::green);
        }

        for (auto& s : m_scripts) {
            s->OnDrawGizmos();
            Gizmos::setColor(Color::green);
        }
    }

    void FishEngine::GameObject::Start()
    {
        for (auto& c : m_components) {
            c->Start();
        }
        for (auto& s : m_scripts) {
            s->Start();
        }
    }
}
