#include "AppCommon.h"

USING_NS_CC;

MenuItemSprite* createCustomMenuItem(const std::string& normalImage, const std::string& disabledImage)
{
	auto image = Sprite::create(normalImage);
	image->setColor(Color3B(100,100,100));
	auto item = MenuItemSprite::create(
		Sprite::create(normalImage),
		image,
		Sprite::create(disabledImage));

	return item;
}