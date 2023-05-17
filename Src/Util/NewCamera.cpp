#include "NewCamera.h"
#include "Utility.h"

sf::Vector2f util::NewCamera::getCameraPosition()
{
	if (_target == nullptr)
		return _center;
	auto targetBounds = _target->getBounds()->getGlobalBounds();
	auto targetPos = sf::Vector2f(targetBounds.left + targetBounds.width / 2, targetBounds.top + targetBounds.height / 2);
	return targetPos;
}

util::NewCamera::NewCamera(sf::View view)
{
	_lastView = view;
}

void util::NewCamera::setTarget(views::View* target)
{
	_target = target;
}

void util::NewCamera::centerAt(sf::Vector2f pos)
{
	_center = pos;
}

void util::NewCamera::center()
{
	auto viewSize = _lastView.getSize();
	auto mid = sf::Vector2f(viewSize.x / 2, viewSize.y / 2);
	centerAt(mid);
}

void util::NewCamera::deployTo(sf::RenderTarget* target)
{
	_lastView = target->getView();
	auto pos = getCameraPosition();
	_lastView.setCenter(pos);
	target->setView(_lastView);
}
