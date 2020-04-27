/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#ifndef _BWL_KEY_VALUE_PARSER_H_
#define _BWL_KEY_VALUE_PARSER_H_

#include <list>
#include <string>
#include <unordered_map>

namespace bwl {

typedef std::unordered_map<std::string, std::string> parsed_line_t;
typedef std::list<parsed_line_t> parsed_multiline_t;

class KeyValueParser {
protected:
    static void parse_line(std::stringstream &ss_in, std::list<char> delimiter_list,
                           parsed_line_t &parsed_line);

    static void parse_multiline(std::stringstream &ss_in, std::list<char> delimiter_list,
                                parsed_multiline_t &parsed_multiline);

    static bool read_param_int(const std::string &key, parsed_line_t &obj, int64_t &value,
                               bool ignore_unknown = false);

    static bool read_param_str(const std::string &key, parsed_line_t &obj, const char **value);

    static void parsed_obj_debug(parsed_line_t &obj);
    static void parsed_obj_debug(parsed_multiline_t &obj);

    virtual void parse_event(const std::string event_str, parsed_line_t &parsed_line);

    virtual size_t event_buffer_start_process_idx(const std::string &event_str);

    virtual void parse_event_keyless_params(const std::string &event_str, size_t idx_start,
                                            parsed_line_t &parsed_line);
};

} // namespace bwl

#endif // _BWL_KEY_VALUE_PARSER_H_
