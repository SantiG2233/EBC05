#Python 3. Hall Effect dynamic tachometer using interrupts
#Real time RPM via multiple, contingious readings
#When reading flashes LED on pin = 36, gnd=34
#Hall Effect: Sense pin = 7, VCC = 17 (3V), gnd  = 25
import time, datetime, sys      #Get sleep funtion, datetime
import RPi.GPIO as GPIO         #Get GPIO library
sense_pin = 7                   #Pin hall effect sense
LED_pin = 36                    #LED pin
GPIO.setmode(GPIO.BOARD)        #Use Raspberry Pi board pin numbers
GPIO.setup(sense_pin, GPIO.IN)  #Input from hall effect switch port
GPIO.setup(LED_pin, GPIO.OUT)   #LED on/off port
last_time = time.time()         #Initilaize
this_time = time.time()         #Initialize
RPM = 0                         #Initialize

#FUNCTION 'add_event_detect' RUNS AT INPUT CHANGE
def EventsPerTime(channel):
    global RPM, this_time, last_time
    GPIO.output(LED_pin, True)  #LED on
    this_time = time.time()     #Get current real time
    RPM = (1/(this_time - last_time))*60 #revs/mins real time diff
    print('Current RPM = ','{:7.1f}'.format(RPM)) #Instantaneous RPMs (not avg)
    last_time = this_time       #Store current time for next measurement
                                #Requires multiple; contigious interrupts
    GPIO.output(LED_pin,False)
    return()

#INTERRUPT: On input change, run EventsPerTime function
GPIO.add_event_detect(sense_pin, GPIO.RISING, callback=EventsPerTime, bouncetime=1)

#MAIN ROUTINE
timedate = datetime.datetime.now().strftime('%H:%M %Y%m%d %a')
print('System Active @', timedate)
print('Ctrl C to quit')         #Message to use control c to quit
try:
    for x in range(0,1200):     #Loop x times
        #print('Last RPM = ','{:7.1f}'.format(RPM)) #Last RPM, end='' no LF
        time.sleep(0.5)         #Time delay before looping
except:
    time.sleep(2)               #Allow settling before quitting
    GPIO.output(ÑED_pin, False) #Turn off ligth when finished
    GPIO.remove_event_detect(sense_pin) #Turn off event detect interrupt
    GPIO.celanup()              #Reset ports
    print('done')               #Normal finish, print 'Done'

