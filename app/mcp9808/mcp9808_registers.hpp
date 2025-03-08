#ifndef MCP9808_REGISTERS_HPP
#define MCP9808_REGISTERS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace MCP9808 {

    struct REGISTER_POINTER {
        std::uint8_t : 4;
        std::uint8_t pointer : 4;
    } PACKED;

    struct CONFIG {
        std::uint8_t : 5;
        std::uint8_t t_hyst : 2;
        std::uint8_t shdn : 1;
        std::uint8_t crit_lock : 1;
        std::uint8_t win_lock : 1;
        std::uint8_t int_clear : 1;
        std::uint8_t alert_stat : 1;
        std::uint8_t alert_cnt : 1;
        std::uint8_t alert_sel : 1;
        std::uint8_t alert_pol : 1;
        std::uint8_t aler_mod : 1;
    } PACKED;

    struct T_UPPER {
        std::uint8_t : 3;
        std::uint16_t t_upper : 10;
        std::uint8_t : 3;
    } PACKED;

    struct T_LOWER {
        std::uint8_t : 3;
        std::uint16_t t_lower : 11;
        std::uint8_t : 2;
    } PACKED;

    struct T_CRIT {
        std::uint8_t : 3;
        std::uint16_t t_crit : 11;
        std::uint8_t : 2;
    } PACKED;

    struct T_AMBIENT {
        std::uint8_t t_crit : 1;
        std::uint8_t t_upper : 1;
        std::uint8_t t_lower : 1;
        std::uint16_t t_ambient : 13;
    } PACKED;

    struct MANUFACTURER_ID {
        std::uint16_t manufacturer_id : 16;
    } PACKED;

    struct DEVICE_ID {
        std::uint8_t device_id : 8;
        std::uint8_t device_revision : 8;
    } PACKED;

    struct RESOLUTION {
        std::uint8_t : 6;
        std::uint8_t resolution : 2;
    } PACKED;

    struct Config {
        CONFIG config{};
        T_UPPER t_upper{};
        T_LOWER t_lower{};
        T_CRIT t_crit{};
        RESOLUTION resolution{};
    };

}; // namespace MCP9808

#undef PACKED

#endif // MCP9808_REGISTERS_HPP