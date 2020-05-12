/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * SPDX-FileCopyrightText: 2020 the prplMesh contributors (see AUTHORS.md)
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include "bwl/nl80211_client.h"

namespace bwl {

bool nl80211_client::SurveyInfo::get_channel_utilization(uint8_t &channel_utilization) const
{
    channel_utilization = UINT8_MAX;

    auto it =
        std::find_if(data.begin(), data.end(), [](const sChannelSurveyInfo &channel_survey_info) {
            return channel_survey_info.in_use;
        });

    if (it == data.end()) {
        return false;
    }

    auto survey_info = *it;

    if (0 == survey_info.time_on_ms) {
        return false;
    }

    channel_utilization = survey_info.time_busy_ms / survey_info.time_on_ms;

    return true;
}

} // namespace bwl
