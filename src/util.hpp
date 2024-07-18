#ifndef _UTIL_HPP_
#define _UTIL_HPP_

// print direction for prt() and prtln()
#define D1_SERI   1    // serial
#define D2_DISP   2    // display
#define D3_BOTH   3    // both

extern void sdu_lobby();
extern void loadMenu(void);
extern void saveBin(void);
extern bool SdBegin();
extern void prt(String sData, int direction = D3_BOTH);
extern void prtln(String sData, int direction = D3_BOTH);
extern void POWER_OFF();
extern void REBOOT();
extern void FOREVER_LOOP();

// ----------------------------------------------------------------------------

#endif //_UTIL_HPP_
