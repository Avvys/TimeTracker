################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../analyser.cpp \
../info.cpp \
../initializer.cpp \
../main.cpp \
../manager.cpp \
../task.cpp \
../tfile.cpp 

OBJS += \
./analyser.o \
./info.o \
./initializer.o \
./main.o \
./manager.o \
./task.o \
./tfile.o 

CPP_DEPS += \
./analyser.d \
./info.d \
./initializer.d \
./main.d \
./manager.d \
./task.d \
./tfile.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/boost -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/glib-2.0 -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


