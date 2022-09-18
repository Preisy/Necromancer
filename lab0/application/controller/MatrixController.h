#pragma once
#include <string>

#include "IController.h"
#include "Matrix.h"
#include "Vector.h"
#include "Response.h"

namespace Controllers {
    class MatrixController : public IController {
        Models::Matrix<int> matrix;
        Models::Vector<int> vector;

        Response add(const std::string & args);
        Response makeVector(const std::string & args);
        Response print(const std::string & args);

    public:
        MatrixController() = default;


        std::unordered_map<std::string, std::function<Response(const std::string &)>> getRequests() override;

        ~MatrixController() override = default;

        MatrixController(MatrixController && matrixController) noexcept;

    };
}