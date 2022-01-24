#pragma once

#include <UI/text.hpp>
#include <base/actors/actor.hpp>

class Dialog {
public:
	Dialog(Actor* actor);
	draw(ShaderHolder*);
}