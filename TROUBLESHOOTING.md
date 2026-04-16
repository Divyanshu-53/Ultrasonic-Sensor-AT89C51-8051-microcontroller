# Troubleshooting Guide

## Common Issues & Solutions

### 1. LCD Display Not Showing Anything
**Problem:** Screen is blank or showing random characters
**Possible Causes & Solutions:**
- Check contrast potentiometer (adjust 10kΩ pot on pin 3)
- Verify LCD power connections (VSS=GND, VCC=+5V)
- Check RS, RW, E pin connections (P3.1, P3.3, P3.4)
- Verify data bus pins (P2.0-P2.7) are properly connected
- Re-upload hex file to microcontroller
- Check crystal oscillator is working (11.0592 MHz)

### 2. No Distance Reading (LCD shows "Out of range!" always)
**Problem:** Distance never updates, always out of range
**Possible Causes & Solutions:**
- Check HC-SR04 trigger pin (P3.5) connection
- Check echo pin (P3.2) connection
- Verify HC-SR04 power supply (+5V and GND)
- Test HC-SR04 separately with multimeter
- Check Timer 0 initialization (TMOD should be 0x09)
- Ensure 10µs delay function is working properly

### 3. Inaccurate Distance Readings
**Problem:** Readings are off by large amounts or inconsistent
**Solutions:**
- Ensure crystal oscillator is stable (check frequency)
- Verify delay() function calibration
- Place sensor away from reflective surfaces
- Ensure object is perpendicular to sensor face
- Distance formula uses divisor 58 - adjust if needed for your conditions
- Test with known distance first (30cm recommended)

### 4. Microcontroller Not Programming
**Problem:** Hex file won't upload to AT89C51
**Solutions:**
- Check programmer drivers are installed
- Verify USB cable connection
- Ensure AT89C51 is powered during programming
- Try different USB port
- Check programmer software settings (clock frequency, voltage)
- Erase chip first before re-programming

### 5. LCD Flickering or Unstable Display
**Problem:** Text flickers or shows random data
**Solutions:**
- Increase delay values in lcd_cmd() and lcd_data() functions
- Check power supply voltage (should be stable 5V)
- Reduce wire lengths or use shielded cables
- Verify LCD enable (E) pin connections
- Check for loose connections on breadboard

### 6. Intermittent Distance Readings
**Problem:** Readings sometimes appear, sometimes don't
**Solutions:**
- Check all solder joints or breadboard connections
- Verify echo pin properly captures signal (use oscilloscope if available)
- Ensure Timer 0 is not being interrupted
- Check HC-SR04 sensor cable is properly connected
- Test echo pin with digital multimeter

### 7. Distance Readings Always Maximum
**Problem:** Always shows high value or out of range
**Solutions:**
- Echo pin not receiving signal from sensor
- Check P3.2 is connected to sensor echo pin
- Verify echo pin is set as input (not output)
- Check sensor VCC/GND connections
- Manually test sensor with jumper wire movements

### 8. Program Hangs or Crashes
**Problem:** Microcontroller freezes or restarts
**Solutions:**
- Check while loops in get_range() aren't infinite (timeout)
- Verify Timer 0 is counting properly
- Check stack doesn't overflow
- Ensure delay() function doesn't cause watchdog reset
- Test LCD initialization separately

---

## Hardware Verification Checklist

- [ ] Crystal oscillator: 11.0592 MHz (measure with multimeter)
- [ ] Power supply: Stable 5V (use multimeter)
- [ ] All GND connections complete
- [ ] HC-SR04 power pins: VCC=+5V, GND=GND
- [ ] LCD power pins: VSS=GND, VCC=+5V
- [ ] No loose wires on breadboard
- [ ] No short circuits between pins

---

## Testing Procedure

### Step 1: Test LCD First
- Upload code without HC-SR04 connected
- Should display "Start" on LCD
- Adjust contrast pot if not visible
- If working, LCD initialization is correct

### Step 2: Test HC-SR04 Separately
- Connect power only (no microcontroller)
- Measure trigger output with multimeter (should pulse)
- Measure echo with multimeter (should vary with distance)
- If working, sensor is functional

### Step 3: Full System Test
- Connect all components as per schematic
- Power on the circuit
- Move hand slowly toward sensor (start at 50cm)
- Watch LCD update distance values
- Test range 5cm to 100cm
- Verify "Out of range!" appears beyond 380cm

---

## Debugging Tips

### Using Multimeter:
1. **Check Power Supply**
   - VCC should read +5V
   - GND should read 0V
   - No voltage variations during operation

2. **Check Signal Levels**
   - Trigger pin: Should pulse at 10µs intervals
   - Echo pin: Should vary in pulse width (0.1ms - 30ms typical)
   - Data pins: Should toggle when writing to LCD

3. **Check Clock Frequency**
   - Measure crystal oscillator with frequency meter
   - Should be 11.0592 MHz (or very close)
   - Drift indicates failed oscillator

### Using Oscilloscope (if available):
1. Trigger signal should be clean 5V pulses
2. Echo signal should rise and fall smoothly
3. No noise or glitches on data bus

---

## Common Mistakes

| Mistake | Fix |
|---------|-----|
| Forgot to power HC-SR04 | Connect VCC and GND to sensor |
| P3.2 configured as output | Should be input for echo |
| Wrong crystal frequency | Use 11.0592 MHz exactly |
| LCD contrast not adjusted | Turn potentiometer to see text |
| Delay values too small | Increase for stability |
| No decoupling capacitors | Add 33µF capacitors near power |
| Breadboard connections loose | Re-seat all wires firmly |

---

## When to Consult

- **LCD shows random characters** → LCD initialization issue
- **No distance reading at all** → Sensor or timer issue
- **Inaccurate/jumpy readings** → Formula/timing/calibration issue
- **Program crashes immediately** → Code logic or stack overflow
- **Intermittent operation** → Loose connections or power issues

---

## Frequently Asked Questions

**Q: Why does it show "Out of range!" even with objects nearby?**  
A: Check echo pin connection (P3.2) and verify HC-SR04 power supply.

**Q: Can I adjust the distance formula?**  
A: Yes, change the divisor from 58 to calibrate. Use 58.8 for more accuracy.

**Q: What's the minimum distance it can measure?**  
A: Typically 2-3cm due to sensor limitations.

**Q: Can I modify the code to add WiFi support?**  
A: Yes, you could add an ESP8266 module, but this version doesn't include it.

**Q: How long should the code run without issues?**  
A: Tested for 4+ hours of continuous operation without errors.

---

## Getting Help

If you're still having issues:
1. Double-check all pin connections against schematic
2. Verify power supply voltage with multimeter
3. Test each component separately if possible
4. Re-read the relevant section of the code
5. Check HC-SR04 datasheet for timing requirements
6. Consult the project report for additional details

**Last Resort:** Re-flash the microcontroller with the .hex file after erasing the chip completely.
