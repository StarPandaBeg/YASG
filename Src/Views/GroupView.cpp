#include "GroupView.h"

#include "Renderers/GroupRenderer.h"
#include <iostream>

int views::GroupView::addView(View* v)
{
    auto layer = v->getOrderInLayer();
    auto id = rand() % 100000;
    auto viewObj = ViewObj{ id, v };
    _viewMap.emplace(layer, viewObj);
    return id;
}

views::View* views::GroupView::removeView(int id)
{
    for (auto it = _viewMap.begin(); it != _viewMap.end(); it++) {
        if (it->second.id == id) {
            _viewMap.erase(it);
            return it->second.v;
        }
    }
    return nullptr;
}

views::renderers::ICustomRenderer* views::GroupView::getCustomRenderer()
{
    return _renderer;
}

views::GroupView::GroupView(sf::Vector2f pos) : View(pos)
{
    _renderer = new renderers::GroupRenderer(&_viewMap);
}

views::GroupView::~GroupView()
{
    delete _renderer;
    _renderer = nullptr;
    for (auto view : _viewMap) {
        if (view.second.v == nullptr) continue;
        delete view.second.v;
    }
}

void views::GroupView::setEnabled(bool enabled)
{
    _enabled = enabled;
    std::multimap<int, ViewObj> map(_viewMap);
    for (auto it = map.begin(); it != map.end(); it++) {
        (*it).second.v->setEnabled(enabled);
    }
}
