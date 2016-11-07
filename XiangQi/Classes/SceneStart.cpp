#include "SceneStart.h"
#include "SceneMenu.h"
#include "AppMacros.h"
Scene* SceneStart::scene()
{
    Scene* scene = Scene::create();

    SceneStart* layer = SceneStart::create();

    scene->addChild(layer);

    return scene;
}

bool SceneStart::init()
{
    Layer::init();

    Size winSize = Director::getInstance()->getWinSize();

	//创建商标-----------------------------------------------------
	Sprite* shangbiao = Sprite::create("shangbiao.png");
	shangbiao->setPosition(Point(winSize.width / 2, winSize.height / 2));
	shangbiao->setScaleX(winSize.width / shangbiao->getContentSize().width);
	shangbiao->setScaleY(winSize.height / shangbiao->getContentSize().height);
	addChild(shangbiao);

	runAction(Sequence::createWithTwoActions(DelayTime::create(3.f),
		CallFuncN::create(CC_CALLBACK_1(SceneStart::CallMenu,this))));

    return true;
}

void SceneStart::CallMenu(Node* sender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,SceneMenu::scene()));
}
