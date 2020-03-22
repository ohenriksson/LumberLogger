```
R1: known resistor
R2: wood
U1: range[0, 5]
U2: range[0, 3.3]

Utot = u1 + u2 = 5.0v
Rtot = R1 + R2
Itot = I1 = I2

R1 = R2 * u1/u2
R2 = R1 * u2/u1

R1A: 3.3M [decided]
Wood resistance(R2) at 0.1V: -> R2 = 3.3M * 0.1/(5-0.1) = 0.067M
Wood resistance(R2) at 3.0V: -> R2 = 3.3M * 3.0/(5-3) = 4.95M

R1B: 220M [decided]
Wood resistance(R2) at 0.1V: -> R2 = 220M * 0.1/(5-0.1) = 4.49M
Wood resistance(R2) at 3.0V: -> R2 = 220M * 3.0/(5-3) = 330M
```

