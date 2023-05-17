#pragma once

#include "View.h"
#include "Renderers/ICustomRenderer.h"

namespace views {
	class GroupView : public View
	{
	private:
		std::multimap<int, ViewObj> _viewMap;
		int _counter = 0;
	protected:
		renderers::ICustomRenderer* _renderer;

		int addView(View* v);
		View* removeView(int id);

		virtual renderers::ICustomRenderer* getCustomRenderer() override;
		GroupView(sf::Vector2f pos);
	public:
		virtual ~GroupView();
		virtual void setEnabled(bool enabled) override;
	};
}

