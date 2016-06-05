################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/MW-AHRSv1.c \
../Sources/main.c \
../Sources/pid_control.c \
../Sources/quad_encoder.c 

OBJS += \
./Sources/Events.o \
./Sources/MW-AHRSv1.o \
./Sources/main.o \
./Sources/pid_control.o \
./Sources/quad_encoder.o 

C_DEPS += \
./Sources/Events.d \
./Sources/MW-AHRSv1.d \
./Sources/main.d \
./Sources/pid_control.d \
./Sources/quad_encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTD_FP_IO=1 -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/lib/Kinetis/pdd/inc" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/lib/Kinetis/iofiles" -I"/home/suhan/kinetis_ws/jack-spherobot/Sources" -I"/home/suhan/kinetis_ws/jack-spherobot/Generated_Code" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/system" -I"/opt/Freescale/KDS_v3/eclipse/ProcessorExpert/Repositories/Kinetis_Repository/lib/Kinetis/pdd2/MK64FN1M0LL12/peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


