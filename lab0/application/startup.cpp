#include "Builder.h"
#include "MatrixController.h"
#include "Dialog.h"

#include "memory"



int main() {
    Builder builder;
    auto mc = std::make_unique<Controllers::MatrixController>(Controllers::MatrixController());
    builder.addController(std::move(mc));

//    builder.useSessionLogging(std::ofstream("../../log.txt"));

    builder.build();

    Dialog dialog = Dialog(std::cin, std::cout);
    dialog.connectToApi(&builder);

    return dialog.run();
}