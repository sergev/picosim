/*!
 \file Log.h
 \brief Class to manage Log
 \author Màrius Montón
 \date Aug 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <sstream>
#include <string>

#include "systemc"
#include "tlm.h"

/**
 * @brief Log management class
 *
 * Don't allocate: use as a global object.
 */
class Log {
public:
    /**
     * @brief method to log some string
     * @return streaming
     *
     * This function can be used in the following way:
     * \code
     * Log::err() << "some warning text"
     * \endcode
     */
    static std::ostream &out(void);
    static std::ostream &err(void);

    /**
     * @brief Set verbose log output to the given filename.
     * @param filename File name for log output, or empty to disable.
     */
    static void set_verbose(const std::string &filename);

    /**
     * @brief Returns log level
     * @return Current log level
     */
    static bool is_verbose();

private:
    static std::string filename;
    static std::ofstream m_stream;
    static std::ofstream m_sink;
};

#endif
