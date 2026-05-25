# STM32F401xx GPIO Driver Documentation

## 1. Development Flow (Step-by-Step)

### Step 1: Define Base Addresses & Register Structures
- Defined memory-mapped base addresses for GPIO peripherals (GPIOA–GPIOH).
- Created `GPIO_RegDef_t` structure mapping all GPIO registers (MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, AFR, etc.).

### Step 2: Define Clock Enable/Disable Macros
- Created macros (`GPIOA_PCLK_EN()`, `GPIOA_PCLK_DI()`, etc.) to enable/disable peripheral clocks via RCC AHB1ENR register.
- Created reset macros (`GPIOA_REG_RESET()`, etc.) using RCC AHB1RSTR.

### Step 3: Create Pin Configuration Structure
- Defined `GPIO_PinConfig_t` with fields: PinNumber, PinMode, PinSpeed, PinPuPdControl, PinOPType, PinAltFunMode.
- Defined `GPIO_Handle_t` containing a pointer to GPIO port + pin config.

### Step 4: Implement Peripheral Clock Control API
- `GPIO_PeriClockControl()` — enables/disables clock based on port base address.

### Step 5: Implement Init/DeInit APIs
- `GPIO_Init()` — configures mode, speed, pull-up/down, output type, alternate function, and interrupt (EXTI) settings.
- `GPIO_DeInit()` — resets all port registers via RCC reset register.

### Step 6: Implement Data Read/Write APIs
- Read from input pin/port via IDR.
- Write to output pin/port via ODR.
- Toggle output pin using XOR on ODR.

### Step 7: Implement Interrupt Configuration APIs
- Configure EXTI trigger (rising/falling/both) via FTSR/RTSR.
- Map GPIO port to EXTI line via SYSCFG EXTICR registers.
- Enable EXTI line in IMR.
- Enable/disable IRQ in NVIC (ISER/ICER).
- Set priority via NVIC priority registers.
- Handle IRQ by clearing EXTI pending register.

---

## 2. API Reference

| API | Description |
|-----|-------------|
| `GPIO_PeriClockControl(pGPIOx, EnorDi)` | Enable/disable peripheral clock for a GPIO port |
| `GPIO_Init(pGPIOHandle)` | Initialize a GPIO pin with the given configuration |
| `GPIO_DeInit(pGPIOx)` | Reset all registers of a GPIO port to default |
| `GPIO_ReadFromInputPin(pGPIOx, PinNumber)` | Read a single pin (returns 0 or 1) |
| `GPIO_ReadFromInputPort(pGPIOx)` | Read entire 16-bit input port |
| `GPIO_WritetoOutputPin(pGPIOx, PinNumber, Value)` | Write 0 or 1 to a specific output pin |
| `GPIO_WritetoOutputort(pGPIOx, Value)` | Write a 16-bit value to the entire output port |
| `GPIO_ToggleOutputPin(pGPIOx, PinNumber)` | Toggle a specific output pin |
| `GPIO_IRQInterruptConfig(IRQNumber, EnorDi)` | Enable/disable an IRQ in NVIC |
| `GPIO_IRQPriorityConfig(IRQNumber, IRQPriority)` | Set priority (0–15) for an IRQ |
| `GPIO_IRQHandling(PinNumber)` | Clear the EXTI pending bit for a pin (call inside ISR) |

### Quick Usage Example

```c
// 1. Enable clock
GPIO_PeriClockControl(GPIOA, ENABLE);

// 2. Configure pin
GPIO_Handle_t gpioLed;
gpioLed.pGPIOx = GPIOA;
gpioLed.GPIO_PinConfig.GPIO_PinNumber = 5;
gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
gpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
gpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
gpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

// 3. Initialize
GPIO_Init(&gpioLed);

// 4. Toggle
GPIO_ToggleOutputPin(GPIOA, 5);
```
