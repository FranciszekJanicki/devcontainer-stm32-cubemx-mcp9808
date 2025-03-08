#ifndef MCP9808_HPP
#define MCP9808_HPP

#include "i2c_device.hpp"
#include "mcp9808_config.hpp"
#include "mcp9808_registers.hpp"
#include <optional>

namespace MCP9808 {

    struct MCP9808 {
    public:
        using I2CDevice = Utility::I2CDevice;

        MCP9808() noexcept = default;
        MCP9808(I2CDevice&& i2c_device, Config const& config) noexcept;

        MCP9808(MCP9808 const& other) = delete;
        MCP9808(MCP9808&& other) noexcept = default;

        MCP9808& operator=(MCP9808 const& other) = delete;
        MCP9808& operator=(MCP9808&& other) noexcept = default;

        ~MCP9808() noexcept;

        std::optional<float> get_temperature_scaled() const noexcept;

    private:
        std::uint8_t read_byte(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(std::uint8_t const reg_address) const noexcept;

        void write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        void write_bytes(std::uint8_t const reg_address, std::array<std::uint8_t, SIZE> const& bytes) const noexcept;

        void initialize(Config const& config) noexcept;
        void deinitialize() noexcept;

        bool is_valid_manufacturer_id() const noexcept;
        bool is_valid_device_id() const noexcept;
        bool is_valid_device_revision() const noexcept;

        std::uint16_t get_manufacturer_id() const noexcept;
        std::uint8_t get_device_id() const noexcept;
        std::uint8_t get_device_revision() const noexcept;

        std::optional<std::int16_t> get_temperature_raw() const noexcept;

        CONFIG get_config_register() const noexcept;
        void set_config_register(CONFIG const config) const noexcept;

        T_UPPER get_t_upper_register() const noexcept;
        void set_t_upper_register(T_UPPER const t_upper) const noexcept;

        T_LOWER get_t_lower_register() const noexcept;
        void set_t_lower_register(T_LOWER const t_lower) const noexcept;

        T_CRIT get_t_crit_register() const noexcept;
        void set_t_crit_register(T_CRIT const t_crit) const noexcept;

        T_AMBIENT get_t_ambient_register() const noexcept;

        MANUFACTURER_ID get_manufacturer_id_register() const noexcept;

        DEVICE_ID get_device_id_register() const noexcept;

        bool initialized_{false};

        float scale_{};

        I2CDevice i2c_device_{};
    };

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, SIZE> MCP9808::read_bytes(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_bytes<SIZE>(reg_address);
    }

    template <std::size_t SIZE>
    inline void MCP9808::write_bytes(std::uint8_t const reg_address,
                                     std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        this->i2c_device_.write_bytes(reg_address, bytes);
    }

}; // namespace MCP9808

#endif // MCP9808_HPP