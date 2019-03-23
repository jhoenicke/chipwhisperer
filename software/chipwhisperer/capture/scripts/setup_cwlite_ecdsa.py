"""Setup script for CWLite/1200 with TREZOR (STM32F target)

Configures scope settings to prepare for capturing SimpleSerial power traces
"""


import chipwhisperer as cw

scope = cw.scope()
self.scope = scope

target = cw.target(scope)
self.target = target
    
scope.gain.gain = 45
scope.adc.samples = 5000
scope.adc.offset = 0
scope.adc.basic_mode = "rising_edge"
scope.clock.clkgen_freq = 30000000
scope.clock.adc_src = "clkgen_x4"
scope.trigger.triggers = "tio4"
scope.io.tio1 = "serial_rx"
scope.io.tio2 = "serial_tx"
scope.io.hs2 = "clkgen"

target.baud=38400
target.setKeyLen(32)
target.setTextLen(32)
target.setOutputLen(32)

#The following shows the "old" method of accessing elements where the new API
#is not yet ready.
self.api.setParameter(['Generic Settings', 'Basic', 'Fixed Encryption Key', u'2B 7E 15 16 28 AE D2 A6 AB F7 15 88 09 CF 4F 3C 2B 7E 15 16 28 AE D2 A6 AB F7 15 88 09 CF 4F 3C'])
self.api.setParameter(['Target Settings', 'Simple Serial', 'proto', 'timeout', 2000])
self.api.setParameter(['OpenADC', 'Trigger Setup', 'Total Samples', 24400])

