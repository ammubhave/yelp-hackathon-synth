import pygame.midi
import os
import serial

pygame.midi.init()

id = 3
print pygame.midi.get_device_info(id)

inp = pygame.midi.Input(id)
ser = serial.Serial('/dev/ttyACM1', 115200, timeout=1)

lk = -1
try:
    while (True):
        while (not inp.poll()):
            if ser.inWaiting() > 0:
                print "ARD: " + ser.read(ser.inWaiting())
        event = inp.read(1)
        if event[0][0][0] == 128:
            if event[0][0][1] == lk:
                ser.write("\xFF")
        else:
            if event[0][0][1] >= 55 and event[0][0][1] <= 81:
                ser.write(chr(event[0][0][1] - 55))
                lk = event[0][0][1]
        ser.flush()
        print event

except Exception, ex:
    print ex
inp.close()
ser.close()
