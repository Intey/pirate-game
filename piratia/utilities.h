#ifndef UTILITIES_H
#define UTILITIES_H

#include <cocos/base/CCEventListenerTouch.h>

namespace cocos2d {
class Sprite;
class Scene;
}

/**
 * @brief создание обработчика события клика по спрайту.
 * Если выполнен клик - будет произведен переход на указанную сцену
 * @param sprite спрайт, по которому ожидается клик
 * @param scene сцена, которая будет запущена после клика
 * @return функция-обработчик клика
 */
cocos2d::EventListenerTouchOneByOne::ccTouchBeganCallback
createSceneTransitionOnSpriteClick(cocos2d::Scene *scene);

#endif // UTILITIES_H
