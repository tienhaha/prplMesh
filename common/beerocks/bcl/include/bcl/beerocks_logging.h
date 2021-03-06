/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2016-2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _BEEROCKS_LOGGING_H_
#define _BEEROCKS_LOGGING_H_

#include <map>
#include <set>
#include <string>

#include "beerocks_config_file.h"
#include "beerocks_defines.h"
#include "beerocks_string_utils.h"

namespace beerocks {
#define CONSOLE_MSG(a)                                                                             \
    do {                                                                                           \
        std::cout << a << "\r\n" << std::flush;                                                    \
    } while (0)
#define CONSOLE_MSG_INPLACE(a)                                                                     \
    do {                                                                                           \
        std::cout << "\r" << a << std::flush;                                                      \
    } while (0)

extern const std::string BEEROCKS_LOGGING_MODULE_NAME;
#define BEEROCKS_INIT_LOGGING(module_name)                                                         \
    const std::string beerocks::BEEROCKS_LOGGING_MODULE_NAME = (module_name);

class log_levels {
public:
    typedef std::set<std::string> set_t;

    log_levels()                   = default;
    ~log_levels()                  = default;
    log_levels(const log_levels &) = default;
    explicit log_levels(const std::set<std::string> &log_levels);
    explicit log_levels(const std::string &log_level_str);
    log_levels &operator=(const log_levels &rhs);
    log_levels &operator=(const std::string &log_level_str);
    log_levels operator&(const log_levels &rhs);

    std::string to_string();
    void parse_string(const std::string &log_level_str);

    bool is_all();
    bool is_off();

    bool fatal_enabled();
    bool error_enabled();
    bool warning_enabled();
    bool info_enabled();
    bool debug_enabled();
    bool trace_enabled();

    void set_log_level_state(const eLogLevel &log_level, const bool &new_state);

private:
    std::set<std::string> m_level_set;
};

extern const log_levels LOG_LEVELS_ALL;
extern const log_levels LOG_LEVELS_OFF;
extern const log_levels LOG_LEVELS_GLOBAL_DEFAULT;
extern const log_levels LOG_LEVELS_MODULE_DEFAULT;
extern const log_levels LOG_LEVELS_SYSLOG_DEFAULT;

class logging {
public:
    typedef std::map<std::string, std::string> settings_t;

    logging(const std::string &config_path = std::string(),
            const std::string &module_name = BEEROCKS_LOGGING_MODULE_NAME);
    explicit logging(const settings_t &settings, bool cache_settings = false,
                     const std::string &module_name = BEEROCKS_LOGGING_MODULE_NAME);
    logging(const beerocks::config_file::SConfigLog &settings, const std::string &module_name,
            bool cache_settings = false);
    ~logging() = default;

    void apply_settings();

    std::string get_module_name();
    log_levels get_log_levels();
    log_levels get_syslog_levels();
    std::string get_log_max_size_setting();
    bool get_log_files_enabled();
    std::string get_log_files_path();
    std::string get_log_filepath();
    std::string get_log_filename();
    bool get_log_files_auto_roll();
    bool get_stdout_enabled();
    bool get_syslog_enabled();

    void set_log_level_state(const eLogLevel &log_level, const bool &new_state);

    // TBD: Can/Should these be removed?
    size_t get_log_rollover_size();
    size_t get_log_max_size();

protected:
    bool load_settings(const std::string &config_file_path);
    std::string get_config_path(std::string config_path);
    std::string get_cache_path();
    bool save_settings(const std::string &config_file_path);

    void set_log_path(std::string log_path);
    void eval_settings();

    static void handle_logging_rollover(const char *, std::size_t);

private:
    static const std::string format;
    static const std::string syslogFormat;

    std::string m_module_name;

    size_t m_logfile_size;
    bool m_log_files_enabled = true;
    std::string m_log_files_path;
    std::string m_log_filename;
    bool m_log_files_auto_roll = true;
    log_levels m_levels;
    log_levels m_syslog_levels;
    bool m_stdout_enabled = true;
    bool m_syslog_enabled = false;

    settings_t m_settings_map;
};

} // namespace beerocks

#endif // _BEEROCKS_LOGGING_H_
