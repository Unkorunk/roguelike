#include "Princess.h"

Princess::Princess() : GameObject('P') {
	this->is_win = false;
}

Princess::Princess(const Vec2d& origin) : GameObject('P', origin) {
	this->is_win = false;
}

void Princess::collideWith(Knight& knight) {
	is_win = true;
}

bool Princess::isWin() const {
	return is_win;
}
