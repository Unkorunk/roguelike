#include "Princess.h"

Princess::Princess() : GameObject('P') {
}

Princess::Princess(const Vec2d& origin) : GameObject('P', origin) {
}
