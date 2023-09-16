#include "Component.h"

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() {}

void Component::Update(float dt) {

}
