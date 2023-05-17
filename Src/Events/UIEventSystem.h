#pragma once

#include "IWindowEventTickable.h"
#include "../Views/UI/IInteractable.h"
#include <map>

namespace util {
	class UIEventSystem : IWindowEventTickable
	{
	private:
		struct Data {
			views::ui::IInteractable* interactable;
			bool mouseDown[5] = {false, false, false, false, false};
			bool inArea = false;
		};

		std::map<int, Data*> _map;
		bool _skipTick = false;
		UIEventSystem();
	
		void process(Data* data, sf::Event e);
	public:
		~UIEventSystem();
		static UIEventSystem* instance();
		void tick(sf::Event e) override;
		int add(views::ui::IInteractable* interactable);
		void remove(int id);
	};
}