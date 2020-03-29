```
R1: known resistor
R2: wood
U1: range[0, 3.3]
U2: range[0, 3.3]

Utot = u1 + u2 = 3.3v
Rtot = R1 + R2
Itot = I1 = I2

R1 = R2 * u1/u2
R2 = R1 * u2/u1

R1A: 3.3M [decided]
Wood resistance(R2) at 0.1V: -> R2 = 3.3M * 0.1/(3.3-0.1) = 0.103M
Wood resistance(R2) at 3.0V: -> R2 = 3.3M * 3.0/(3.3-3.0) = 33M

R1B: 220M [decided]
Wood resistance(R2) at 0.1V: -> R2 = 220M * 0.1/(3.3-0.1) = 6.875M
Wood resistance(R2) at 3.0V: -> R2 = 220M * 3.0/(3.3-3.0) = 2200M
```

