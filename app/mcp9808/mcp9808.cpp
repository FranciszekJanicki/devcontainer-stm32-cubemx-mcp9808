#include "mcp9808.hpp"

namespace MCP9808 {

    MCP9808::MCP9808(I2CDevice&& i2c_device, Config const& config) noexcept :
        scale_{config_to_scale(config)}, i2c_device_{std::forward<I2CDevice>(i2c_device)}
    {
        this->initialize(config);
    }

    MCP9808::~MCP9808() noexcept
    {
        this->deinitialize();
    }

    std::optional<float> MCP9808::get_temperature_scaled() const noexcept
    {
        return this->get_temperature_raw().transform(
            [this](std::int16_t const raw) { return static_cast<float>(raw) * this->scale_; });
    }

    std::uint8_t MCP9808::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_byte(reg_address);
    }

    void MCP9808::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->i2c_device_.write_byte(reg_address, byte);
    }

    void MCP9808::initialize(Config const& config) noexcept
    {
        if (this->is_valid_device_id() && this->is_valid_device_revision() && this->is_valid_manufacturer_id()) {
            this->set_config_register(config.config);
            this->set_t_upper_register(config.t_upper);
            this->set_t_lower_register(config.t_lower);
            this->set_t_crit_register(config.t_crit);
            this->initialized_ = true;
        }
    }

    void MCP9808::deinitialize() noexcept
    {
        if (this->is_valid_device_id() && this->is_valid_device_revision() && this->is_valid_manufacturer_id()) {
            this->initialized_ = false;
        }
    }

    bool MCP9808::is_valid_manufacturer_id() const noexcept
    {
        return this->MCP9808::get_manufacturer_id() == DEFAULT_MANUFACTURER_ID;
    }

    bool MCP9808::is_valid_device_id() const noexcept
    {
        return this->MCP9808::get_device_id() == DEFAULT_DEVICE_ID;
    }

    bool MCP9808::is_valid_device_revision() const noexcept
    {
        return this->MCP9808::get_device_revision() == DEFAULT_DEVICE_REVISION;
    }

    std::uint16_t MCP9808::get_manufacturer_id() const noexcept
    {
        return std::bit_cast<std::uint16_t>(this->get_manufacturer_id_register());
    }

    std::uint8_t MCP9808::get_device_id() const noexcept
    {
        return this->get_device_id_register().device_id;
    }

    std::uint8_t MCP9808::get_device_revision() const noexcept
    {
        return this->get_device_id_register().device_revision;
    }

    std::optional<std::int16_t> MCP9808::get_temperature_raw() const noexcept
    {
        return this->initialized_ ? std::optional<std::int16_t>{this->get_t_ambient_register().t_ambient}
                                  : std::optional<std::int16_t>{std::nullopt};
    }

    CONFIG MCP9808::MCP9808::get_config_register() const noexcept
    {
        return std::bit_cast<CONFIG>(this->read_bytes<sizeof(CONFIG)>(std::to_underlying(RA::CONFIG)));
    }

    void MCP9808::set_config_register(CONFIG const config) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::CONFIG),
                          std::bit_cast<std::array<std::uint8_t, sizeof(CONFIG)>>(config));
    }

    T_UPPER MCP9808::MCP9808::get_t_upper_register() const noexcept
    {
        return std::bit_cast<T_UPPER>(this->read_bytes<sizeof(T_UPPER)>(std::to_underlying(RA::T_UPPER)));
    }

    void MCP9808::set_t_upper_register(T_UPPER const t_upper) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::T_UPPER),
                          std::bit_cast<std::array<std::uint8_t, sizeof(T_UPPER)>>(t_upper));
    }

    T_LOWER MCP9808::MCP9808::get_t_lower_register() const noexcept
    {
        return std::bit_cast<T_LOWER>(this->read_bytes<sizeof(T_LOWER)>(std::to_underlying(RA::T_LOWER)));
    }

    void MCP9808::set_t_lower_register(T_LOWER const t_lower) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::T_LOWER),
                          std::bit_cast<std::array<std::uint8_t, sizeof(T_LOWER)>>(t_lower));
    }

    T_CRIT MCP9808::MCP9808::get_t_crit_register() const noexcept
    {
        return std::bit_cast<T_CRIT>(this->read_bytes<sizeof(T_CRIT)>(std::to_underlying(RA::T_CRIT)));
    }

    void MCP9808::set_t_crit_register(T_CRIT const t_crit) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::T_CRIT),
                          std::bit_cast<std::array<std::uint8_t, sizeof(T_CRIT)>>(t_crit));
    }

    T_AMBIENT MCP9808::MCP9808::get_t_ambient_register() const noexcept
    {
        return std::bit_cast<T_AMBIENT>(this->read_bytes<sizeof(T_AMBIENT)>(std::to_underlying(RA::T_AMBIENT)));
    }

    MANUFACTURER_ID MCP9808::MCP9808::get_manufacturer_id_register() const noexcept
    {
        return std::bit_cast<MANUFACTURER_ID>(
            this->read_bytes<sizeof(MANUFACTURER_ID)>(std::to_underlying(RA::MANUFACTURER_ID)));
    }

    DEVICE_ID MCP9808::MCP9808::get_device_id_register() const noexcept
    {
        return std::bit_cast<DEVICE_ID>(this->read_bytes<sizeof(DEVICE_ID)>(std::to_underlying(RA::DEVICE_ID)));
    }

}; // namespace MCP9808