#include "processor.h"

//
// Execute current opcode.
// Set breakpoint flag on any exception.
// Set pc_affected when jump performed.
//
void Processor::process_instruction(bool &breakpoint, bool &pc_affected)
{
    // TODO
    //switch (opcode) {
    //case OP_LUI:
    //    Exec_LUI();
    //    break;
    //case OP_JAL:
    //    Exec_JAL();
    //    pc_affected = true;
    //    break;
    //case OP_EBREAK:
    //    Exec_EBREAK();
    //    breakpoint = true;
    //    break;
    //default:
    //    terminate_simulation("Wrong instruction");
    //    break;
    //}
}
