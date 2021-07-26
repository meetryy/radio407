################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../radio407/drivers/ili9341/ili9341.c \
../radio407/drivers/ili9341/ili9341_font.c \
../radio407/drivers/ili9341/ili9341_gfx.c 

OBJS += \
./ili9341/ili9341.o \
./ili9341/ili9341_font.o \
./ili9341/ili9341_gfx.o 

C_DEPS += \
./ili9341/ili9341.d \
./ili9341/ili9341_font.d \
./ili9341/ili9341_gfx.d 


# Each subdirectory must supply rules for building sources it contributes
ili9341/ili9341.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341/ili9341.c ili9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ili9341/ili9341.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ili9341/ili9341_font.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341/ili9341_font.c ili9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ili9341/ili9341_font.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ili9341/ili9341_gfx.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341/ili9341_gfx.c ili9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ili9341/ili9341_gfx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

