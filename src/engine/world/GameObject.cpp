#include "GameObject.h"

GameObject::GameObject(const char* name)
    : g_name(name)
    {
    data.push_back({-1.0f, -1.0f, 0.0f});
    data.push_back({ -1.0f,  1.0f, 0.0f});
    data.push_back({ 1.0f, 1.0f, 0.0f});

    data.push_back({ -1.0f, -1.0f, 0.0f});
    data.push_back({ 1.0f, 1.0f, 0.0f});
    data.push_back({ 1.0f, -1.0f, 0.0f});
    buffer = new Buffer3d((float*)&data[0], (int)data.size());
}