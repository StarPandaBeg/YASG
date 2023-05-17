#pragma once

namespace sf {
	class RenderWindow;
}

namespace views {
	namespace renderers {
		class ICustomRenderer {
		public:
			virtual void render(sf::RenderWindow* win) = 0;
		};
	}
}