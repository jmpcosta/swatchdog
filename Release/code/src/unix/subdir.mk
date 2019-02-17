################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/src/unix/procMgr_unix.cpp \
../code/src/unix/service_unix.cpp 

OBJS += \
./code/src/unix/procMgr_unix.o \
./code/src/unix/service_unix.o 

CPP_DEPS += \
./code/src/unix/procMgr_unix.d \
./code/src/unix/service_unix.d 


# Each subdirectory must supply rules for building sources it contributes
code/src/unix/%.o: ../code/src/unix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DOS_LINUX -I${SWATCHDOG_DIR}/code/inc -I"${OSAPI_PLUS_DIR}/code" -O3 -Wall -Wextra -Wconversion -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


