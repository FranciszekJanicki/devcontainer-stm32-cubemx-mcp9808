#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "i2c_device.hpp"
#include "mcp9808.hpp"
#include "usart.h"
#include <cstdio>

namespace {

    volatile auto interrupt = false;

};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    interrupt = true;
}

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_I2C1_Init();

    using namespace Utility;
    using namespace MCP9808;

    auto i2c_device = I2CDevice{&hi2c1, std::to_underlying(DevAddress::A2L_A1L_A0L)};

    auto config = CONFIG{};

    auto t_upper = T_UPPER{};

    auto t_lower = T_LOWER{};

    auto t_crit = T_CRIT{};

    auto resolution = RESOLUTION{};

    auto mcp_config =
        Config{.config = config, .t_upper = t_upper, .t_lower = t_lower, .t_crit = t_crit, .resolution = resolution};

    auto mcp9808 = MCP9808::MCP9808{std::move(i2c_device), mcp_config};

    while (true) {
        if (interrupt) {
            auto const temperature = mcp9808.get_temperature_scaled().value();
            std::printf("temperature: %f\n\r", temperature);
            interrupt = false;
        }
    }

    return 0;
}
