/*
 * Copyright (c) 2012-2015 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include <kern/debug.h>
#include <kern/err.h>
#include <assert.h>
#include <dev/gpio.h>
#include <platform/stm32.h>
#include <platform/gpio.h>

static GPIO_TypeDef *port_to_pointer(unsigned int port) {
    DEBUG_ASSERT(port <= GPIO_PORT_K);

    switch (port) {
        default:
        case GPIO_PORT_A:
            return GPIOA;
        case GPIO_PORT_B:
            return GPIOB;
        case GPIO_PORT_C:
            return GPIOC;
        case GPIO_PORT_D:
            return GPIOD;
        case GPIO_PORT_E:
            return GPIOE;
        case GPIO_PORT_F:
            return GPIOF;
        case GPIO_PORT_G:
            return GPIOG;
        case GPIO_PORT_H:
            return GPIOH;
        case GPIO_PORT_I:
            return GPIOI;
        case GPIO_PORT_J:
            return GPIOJ;
        case GPIO_PORT_K:
            return GPIOK;
    }
}

static void enable_port(unsigned int port) {
    DEBUG_ASSERT(port <= GPIO_PORT_K);

    switch (port) {
        case GPIO_PORT_A:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case GPIO_PORT_B:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case GPIO_PORT_C:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case GPIO_PORT_D:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        case GPIO_PORT_E:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
        case GPIO_PORT_F:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
        case GPIO_PORT_G:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
        case GPIO_PORT_H:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
        case GPIO_PORT_I:
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
        case GPIO_PORT_J:
            __HAL_RCC_GPIOJ_CLK_ENABLE();
            break;
        case GPIO_PORT_K:
            __HAL_RCC_GPIOK_CLK_ENABLE();
            break;
    }
}

void stm32_gpio_early_init(void) {
}

int gpio_config(unsigned nr, unsigned flags) {
    uint port = GPIO_PORT(nr);
    uint pin = GPIO_PIN(nr);

    enable_port(port);

    GPIO_InitTypeDef init;
    init.Speed = GPIO_SPEED_HIGH;
    init.Pin = (1 << pin);
    init.Alternate = 0;

    if (flags & GPIO_INPUT) {
        init.Mode = GPIO_MODE_INPUT;
    } else if (flags & GPIO_OUTPUT) {
        if (flags & GPIO_STM32_OD) {
            init.Mode = GPIO_MODE_OUTPUT_OD;
        } else {
            init.Mode = GPIO_MODE_OUTPUT_PP;
        }
    } else if (flags & GPIO_STM32_AF) {
        if (flags & GPIO_STM32_OD) {
            init.Mode = GPIO_MODE_AF_OD;
        } else {
            init.Mode = GPIO_MODE_AF_PP;
        }
        init.Alternate = GPIO_AFNUM(flags);
    } else {
        panic("stm32f7: invalid args to gpio_config\n");
        return ERR_INVALID_ARGS;
    }

    if (flags & GPIO_PULLUP) {
        init.Pull = GPIO_PULLUP;
    } else if (flags & GPIO_PULLDOWN) {
        init.Pull = GPIO_PULLDOWN;
    } else {
        init.Pull = GPIO_NOPULL;
    }

    HAL_GPIO_Init(port_to_pointer(port), &init);

    return 0;
}

void gpio_set(unsigned nr, unsigned on) {
    HAL_GPIO_WritePin(port_to_pointer(GPIO_PORT(nr)), 1 << GPIO_PIN(nr), on);
}

int gpio_get(unsigned nr) {
    return HAL_GPIO_ReadPin(port_to_pointer(GPIO_PORT(nr)), 1 << GPIO_PIN(nr));
}

