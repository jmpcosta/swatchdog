################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../code/src/procMgr.cpp \
../code/src/service.cpp \
../code/src/swatchdog.cpp 

OBJS += \
./code/src/procMgr.o \
./code/src/service.o \
./code/src/swatchdog.o 

CPP_DEPS += \
./code/src/procMgr.d \
./code/src/service.d \
./code/src/swatchdog.d 


# Each subdirectory must supply rules for building sources it contributes
code/src/%.o: ../code/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DOS_LINUX -I${SWATCHDOG_DIR}/code/inc -I"${OSAPI_PLUS_DIR}/code" -O3 -Wall -Wextra -Wconversion -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


