#include "math/matrix.hpp"

using namespace oingo;

static bool calculate_inverse(const auto& A) try
{
    std::cout << "Trying to inverse matrix:\n" << A
        << "Inverse:\n" << math::invert(A) << '\n';
    return true;
}
catch (const std::runtime_error& e)
{
    std::cout << "Failed to inverse - " << e.what() << "\n\n";
    return false;
}

static bool calculate_mult(const auto& A, const auto& v)
{
    std::cout << "Multiplying A*v:\n"
        << "A:\n" << A
        << "v:\n" << v << '\n'
        << "A*v:\n" << A * v << "\n\n";
}

int main()
{
    const auto MAT0 = math::identity<float_t, 3>();
    const auto MAT1 = math::matrix<float_t, 3, 3>{
        1,  0, -3,
        4, -8, 12,
        3, 15,  0
    };
    const auto MAT2 = math::matrix<float_t, 3, 3>{
        1, 0, 0,
        0, 5, 0,
        0, 0, 5
    };

    const auto VEC0 = math::vector<float_t, 3>{ 1,  0, 0 };
    const auto VEC1 = math::vector<float_t, 3>{ 7, -4, 2 };
    const auto VEC2 = math::vector<float_t, 3>{ 1,  0, 3 };

    for (const auto& A : { MAT0, MAT1, MAT2 })
    {
        calculate_inverse(A);
        for (const auto& v : { VEC0, VEC1, VEC2 })
            calculate_mult(A, v);
    }

    return EXIT_SUCCESS;
}