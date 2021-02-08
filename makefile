
PROJECT_NAME	= PROYECTOFINAL

##Información del micro en cuestion

DEVICE 			= atmega328p
PROGRAMMER 		= arduino 		#Esto es solo porque tenemos caragado el bootloader de la placa arduino
PORT 			= /dev/ttyUSB0	#Esto se debe verificar en cada caso en nuestro caso corriendo Manjaro siempre lo tenemos en el mismo puerto
BAUD 			= 115200 		#Baudios del puerto serial para nuestro arduino son 115200
F_CLOCK 		= 16000000

##Carpetas incluidas en el proyecto

INCLUDEPATHS 	= -I ./
INCLUDEPATHS 	+= -I ./ADC/
INCLUDEPATHS 	+= -I ./USART/
INCLUDEPATHS 	+= -I ./PWM/
INCLUDEPATHS 	+= -I ./USS/

## Objetos que seran necesarios compilar para la compilación

OBJECT_FILE 	= main.o
OBJECT_FILE 	+= ./ADC/ADC.o
OBJECT_FILE 	+= ./PWM/PWM.o
OBJECT_FILE 	+= ./USART/USART.o
OBJECT_FILE 	+= ./USS/USS.o
#OBJECT_FILE	 += "ARCHIVO CON RUTA ABSOLUTA"

## Configuración de compilador

COMPILER 		= avr-g++
CFLAGS 			= -ffunction-sections -fpermissive -std=c++11
LDFLAGS 		= -Wl,-gc-sections

## Comando basico de compilación

COMPILE 		= $(COMPILER) $(CFLAGS) -Wall -Os -DF_CPU=$(F_CLOCK) -mmcu=$(DEVICE) $(INCLUDEPATHS)

## Procesos a realizar por "make" a la hora de ejecutarse

default: compile upload clean

# "compile" se encargara de la generación del codigo maquina compatible con el micro

compile: $(PROJECT_NAME).hex

.c.o:
	$(COMPILE) -c $< -o $@

$(PROJECT_NAME).elf: $(OBJECT_FILE)
	$(COMPILE) -o $(PROJECT_NAME).elf $(OBJECT_FILE)

$(PROJECT_NAME).hex: $(PROJECT_NAME).elf
	rm -f $(PROJECT_NAME).hex
	avr-objcopy -j .text -j .data -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(PROJECT_NAME).elf

# "upload" se encaragra de quemar el codigo en el micro

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(PROJECT_NAME).hex:i 

# "clean" eliminara todos los archivos que queden del proceso de compilación

clean:
	rm $(OBJECT_FILE)
	rm *.elf
	rm *.hex