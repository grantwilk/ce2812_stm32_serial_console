################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CE_Dev_Board_Drivers/Src/delay.c \
../Drivers/CE_Dev_Board_Drivers/Src/uart_driver.c 

OBJS += \
./Drivers/CE_Dev_Board_Drivers/Src/delay.o \
./Drivers/CE_Dev_Board_Drivers/Src/uart_driver.o 

C_DEPS += \
./Drivers/CE_Dev_Board_Drivers/Src/delay.d \
./Drivers/CE_Dev_Board_Drivers/Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CE_Dev_Board_Drivers/Src/delay.o: ../Drivers/CE_Dev_Board_Drivers/Src/delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CE_Dev_Board_Drivers/Src/delay.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CE_Dev_Board_Drivers/Src/uart_driver.o: ../Drivers/CE_Dev_Board_Drivers/Src/uart_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CE_Dev_Board_Drivers/Src/uart_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

