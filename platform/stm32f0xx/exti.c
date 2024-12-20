/*
 * Copyright (c) 2017 The Fuchsia Authors.
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */

#include <platform/exti.h>

#include <arch/arm/cm.h>
#include <assert.h>
#include <kern/compiler.h>
#include <platform/rcc.h>
#include <stdint.h>

bool __WEAK stm32_exti0_irq(void) {
    return false;
}

bool __WEAK stm32_exti1_irq(void) {
    return false;
}

bool __WEAK stm32_exti2_irq(void) {
    return false;
}

bool __WEAK stm32_exti3_irq(void) {
    return false;
}

bool __WEAK stm32_exti4_irq(void) {
    return false;
}

bool __WEAK stm32_exti5_irq(void) {
    return false;
}

bool __WEAK stm32_exti6_irq(void) {
    return false;
}

bool __WEAK stm32_exti7_irq(void) {
    return false;
}

bool __WEAK stm32_exti8_irq(void) {
    return false;
}

bool __WEAK stm32_exti9_irq(void) {
    return false;
}

bool __WEAK stm32_exti10_irq(void) {
    return false;
}

bool __WEAK stm32_exti11_irq(void) {
    return false;
}

bool __WEAK stm32_exti12_irq(void) {
    return false;
}

bool __WEAK stm32_exti13_irq(void) {
    return false;
}

bool __WEAK stm32_exti14_irq(void) {
    return false;
}

bool __WEAK stm32_exti15_irq(void) {
    return false;
}

#define STM32_DISPATCH_EXTI(pr, irq, resched) do { \
    if ((pr) & (1 << (irq))) { \
        resched |= stm32_exti ## irq ## _irq(); \
    } \
 } while(0)

void stm32_EXTI0_1_IRQ(void) {
    arm_cm_irq_entry();

    uint32_t pr = EXTI->PR & 0x3;
    EXTI->PR = pr;

    bool resched = false;
    STM32_DISPATCH_EXTI(pr, 0, resched);
    STM32_DISPATCH_EXTI(pr, 1, resched);

    arm_cm_irq_exit(resched);
}

void stm32_EXTI2_3_IRQ(void) {
    arm_cm_irq_entry();

    uint32_t pr = EXTI->PR & (0x3 << 2);
    EXTI->PR = pr;

    bool resched = false;
    STM32_DISPATCH_EXTI(pr, 2, resched);
    STM32_DISPATCH_EXTI(pr, 3, resched);

    arm_cm_irq_exit(resched);
}

void stm32_EXTI4_15_IRQ(void) {
    arm_cm_irq_entry();

    uint32_t pr = EXTI->PR & 0xfff0U;
    EXTI->PR = pr;

    bool resched = false;
    STM32_DISPATCH_EXTI(pr, 4, resched);
    STM32_DISPATCH_EXTI(pr, 5, resched);
    STM32_DISPATCH_EXTI(pr, 6, resched);
    STM32_DISPATCH_EXTI(pr, 7, resched);
    STM32_DISPATCH_EXTI(pr, 8, resched);
    STM32_DISPATCH_EXTI(pr, 9, resched);
    STM32_DISPATCH_EXTI(pr, 10, resched);
    STM32_DISPATCH_EXTI(pr, 11, resched);
    STM32_DISPATCH_EXTI(pr, 12, resched);
    STM32_DISPATCH_EXTI(pr, 13, resched);
    STM32_DISPATCH_EXTI(pr, 14, resched);
    STM32_DISPATCH_EXTI(pr, 15, resched);

    arm_cm_irq_exit(resched);
}

#undef STM32_DISPATCH_EXTI

void stm32_setup_ext_interrupt(int interrupt, stm32_ext_interrupt_port_t port,
                               bool rising_edge, bool falling_edge) {
    assert(0 <= interrupt && interrupt <= 15);

    stm32_rcc_set_enable(STM32_RCC_CLK_SYSCFGCOMP, true);

    uint32_t cfg = SYSCFG->EXTICR[interrupt >> 2];
    uint shift = 4 * (interrupt & 0x3);
    cfg &= SYSCFG_EXTICR1_EXTI0 << shift;
    cfg |= port << shift;
    SYSCFG->EXTICR[interrupt >> 2] = cfg;

    if (rising_edge) {
        EXTI->RTSR |= 1 << interrupt;
    } else {
        EXTI->RTSR &= ~(1 << interrupt);
    }

    if (falling_edge) {
        EXTI->FTSR |= 1 << interrupt;
    } else {
        EXTI->FTSR &= ~(1 << interrupt);
    }

    EXTI->IMR |= 1 << interrupt;
    EXTI->PR = 1 << interrupt;

    if (0 <= interrupt && interrupt <= 1) {
        NVIC_EnableIRQ(EXTI0_1_IRQn);
    } else if (2 <= interrupt && interrupt <= 3) {
        NVIC_EnableIRQ(EXTI2_3_IRQn);
    } else if (4 <= interrupt && interrupt <= 15) {
        NVIC_EnableIRQ(EXTI4_15_IRQn);
    }
}
