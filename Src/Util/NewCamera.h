#pragma once

#include "../Views/View.h"

namespace util {
	class NewCamera
	{
	private:
		views::View* _target = nullptr;
		sf::Vector2f _center;
		sf::View _lastView;

		sf::Vector2f getCameraPosition();
	public:
		NewCamera(sf::View view);
		void setTarget(views::View* target);
		void centerAt(sf::Vector2f pos);
		void center();

		void deployTo(sf::RenderTarget* target);
	};
}

