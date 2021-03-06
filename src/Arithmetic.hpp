#pragma once

#include <stdint.h>
#include "Register.hpp"
#include "VMState.hpp"

namespace arithmetic
{
    uint32_t Add(VMState* state, uint32_t a, uint32_t b);
    uint32_t Sub(VMState* state, uint32_t a, uint32_t b);

    uint32_t And(VMState* state, uint32_t a, uint32_t b);
    uint32_t Or(VMState* state, uint32_t a, uint32_t b);
    uint32_t Xor(VMState* state, uint32_t a, uint32_t b);

    uint32_t ShiftLeft(VMState* state, uint32_t a, uint32_t b);
};