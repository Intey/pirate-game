#ifndef ISLANDSMAP_H
#define ISLANDSMAP_H

#include <vector>

namespace cocos2d {
class Scene;
class Sprite;
}


/**
 * @brief Класс взаимодействия карты остравов. Описывает острова, и вызывает
 * callback'и при переходе на указанный остров.
 */
class IslandsMap
{
public:
    /**
     * @brief Инициализация карты. Определяет все острова.
     * @param scene базовая сцена, на которой будет работать карта остравов
     */
    IslandsMap(cocos2d::Scene *scene);

    /**
     * @brief отрисовка карты на экране
     */
    void renderOnScene(cocos2d::Scene * scene);

private:
    std::vector<cocos2d::Sprite*> m_coastSprites;
    std::vector<cocos2d::Scene*> m_scenes;

};

#endif // ISLANDSMAP_H
