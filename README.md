# 27MHz & 458MHz-using-AX5043
Preliminary routine to test out Arduino Nanos connected to the AX5043. No data has been sent yet from TX to RX. My thanks to Jonathan (C-3PO) for all his help and to the author of:
https://www.notblackmagic.com/bitsnpieces/ax5043/
The hardware has been tried on 27 Mhz. It transmits, but no PLL lock yet. Tweaking output circuit?
27 June. The TX is set for ON for 8 secs and OFF for 2 secs but still some basic problems with frequency changing and no lock with 27 MHz so continuing development on 458 MHz.
30 June Latest version PLL locks OK and transmits on 27  MHz CB radio) band. (Antenna matching circuit from:
https://www.onsemi.com/forum/t/faq-how-to-operate-ax5043-at-27-mhz-custom-matching-networks-for-ax5043/274
