################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals/USB0_Init.c \
/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals/VREF_Init.c 

OBJS += \
./Static_Code/Peripherals/USB0_Init.o \
./Static_Code/Peripherals/VREF_Init.o 

C_DEPS += \
./Static_Code/Peripherals/USB0_Init.d \
./Static_Code/Peripherals/VREF_Init.d 


# Each subdirectory must supply rules for building sources it contributes
Static_Code/Peripherals/USB0_Init.o: /opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals/USB0_Init.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTD_FP_IO=1 -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/lib/Kinetis/pdd/inc" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/lib/Kinetis/iofiles" -I"/home/suhan/kinetis_ws/jack-spherobot/Sources" -I"/home/suhan/kinetis_ws/jack-spherobot/Generated_Code" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/system" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Static_Code/Peripherals/VREF_Init.o: /opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals/VREF_Init.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTD_FP_IO=1 -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/lib/Kinetis/pdd/inc" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/lib/Kinetis/iofiles" -I"/home/suhan/kinetis_ws/jack-spherobot/Sources" -I"/home/suhan/kinetis_ws/jack-spherobot/Generated_Code" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/system" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


