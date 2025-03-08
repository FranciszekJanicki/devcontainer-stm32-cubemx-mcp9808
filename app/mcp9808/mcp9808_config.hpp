#ifndef MCP9808_CONFIG_HPP
#define MCP9808_CONFIG_HPP

#include "mcp9808_registers.hpp"
#include <cstdint>

namespace MCP9808 {

    enum struct DevAddress : std::uint8_t {
        A2L_A1L_A0L = 0b0011000,
        A2L_A1L_A0H = 0b0011001,
        A2L_A1H_A0H = 0b0011011,
        A2H_A1H_A0H = 0b0011111,
        A2H_A1H_A0L = 0b0011110,
        A2H_A1L_A0L = 0b0011100,
        A2L_A1H_A0L = 0b0011010,
        A2H_A1L_A0H = 0b0011101,
    };

    enum struct RA : std::uint8_t {
        REGISTER_POINTER = 0x00,
        CONFIG = 0x01,
        T_UPPER = 0x02,
        T_LOWER = 0x03,
        T_CRIT = 0x04,
        T_AMBIENT = 0x05,
        MANUFACTURER_ID = 0x06,
        DEVICE_ID = 0x07,
        RESOLUTION = 0x08,
    };

    enum struct LimitHyst : std::uint8_t {
        HYST_0C0 = 0b00,
        HYST_1C5 = 0b01,
        HYST_3C0 = 0b10,
        HYST_6C0 = 0b11,
    };

    enum struct Mode : std::uint8_t {
        CONTINUOUS = 0b00,
        SHUTDOWN = 0b01,
    };

    enum struct CritLock : std::uint8_t {
        UNLOCKED = 0b00,
        LOCKED = 0b01,
    };

    enum struct WinLock : std::uint8_t {
        UNLOCKED = 0b00,
        LOCKED = 0b01,
    };

    enum struct IntClear : std::uint8_t {
        NO_EFFECT = 0b00,
        CLEAR_DATA_READY = 0b01,
    };

    enum struct AlertStat : std::uint8_t {
        DISABLE_ALERT = 0b00,
        ASSERT_ALERT = 0b01,
    };

    enum struct AlertCnt : std::uint8_t {
        ENABLED = 0b01,
        DISABLED = 0b00,
    };

    enum struct AlertSel : std::uint8_t {
        ALERT_ALL = 0b00,
        ALERT_CRIT_ONLY = 0b01,
    };

    enum struct AlertPol : std::uint8_t {
        ACTIVE_LOW = 0b00,
        ACTIVE_HIGH = 0b01,
    };

    enum struct AlertMod : std::uint8_t {
        COMPARATOR_OUTPUT = 0b00,
        INTERRUPT_OUTPUT = 0b01,
    };

    enum struct Resolution : std::uint8_t {
        RES_0C5 = 0b00,
        RES_0C25 = 0b01,
        RES_0C125 = 0b10,
        RES_0C0625 = 0b11,
    };

    constexpr std::uint8_t DEFAULT_DEVICE_ID = 0x04;
    constexpr std::uint16_t DEFAULT_MANUFACTURER_ID = 0x0054;
    constexpr std::uint8_t DEFAULT_DEVICE_REVISION = 0x00;

    inline float resolution_to_scale(Resolution const resolution) noexcept
    {
        switch (resolution) {
            case Resolution::RES_0C5:
                return 0.5F;
            case Resolution::RES_0C25:
                return 0.25F;
            case Resolution::RES_0C125:
                return 0.125F;
            case Resolution::RES_0C0625:
                return 0.0625F;
            default:
                return 0.0F;
        }
    }

    inline float config_to_scale(Config const& config) noexcept
    {
        return resolution_to_scale(static_cast<Resolution>(config.resolution.resolution));
    }

}; // namespace MCP9808

#endif // MCP9808_CONFIG_HPP