#pragma once

#include "domain/entity/PlayerEntity.h"

#include "entities/EntityView.h"

class PlayerView : public EntityView {
    Injected<PlayerModel> playerModel;

public:

};

