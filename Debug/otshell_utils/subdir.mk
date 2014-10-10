################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../otshell_utils/ccolor.cpp \
../otshell_utils/runoptions.cpp \
../otshell_utils/utils.cpp 

OBJS += \
./otshell_utils/ccolor.o \
./otshell_utils/runoptions.o \
./otshell_utils/utils.o 

CPP_DEPS += \
./otshell_utils/ccolor.d \
./otshell_utils/runoptions.d \
./otshell_utils/utils.d 


# Each subdirectory must supply rules for building sources it contributes
otshell_utils/%.o: ../otshell_utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/boost -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


