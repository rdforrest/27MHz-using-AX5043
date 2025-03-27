# 27MHz & 458MHz-using-AX5043
Preliminary routine to test out Arduino Nano connected to the AX5043.  My thanks to Jonathan (C-3PO) for all his help and to the author of:
https://www.notblackmagic.com/bitsnpieces/ax5043/
The TX is set for ON for 8 secs and OFF for 2 secs. 
7 July. Latest version PLL locks OK and transmits on 27  MHz CB radio) band. Antenna matching circuit from:
https://www.onsemi.com/forum/t/faq-how-to-operate-ax5043-at-27-mhz-custom-matching-networks-for-ax5043/274
Very puzzling but TX circuit does not transmit on full power. (Module current about 2mA, should be about 50mA from data sheet.)
Very slow progress on this project - still not sent any data or transmitted at usable power. I am still not sure that I have the hardware working properly (ax5043 connections and RF filter.) but I'm sure that an Arduino based approach is right for our r/c model submarine application. (Need for small size and low power. Raspberry Pi doesn't really fit the bill.)
To add to the problems with this project, I see that the AX5043 device is to be discontinued at the end of 2022 so I am not going to do any more development. What a waste of everyone's time!

27th March 2025.
Some good developments happening:
- It would seem that the AX5043 is not being discontinued, after all:
https://community.onsemi.com/s/article/FAQ-Is-the-AX5043-going-EOL-soon-No

- Rob Schuckman in Holland has been doing some very good development work. I have been using two of his TX and RXs in my submarines since october 2024 and they are working very well. You can see details of his work over here:
  https://robschuckman.wixsite.com/robschuckman/27mhz-remote-control
