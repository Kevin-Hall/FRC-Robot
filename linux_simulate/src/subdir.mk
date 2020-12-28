################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LEDLights.cpp \
../src/Launcher.cpp \
../src/Robot.cpp \
../src/Tankdrive.cpp \
../src/Ultrasonic.cpp \
../src/Vision.cpp \
../src/constants.cpp 

OBJS += \
./src/LEDLights.o \
./src/Launcher.o \
./src/Robot.o \
./src/Tankdrive.o \
./src/Ultrasonic.o \
./src/Vision.o \
./src/constants.o 

CPP_DEPS += \
./src/LEDLights.d \
./src/Launcher.d \
./src/Robot.d \
./src/Tankdrive.d \
./src/Ultrasonic.d \
./src/Vision.d \
./src/constants.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\IBM_ADMIN\workspace\2016 Tank Drive Basic 3.0/src" -IC:\Users\IBM_ADMIN/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


