################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Client.cpp \
../ClientMain.cpp \
../ClientModel.cpp \
../ClientToJavaMain.cpp \
../protocol.cpp \
../sendToJava.cpp 

OBJS += \
./Client.o \
./ClientMain.o \
./ClientModel.o \
./ClientToJavaMain.o \
./protocol.o \
./sendToJava.o 

CPP_DEPS += \
./Client.d \
./ClientMain.d \
./ClientModel.d \
./ClientToJavaMain.d \
./protocol.d \
./sendToJava.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


