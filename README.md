# UART_INTERRUPT_STM32
STM32G4 Bare-Metal Interrupt Systems
This repository contains two foundational bare-metal projects for the STM32G4 series, focusing on transitioning from polling-based logic to Event-Driven Programming using Interrupt Service Routines (ISRs).

Project 1: External GPIO Interrupts (EXTI)
Goal: Detect a physical button press on PC13 without hogging CPU cycles.

Key Registers: SYSCFG->EXTICR[3], EXTI->IMR1, EXTI->FTSR1.

Outcome: Asynchronous LED toggling based on hardware edge detection.

Project 2: Interrupt-Driven UART with Callbacks
Goal: High-efficiency serial communication using RXNE (Receive) and TXE (Transmit) interrupts.

Key Registers: USART2->CR1 (Interrupt Enables), USART2->ISR (Status checking

 Feature: The Callback Architecture
Instead of putting application logic (like toggling an LED) directly inside the IRQHandler, this project uses Static Callbacks.

uart_callback(): Triggered when a byte arrives. It parses the command (e.g., '1' for LED ON) without blocking the main() loop.

uart_callback_tx(): Triggered when the Transmit Data Register is ready for more data.
