# arduino_rw1990 

Read and flash RW1990 keys using arduino.

RW1990 aka RW-1990. Most likely RW-1990.1, ТМ-08, ТМ-08v2 will be working.

### It should be something about 'PCB'

You will need:
* Resistor 2.2k
* Arduino Nano. Or not Nano, Uno is also good. Or you can pick some Arduino-compatible board.
* Wires x3

Long story short: pull PIN 10 over capacitor to VCC. Plug this pin to the center of the iButton key. Key 'borders' should be connected to the ground.

Just take a look on [what_is_it_should_be_look_like.jpg](what_is_it_should_be_look_like.jpg)

### HOWTO 

To ***read key*** just flash snipped as is.

To ***write key*** you need do next steps:

1. Set `key_to_write` to key you want to write.
2. Find in code '// UNCOMMENT THIS SECTION FOR FLASHING KEY' section and uncomment this section.
3. Flash. Check. Get satisfied.

### Example

Read:
```
.........
[1:F0:88:12:1:0:0:2E]

[1:F0:88:12:1:0:0:2E]

[1:F0:88:12:1:0:0:2E]

[1:F0:88:12:1:0:0:2E]
..................................
```

Write:

```
..
[1:F0:88:12:1:0:0:2E]
++++++++
[1:5F:69:B:1:0:0:EA]

[1:5F:69:B:1:0:0:EA]
 programmed to KEY requested
[1:5F:69:B:1:0:0:EA]
 programmed to KEY requested.....
```

### References:

Uses some code, ideas, information, inspiration taken from:
* https://github.com/AlexMalov/EasyKeyDublicator/
* https://habr.com/ru/post/237487/

### License

Since I didn't find any license info in projects used please consider this as WTFPL app.