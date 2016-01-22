#include "stdafx.h"
#include "InputManager.h"


InputManager* InputManager::mInstance = nullptr;
InputManager::InputManager()
{
    keysPressed = std::vector<sf::String>();
    keysPressedLastUpdate = std::vector<sf::String>();
}

InputManager* InputManager::instance()
{
    if (mInstance == nullptr)
    {
        mInstance = new InputManager();
    }

    return mInstance;
}

std::vector<sf::String> const& InputManager::getKeys()
{
    return keysPressed;
}

std::vector<sf::String> const& InputManager::getKeysLastUpdate()
{
    return keysPressedLastUpdate;
}

bool InputManager::Down(sf::String key)
{
    auto begin = keysPressed.begin();
    auto end = keysPressed.end();
    if (std::find(begin, end, key) != end)
        return true;
    return false;
}

bool InputManager::Up(sf::String key)
{
    auto begin = keysPressed.begin();
    auto end = keysPressed.end();
    if (std::find(begin, end, key) == end)
        return true;
    return false;
}

bool InputManager::Pressed(sf::String key)
{
    auto begin = keysPressed.begin();
    auto end = keysPressed.end();
    auto begin_LU = keysPressedLastUpdate.begin();
    auto end_LU = keysPressedLastUpdate.end();
    if (std::find(begin_LU, end_LU, key) == end_LU && std::find(begin, end, key) != end)
        return true;
    return false;
}

bool InputManager::Held(sf::String key)
{
    auto begin = keysPressed.begin();
    auto end = keysPressed.end();
    auto begin_LU = keysPressedLastUpdate.begin();
    auto end_LU = keysPressedLastUpdate.end();
    if (std::find(begin_LU, end_LU, key) != end_LU && std::find(begin, end, key) != end)
        return true;
    return false;
}

bool InputManager::Released(sf::String key)
{
    auto begin = keysPressed.begin();
    auto end = keysPressed.end();
    auto begin_LU = keysPressedLastUpdate.begin();
    auto end_LU = keysPressedLastUpdate.end();
    if (std::find(begin_LU, end_LU, key) != end_LU && std::find(begin, end, key) == end)
        return true;
    return false;
}

void InputManager::ClearKeys() {
	keysPressedLastUpdate = keysPressed;
	keysPressed.clear();
}

void InputManager::UpdatePressedKeys(sf::Event e)
{
	keysPressedLastUpdate = keysPressed;
	keysPressed.clear();
    if (e.type == sf::Event::KeyPressed)
    {
        if (e.key.code == sf::Keyboard::Left)
        {
            keysPressed.push_back("Left");
        }
        if (e.key.code == sf::Keyboard::Right)
        {
            keysPressed.push_back("Right");
        }
        if (e.key.code == sf::Keyboard::Up)
        {
            keysPressed.push_back("Up");
        }
        if (e.key.code == sf::Keyboard::Down)
        {
            keysPressed.push_back("Down");
        }
        if (e.key.code == sf::Keyboard::End)
        {
            keysPressed.push_back("End");
        }
        if (e.key.code == sf::Keyboard::Home)
        {
            keysPressed.push_back("Home");
        }
        if (e.key.code == sf::Keyboard::PageDown)
        {
            keysPressed.push_back("PageDown");
        }
        if (e.key.code == sf::Keyboard::Space)
        {
            keysPressed.push_back("Space");
        }
    }
}