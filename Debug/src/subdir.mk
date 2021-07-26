################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../radio407/src/adc.c \
../radio407/src/agc.c \
../radio407/src/aic23b.c \
../radio407/src/audio_routing.c \
../radio407/src/buttons.c \
../radio407/src/dsp.c \
../radio407/src/encoder.c \
../radio407/src/fir.c \
../radio407/src/gfx.c \
../radio407/src/gfx_items.c \
../radio407/src/hw.c \
../radio407/src/lcd.c \
../radio407/src/local_gen.c \
../radio407/src/tools.c 

OBJS += \
./src/adc.o \
./src/agc.o \
./src/aic23b.o \
./src/audio_routing.o \
./src/buttons.o \
./src/dsp.o \
./src/encoder.o \
./src/fir.o \
./src/gfx.o \
./src/gfx_items.o \
./src/hw.o \
./src/lcd.o \
./src/local_gen.o \
./src/tools.o 

C_DEPS += \
./src/adc.d \
./src/agc.d \
./src/aic23b.d \
./src/audio_routing.d \
./src/buttons.d \
./src/dsp.d \
./src/encoder.d \
./src/fir.d \
./src/gfx.d \
./src/gfx_items.d \
./src/hw.d \
./src/lcd.d \
./src/local_gen.d \
./src/tools.d 


# Each subdirectory must supply rules for building sources it contributes
src/adc.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/adc.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/agc.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/agc.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/agc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/aic23b.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/aic23b.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/aic23b.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/audio_routing.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/audio_routing.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/audio_routing.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/buttons.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/buttons.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/buttons.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/dsp.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/dsp.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/dsp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/encoder.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/encoder.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/encoder.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/fir.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/fir.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/fir.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/gfx.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/gfx.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/gfx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/gfx_items.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/gfx_items.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/gfx_items.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/hw.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/hw.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/hw.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/lcd.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/lcd.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/local_gen.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/local_gen.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/local_gen.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/tools.o: C:/Google\ Drive/cubeIDE_workspace/radio407/radio407/src/tools.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -D__FPU_PRESENT -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/inc" -I"C:/Google Drive/cubeIDE_workspace/radio407/radio407/drivers/ili9341" -I"C:/Google Drive/cubeIDE_workspace/radio407/Drivers/CMSIS/DSP/Include" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/tools.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

