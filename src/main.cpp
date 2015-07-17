#include "VMState.hpp"
#include "register.hpp"
#include "opcodes.hpp"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <termios.h>
#undef CR0
#endif

int main(int argc, char** argv)
{
#ifdef _WIN32
    SetConsoleTitle("Cynosure");
#else
    struct termios termattr;
    tcgetattr(0, &termattr);
    termattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &termattr);
#endif

    VMState* state = new VMState("floppy_1_44.img", "debug.log", 1024 * 1024);
    state->CR0.protectedMode = false;
    state->CR0.emulation = true;

    state->eflags.direction = false;

    Opcode opcodes[256];
    opcodesGenerate(opcodes);

    state->running = true;
    while (state->running)
    {
        Opcode opcode = opcodes[CURR_INS];

        LOG_STREAM << "0x" << std::setw(2) << std::hex << (uint32_t)opcode.opcode << ": "
                   << opcode.name;

        opcode.func(state, opcode);
        state->eip += opcode.GetFinalOffset(state);

        LOG_STREAM << std::endl;
    }

    delete state;
    return 0;
}