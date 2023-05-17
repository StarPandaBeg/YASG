#include "InputSystem.h"

#include <algorithm>
#include <vector>

using namespace events;
using namespace events::input;

std::vector<int> movementKeys{ sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D };

int tryGetMovementKeyIndex(int keycode) {
	auto result = std::find(movementKeys.begin(), movementKeys.end(), keycode);
	if (result == movementKeys.end()) return -1;
	return std::distance(movementKeys.begin(), result);
}

util::InputSystem* util::InputSystem::instance()
{
	static InputSystem instance;
	return &instance;
}

void util::InputSystem::update(sf::Event e)
{
	Event* ev = nullptr;
	bool is_init = true;
	int index;

	switch (e.type) {
	case sf::Event::EventType::MouseButtonPressed:
		ev = new MouseEvent(e.mouseButton);
		break;
	case sf::Event::EventType::KeyPressed:
		ev = new KeyEvent(e.key);
		index = tryGetMovementKeyIndex(e.key.code);
		if (index == -1) break;

		emit(MovementEvent((MovementDirection)index));
		break;
	}

	if (ev == nullptr) return;
	emit(*ev);
	delete ev;
}
