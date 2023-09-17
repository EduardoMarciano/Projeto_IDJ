#include "Component.h"
#include "Rect.h"

Component::Component(GameObject &associated) : associated(associated) {}

Component::~Component() {}