//
// Copyright 2015 National Instruments Corp.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <config.h>

#include <uhd/build_info.hpp>

#include <boost/format.hpp>
#include <boost/version.hpp>
#include <boost/algorithm/string.hpp>

#ifdef ENABLE_USB
#include <libusb.h>
#endif

namespace uhd { namespace build_info {

    const std::string boost_version() {
        return boost::algorithm::replace_all_copy(
            std::string(BOOST_LIB_VERSION), "_", "."
        );
    }

    const std::string build_date() {
        return "Sat, 25 Nov 2017 02:40:24";
    }

    const std::string c_compiler() {
        return "GNU 8.0.0";
    }

    const std::string cxx_compiler() {
        return "GNU 8.0.0";
    }

#ifdef _MSC_VER
    static const std::string define_flag = "/D ";
#else
    static const std::string define_flag = "-D";
#endif

    const std::string c_flags() {
        return boost::algorithm::replace_all_copy(
            (define_flag + std::string("UHD_IMAGES_DIR=OFF;HAVE_CONFIG_H")),
            std::string(";"), (" " + define_flag)
        );
    }

    const std::string cxx_flags() {
        return boost::algorithm::replace_all_copy(
            (define_flag + std::string("UHD_IMAGES_DIR=OFF;HAVE_CONFIG_H -fvisibility=hidden -fvisibility-inlines-hidden")),
            std::string(";"), (" " + define_flag)
        );
    }

    const std::string enabled_components() {
        return boost::algorithm::replace_all_copy(
            std::string("LibUHD;LibUHD - C API;Examples;Utils;Tests;USB;B100;B200;USRP1;USRP2;X300;N230;OctoClock"),
            std::string(";"), std::string(", ")
        );
    }

    const std::string install_prefix() {
        return "/usr/local";
    }

    const std::string libusb_version() {
    #ifdef ENABLE_USB
        /*
         * Versions can only be queried from 1.0.13 onward.
         * Depending on if the commit came from libusbx or
         * libusb (now merged), the define might be different.
         */
        #ifdef LIBUSB_API_VERSION /* 1.0.18 onward */
            int major_version = LIBUSB_API_VERSION >> 24;
            int minor_version = (LIBUSB_API_VERSION & 0xFF0000) >> 16;
            int micro_version = ((LIBUSB_API_VERSION & 0xFFFF) - 0x100) + 18;

            return str(boost::format("%d.%d.%d")
                          % major_version % minor_version % micro_version);
        #elif defined(LIBUSBX_API_VERSION) /* 1.0.13 - 1.0.17 */
            switch(LIBUSBX_API_VERSION & 0xFF) {
                case 0x00:
                    return "1.0.13";
                case 0x01:
                    return "1.0.15";
                case 0xFF:
                    return "1.0.14";
                default:
                    return "1.0.16 or 1.0.17";
            }
        #else
            return "< 1.0.13";
        #endif
    #else
        return "N/A";
    #endif
    }
}}
