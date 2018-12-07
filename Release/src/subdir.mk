################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Swatchdog.cpp \
../src/procMgr.cpp \
../src/procMgr_linux.cpp \
../src/service.cpp \
../src/service_unix.cpp 

OBJS += \
./src/Swatchdog.o \
./src/procMgr.o \
./src/procMgr_linux.o \
./src/service.o \
./src/service_unix.o 

CPP_DEPS += \
./src/Swatchdog.d \
./src/procMgr.d \
./src/procMgr_linux.d \
./src/service.d \
./src/service_unix.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -DOS_LINUX -DOSAPI_TRACING -I"/home/joao/workspace/HASI/service/inc" -I"/home/joao/workspace/osapi_plus/code" -O0 -g3 -p -pg -ftest-coverage -fprofile-arcs -Wall -Wextra -Wconversion -c -fmessage-length=0 -fstack-protector-all -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


