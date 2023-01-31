### MEMO

用DFU Programmer 改變arduino （USB to  MIDI）  

cd Downloads/     
**  到”資源”所在的資料夾  

sudo dfu-programmer atmega16u2 erase  


sudo dfu-programmer atmega16u2 flash arduino_midi.hex  
sudo dfu-programmer atmega16u2 flash usbserial-atmega16u2.hex  

sudo dfu-programmer atmega16u2 reset  

