from machine import ADC,Pin
import utime

adc_light = ADC(Pin(28))

while True:
    light_value = adc_light.read_u16()
    print(light_value)
    utime.sleep_ms(500)