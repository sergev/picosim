/*!
 \file log.cpp
 \brief Class to manage Log
 \author Màrius Montón
 \date Aug 2018
 */
// SPDX-License-Identifier: GPL-3.0-or-later

#include "log.h"

//
// Return a stream to print an error message.
//
std::ostream &Log::err()
{
    // Print to stdout or the log file, when opened.
    std::ostream &out = m_stream.is_open() ? m_stream : std::cout;

    // Set flags to default.
    std::ios_base::fmtflags default_flags{};
    out.flags(default_flags);

    auto time_nsec = sc_core::sc_time_stamp().value();
    out << '(' << std::dec << time_nsec << ") ";
    return out;
}

//
// Return a stream to print a non-critical message.
//
std::ostream &Log::out()
{
    if (!m_stream.is_open()) {
        // Ignore non-critical messages.
        return m_sink;
    }
    return err();
}

//
// When filename is nonempty: enable verbose log output to the file.
// When filename is nempty: disable verbose output, send it to stdout.
//
void Log::set_verbose(const std::string &fname)
{
    filename = fname;

    if (m_stream.is_open()) {
        m_stream.close();
        if (filename.empty()) {
            // std::cout << "Log disabled" << std::endl;
        }
    }

    if (!filename.empty()) {
        m_stream.open(filename);
        // std::cout << "Log redirected to " << filename << std::endl;
    }
}

//
// Return true when verbose mode is enabled (output to a file).
//
bool Log::is_verbose()
{
    return m_stream.is_open();
}

std::string Log::filename;
std::ofstream Log::m_stream;
std::ofstream Log::m_sink;
