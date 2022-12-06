#pragma once

#include "PlayerModel.h"

#include "entities/EntityView.h"

class PlayerView : public EntityView {
    Injected<PlayerModel> playerModel;

public:

};

