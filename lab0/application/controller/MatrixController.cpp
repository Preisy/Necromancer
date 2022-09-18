#include "MatrixController.h"

#include <sstream>
#include <functional>
//#include <execution>

Response Controllers::MatrixController::add(const std::string & args) {
    std::istringstream ss(args);

    int i, j, value;
    ss >> i >> j >> value;

    if (!ss || !ss.eof()) {
        return {"", ResponseCode::BadRequest};
    }

    matrix.insert(i, j, value);

    return {"", Ok};
}

int sumOfDigits(int n) {
    int sum = 0;
    while (n != 0) {
        sum += n % 10;
        n = n / 10;
    }
    return sum;
}

Response Controllers::MatrixController::makeVector(const std::string & args) {
    if (args != "") {
        return {"", BadRequest};
    }

    const Models::Matrix<int> & matrix = this->matrix;

    vector = Models::Vector<int>(matrix.length());

    int i = 0;
//    std::for_each(std::execution::parallel_policy, ) // some intel lib
    // gcc openmp/intel tbb
    // boost::beast ??
    for (auto it = matrix.begin(); it != matrix.end(); ++it) {
        int sum = sumOfDigits((*(*it).begin()).value);
        for (auto jt = (*it).begin(); jt != (*it).end(); ++jt) {
            if (sumOfDigits((*jt).value) == sum) {
                vector[i] += (*jt).value;
            }
        }
        ++i;
    }

    return {"", Ok};
}

Response Controllers::MatrixController::print(const std::string & args) {
    std::ostringstream ss;

    for (auto it = matrix.begin(); it != matrix.end(); ++it) {
        for(auto jt = (*it).begin(); jt != (*it).end(); ++jt) {
            ss << "["<< (*jt).i << "][" << (*jt).j << "]: " << (*jt).value << "  ";
        }
        ss << std::endl;
    }

    ss << "[";
    for (int i = 0; i < vector.getLen(); ++i) {
        ss << vector[i];
        if (i != vector.getLen() - 1)
            ss << ", ";
    }
    ss << "]";

    return {ss.str(), Ok};
}


std::unordered_map<std::string, std::function<Response(const std::string &)>> Controllers::MatrixController::getRequests() {
    std::unordered_map<std::string, std::function<Response(const std::string &)>> res;
    res.emplace("add", [this](const std::string & args) {return add(args);});
    res.emplace("mk", [this](const std::string & args) {return makeVector(args);});
    res.emplace("print", [this](const std::string & args) {return print(args);});
    return res;
}

Controllers::MatrixController::MatrixController(Controllers::MatrixController && matrixController) noexcept {
    matrix = std::move(matrixController.matrix);
    vector = std::move(matrixController.vector);
    matrixController.matrix = Models::Matrix<int>();
}


