# HoloControl
HoloLens input device based on Wii Nunchuk controller.
- Adds two buttons and joystick functionality
- Wireless connection over Bluetooth
- Low latency, reaction time < 1/20 second
- Easy to use in Unity, no external depenencies

## Demo

[![Alt text](https://img.youtube.com/vi/75GZE48Ib2U/0.jpg)](https://www.youtube.com/watch?v=75GZE48Ib2U)

## How it works

![Hardware overview](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/overview.png)

- Arduino board reads button state from nunchuk over I2C protocol.
- Arduno translates key press events in HID codes and sends them to EZ-Key board over serial interface.
- Bluefruit EZ-Key board appears like an external keyboard in the list of available Bluetooth devices on the HoloLens.
- Standard Bluetooth pairing, no PIN required. If something goes wrong there is Pair button on the EZ-Key board to restart the connection.
- For Unity scripts the HoloControler looks like normal key press events comming from a keyboard.


First prototype

[<img src="https://raw.githubusercontent.com/cazacov/HoloControl/master/img/Prototype.png" alt="Prototype" width="480" height="320"/>](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/Prototype.png "Prototype")


## Hardware


### Parts list
| Part | Price in EU | Comment |
| --- | --- | --- |
| Wii Nunchuk | 10 € | Got one in perfect condition on Ebay |
| Arduino Mini 3.3V/8MHz | 9.50 € | Reads data from the Nunchuk |
| Bluefruit EZ-Key | 21 € | Bluetooth HID Keyboard Controller |

You will also need FTDI cable to program Arduino Mini. It's also possible to [use regular Arduino as programmer](https://www.arduino.cc/en/Guide/ArduinoMini).

### Wiring

Wired version

[<img src="https://raw.githubusercontent.com/cazacov/HoloControl/master/img/circuit.png" alt="Circuit diagram" />](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/circuit.png "Circuit diagram")


Arduino stacked on the top of EZ-Key board. I put a piece of plastic between boards for electrical isolation.

[<img src="https://raw.githubusercontent.com/cazacov/HoloControl/master/img/sandwich.png" alt="Boards" width="460" height="320"/>](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/sandwich.png "Boards")

Nunchuk board pinout.

[<img src="https://raw.githubusercontent.com/cazacov/HoloControl/master/img/nunchuck_pinout.png" alt="Nunchuk board" width="460" height="320"/>](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/nunchuck_pinout.png "Nunchuk board")


Electronics nicely fits into original nunchuk case.

[<img src="https://raw.githubusercontent.com/cazacov/HoloControl/master/img/assembled.png" alt="Assembled controller" width="460" height="200"/>](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/assembled.png "Assembled controller")


## Firmware

Arduino sources are in the "Arduino" folder.

The easiest way to program Arduino Mini is using FTDI cable. It's also possible to use USB<->Serial adapter or Arduino UNO as programming device.

Be sure to choose correct board type in the Arduino IDE

[<img src="https://raw.githubusercontent.com/cazacov/HoloControl/master/img/Arduino_IDE_settings.png" alt="Arduino IDE settings" width="695" height="320"/>](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/Arduino_IDE_settings.png "Arduino IDE settings")


## Using in Unity

The controller simulates keys strokes on a Bluetooth keybord. Jostick directions are translated in A, D, W, S keys. Z button is mapped to Return and C button to Escape. 

You can get key state with the standard UnityEngine.Input class:

```csharp
if (UnityEngine.Input.GetKey(KeyCode.A))
{
	// Joystick left
	...
}

if (UnityEngine.Input.GetKey(KeyCode.D))
{
	// Joystick right
	...
}
```



## Wired version
Still needs cable for power supply (USB plug A).

[<img src="https://raw.githubusercontent.com/cazacov/HoloControl/master/img/wired_version.png" alt="HoloController" width="460" height="320"/>](https://raw.githubusercontent.com/cazacov/HoloControl/master/img/wired_version.png "HoloController")


## Wireless version

Adds LiPo accumulator and charging controller.

Coming soon.
