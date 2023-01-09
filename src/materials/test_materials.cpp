#include "test_materials.hpp"

namespace oingo::materials
{

    const material matt_white {
        .ke = { 0.9, 0.9, 0.9 },
        .ks = { 1, 1, 1 }
    };
    
    const material matt_red {
        .ke = { 0.9, 0.1, 0.1 },
        .ks = { 1, 1, 1 }
    };

}