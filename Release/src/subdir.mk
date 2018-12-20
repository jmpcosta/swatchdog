################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/procMgr.cpp \
../src/procMgr_linux.cpp \
../src/service.cpp \
../src/service_unix.cpp \
../src/swatchdog.cpp \
../src/systemService_unix.cpp 

OBJS += \
./src/procMgr.o \
./src/procMgr_linux.o \
./src/service.o \
./src/service_unix.o \
./src/swatchdog.o \
./src/systemService_unix.o 

CPP_DEPS += \
./src/procMgr.d \
./src/procMgr_linux.d \
./src/service.d \
./src/service_unix.d \
./src/swatchdog.d \
./src/systemService_unix.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DOS_LINUX -I../inc -I/usr/include -I../../../osapi_plus/code -I"/osapi_plus/code" -O3 -Wall -Wextra -Wconversion -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


