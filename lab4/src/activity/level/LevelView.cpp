#include "LevelView.h"
#include "activity/field/FieldView.h"
#include "activity/field/FieldController.h"

void LevelView::update(long long int time) {
    field->update(time);
}

void LevelView::draw() {
    field->draw();
}

