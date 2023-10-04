#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <sstream>
#include <string>

#include "systemc"
#include "tlm.h"

class Log {
public:
    static std::ostream &out(void);
    static std::ostream &err(void);

    static void set_verbose(const std::string &filename);

    static bool is_verbose();

private:
    static std::string filename;
    static std::ofstream m_stream;
    static std::ofstream m_sink;
};

#endif
