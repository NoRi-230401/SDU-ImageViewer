#include <M5Unified.h>
#include "ImageViewer.hpp"
#include "menu.hpp"
#include "util.hpp"

ImageViewer viewer;

void setup(void)
{
    MODE_ST = MODE_M1;

    auto cfg = M5.config();
    M5.begin(cfg);
    sdu_lobby();

    disp_init();
    M5.Display.setTextScroll(true);
    delay(500);

    if (!viewer.begin())
        FOREVER_LOOP();

    MODE_ST = MODE00;
}

void loop(void)
{
    if (MODE_ST == MODE00)
    {
        M5.update();

        if (!M5.BtnB.wasHold())
        {
            viewer.update();
            delay(10);
        }
        else
        {
            prtln("BtnB was Hold, go to SETTING MENU", D1_SERI);
            MODE_ST = MENU01;    // SETTIN MENU mode first
            disp_init();
            setup_menu(MENU01);
            delay(500);
        }
    }
    else
    {
        loop_menu();            // loop for SETTING MENU
    }
}
