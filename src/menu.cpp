#include <M5Unified.h>
#include "menu.hpp"
#include "util.hpp"
#include "ImageViewer.hpp"
extern ImageViewer viewer;
void menuPrt(String msg, int lineNo);

// --　ここから個別のアプリ毎に対応必要 -------------------------------------
static void fn01_AUTOMODE_OFF()
{
  prtln("AutoMode set OFF", D1_SERI);
  viewer.setAutoMode(AUTOMODE_OFF);
  menuPrt("AutoMode", 2);
  menuPrt(" -> off", 3);
  delay(100);
}

static void fn01_AUTOMODE_FORWARD()
{
  prtln("AutoMode set FORWARD", D1_SERI);
  viewer.setAutoMode(AUTOMODE_FORWARD);
  menuPrt("AutoMode", 2);
  menuPrt(" -> forward", 3);
  delay(100);
}

static void fn01_AUTOMODE_BACKWARD()
{
  prtln("AutoMode set BACKWARD", D1_SERI);
  viewer.setAutoMode(AUTOMODE_BACKRWARD);
  menuPrt("AutoMode", 2);
  menuPrt(" -> backward", 3);
  delay(100);
}

static void fn01_AUTOMODE_RND()
{
  prtln("AutoMode set RND", D1_SERI);
  viewer.setAutoMode(AUTOMODE_RND);
  menuPrt("AutoMode", 2);
  menuPrt("-> random", 3);
  delay(100);
}

static void fn02_intval_01()
{
  prtln("Interval 3sec", D1_SERI);
  menuPrt("Interval", 2);
  menuPrt("  -> 3sec", 3);
  viewer.setIntval(3000);
  delay(100);
}

static void fn02_intval_02()
{
  prtln("Interval 5sec", D1_SERI);
  menuPrt("Interval", 2);
  menuPrt("  -> 5sec", 3);
  viewer.setIntval(5000);
  delay(100);
}

static void fn02_intval_03()
{
  prtln("Interval 10sec", D1_SERI);
  menuPrt("Interval", 2);
  menuPrt("  -> 10sec", 3);
  viewer.setIntval(10000);
  delay(100);
}

static void fn03_intvalRnd_off()
{
  prtln("Interval Rnd Off", D1_SERI);
  menuPrt("Interval Rnd", 2);
  menuPrt("  -> off", 3);
  viewer.setIntvalRnd(false);
  delay(100);
}

static void fn03_intvalRnd_on()
{
  prtln("Interval Rnd On", D1_SERI);
  menuPrt("Interval Rnd", 2);
  menuPrt("  -> on", 3);
  viewer.setIntvalRnd(true);
  delay(100);
}

static void fn04_SDU_menu()
{
  prtln("Will Load SD-Updater menu.bin", D1_SERI);
  menuPrt(" Load menu.bin", 2);
  delay(3000);
  disp_init();
  delay(100);
  loadMenu();
  FOREVER_LOOP();
}

static void fn05_SDU_saveBin()
{
  prtln("Will Save bin_file to SD", D1_SERI);
  menuPrt(" Save bin to SD", 2);
  delay(3000);
  disp_init();
  delay(100);
  saveBin();
  delay(100);
  disp_init();
  delay(100);
  setup_menu(MENU05);
  delay(100);
}

static void fn06_PowerOff()
{
  prtln("PowerOff", D1_SERI);
  menuPrt(" Power Off", 2);
  delay(3000);
  M5.Power.powerOff();
  FOREVER_LOOP;
}

/// メニュー定義： btn(1-4個まで)名前と処理関数
static const menu_item menu01[] = {
    {"off", fn01_AUTOMODE_OFF},
    {"forward", fn01_AUTOMODE_FORWARD},
    {"backward", fn01_AUTOMODE_BACKWARD},
    {"random", fn01_AUTOMODE_RND},
};
static const menu_item menu02[] = {
    {"3sec", fn02_intval_01},
    {"5sec", fn02_intval_02},
    {"10sec", fn02_intval_03},
};
static const menu_item menu03[] = {
    {"off", fn03_intvalRnd_off},
    {"on", fn03_intvalRnd_on},
};
static const menu_item menu04[] = {
    {"SDU-menu", fn04_SDU_menu},
};
static const menu_item menu05[] = {
    {"SaveBin", fn05_SDU_saveBin},
};
static const menu_item menu06[] = {
    {"PowerOff", fn06_PowerOff},
};
/// 要素数
static constexpr const size_t btn01Len = sizeof(menu01) / sizeof(menu01[0]);
static constexpr const size_t btn02Len = sizeof(menu02) / sizeof(menu02[0]);
static constexpr const size_t btn03Len = sizeof(menu03) / sizeof(menu03[0]);
static constexpr const size_t btn04Len = sizeof(menu04) / sizeof(menu04[0]);
static constexpr const size_t btn05Len = sizeof(menu05) / sizeof(menu05[0]);
static constexpr const size_t btn06Len = sizeof(menu06) / sizeof(menu06[0]);

static constexpr const size_t BTN_LEN[] = {btn01Len, btn02Len, btn03Len, btn04Len, btn05Len, btn06Len};
static const menu_item *MENU[] = {menu01, menu02, menu03, menu04, menu05, menu06};

// 画面の最上位行に表示するメッセージ作成
String getMenu_msg(int mode)
{
  String msg = "";
  const String AUTOMODE[4] = {"off", "forward", "backward", "random"};

  switch (mode)
  {
  case MENU01:
    msg = "AutoMode : " + AUTOMODE[viewer.getAutoMode()];
    break;

  case MENU02:
    msg = "AutoMode Interval : " + String(viewer.getIntval() / 1000, 10) + "sec";
    break;

  case MENU03:
    if (viewer.getIntvalRnd())
      msg = "AutoMode Interval Rnd : on";
    else
      msg = "AutoMode Interval Rnd : off";
    break;

  case MENU04:
    msg = "Load SD-Updater menu.bin";
    break;

  case MENU05:
    msg = "Save bin-file to SD";
    break;

  case MENU06:
    msg = "Power Off";
    break;

  default:
    break;
  }

  return msg;
}

// exitして、MODE00に戻ったときの表示
void MODE00_disp()
{
  M5.Display.setTextScroll(true);
  M5.Display.printf("****   SDU-imageViewer   ****\n\n\n");
  M5.Display.printf("(BtnA)click: backward image\n\n");
  M5.Display.printf("(BtnB) hold: setting menu\n\n");
  M5.Display.printf("(BtnC)click: forward image\n");
}
// --　ここまで個別のアプリ毎に対応必要 -------------------------------------

void menuPrt(String msg, int lineNo)
{ // prt msg for right-area of menu (lineNo : 0 to 7)
  if (lineNo < 0 || lineNo > 7)
    return;

  int32_t SX = 170;
  int32_t SY = (lineNo + 1) * 25;

  M5.Display.setTextScroll(false);
  M5.Display.setTextDatum(0);

  // SPACE for cleanning
  M5.Display.setCursor(SX, SY);
  M5.Display.print("                        ");

  M5.Display.setCursor(SX, SY);
  M5.Display.print(msg.c_str());
}

void setup_menu(int mode);
void loop_menu();
void disp_init();
void draw_menu(size_t index, bool focus);
void select_menu(size_t index);
void exec_menu(int modeNo, size_t fnIndex);
void M5Disp(String msg, int32_t x, int32_t y);

static size_t btn_len = BTN_LEN[0]; // ボタン個数
size_t cursor_index = 0;            // 現在カーソルのあるボタン位置
int MODE_ST = MODE_M2;              // mode status = init
static int menu_x;
static int menu_y;
static int menu_w;
static int menu_h;
static int menu_padding;

void draw_menu(size_t index, bool focus)
{
  auto baseColor = M5.Display.getBaseColor();
  M5.Display.setColor(focus ? baseColor : ~baseColor);

  // ボタン外枠
  M5.Display.drawRect(menu_x, menu_y + index * menu_padding, menu_w, menu_h);
  M5.Display.drawRect(menu_x + 1, menu_y + index * menu_padding + 1, menu_w - 2, menu_h - 2);

  // ボタン内側
  M5.Display.setColor(focus ? ~baseColor : baseColor);
  M5.Display.fillRect(menu_x + 2, menu_y + index * menu_padding + 2, menu_w - 4, menu_h - 4);

  // 中心にボタン名前
  M5.Display.setTextDatum(textdatum_t::middle_center);
  M5.Display.setTextColor(focus ? baseColor : ~baseColor, focus ? ~baseColor : baseColor);
  M5.Display.drawString(
      MENU[MODE_ST - 1][index].btnName,
      menu_x + (menu_w >> 1),
      menu_y + index * menu_padding + (menu_h >> 1));
}

void select_menu(size_t index)
{
  /// 操作音を鳴らす。
  float Hz = 880 * powf(2.0, index / 12.0f);
  // M5.Speaker.tone(Hz, 100);
  cursor_index = index;
}

void exec_menu(int modeNo, size_t fnIndex)
{
  // menuNo MENU01 to MENU_END
  if (modeNo < MENU01 || modeNo > MENU_END)
    return;

  if (MENU[modeNo - 1][fnIndex].func != nullptr)
  {
    MENU[modeNo - 1][fnIndex].func();
  }
}

void disp_init()
{
  M5.Display.endWrite();
  M5.Display.fillScreen(TFT_BLACK); // 画面クリア
  M5.Display.setRotation(1);
  M5.Display.setTextSize(1.0);
  M5.Display.setFont(&fonts::DejaVu18);          // フォントセット
  M5.Display.setTextColor(TFT_WHITE, TFT_BLACK); // 描画色、背景色を設定。
  M5.Display.setTextDatum(0);
  M5.Display.setCursor(0, 0); // カーソルセット
  M5.Display.setTextScroll(false);
  M5.Display.setTextWrap(false); // テキスト自動折返し
}

void setup_menu(int mode)
{
  const int M_PADDING[4] = {70, 60, 50, 48};
  const int M_H[4] = {60, 50, 40, 40};
  const int M_Y[4] = {70, 60, 50, 25};
  String msg = "";
  M5.Display.fillScreen(TFT_BLACK);

  cursor_index = 0;

  btn_len = BTN_LEN[mode - 1];
  prtln("btn_len = " + String(btn_len, 10), D1_SERI);

  menu_x = 0;
  menu_y = M_Y[btn_len - 1];
  menu_w = M5.Display.width() >> 1;
  menu_h = M_H[btn_len - 1];
  menu_padding = M_PADDING[btn_len - 1];
  prtln("mode = " + String(mode, 10), D1_SERI);
  prtln("btn_len = " + String(btn_len, 10), D1_SERI);
  prtln("menu_x = " + String(menu_x, 10), D1_SERI);
  prtln("menu_y = " + String(menu_y, 10), D1_SERI);
  prtln("menu_w = " + String(menu_w, 10), D1_SERI);
  prtln("menu_h = " + String(menu_h, 10), D1_SERI);
  prtln("menu_padding = " + String(menu_padding, 10), D1_SERI);

  msg = getMenu_msg(mode);
  M5Disp(msg, 0, 0);

  msg = "     prev         exit         next";
  M5Disp(msg, 0, M5.Display.height() - 20);

  msg = "  MENU  " + String(mode, 10) + " / " + String(MENU_END, 10);
  menuPrt(msg, 0);

  for (size_t i = 0; i < btn_len; i++)
  {
    draw_menu(i, false);
  }
}

void loop_menu()
{
  { /// 10ミリ秒間隔で処理が進むように待機する。
    static uint32_t prev_ms;
    uint32_t ms = M5.millis();
    int diff = (10 - (ms - prev_ms));
    if (diff > 0)
    {
      ms += diff;
      M5.delay(diff);
    }
    prev_ms = ms;
  }

  M5.update();

  auto touch_count = M5.Touch.getCount();
  for (size_t i = 0; i < touch_count; i++)
  {
    auto detail = M5.Touch.getDetail(i);
    if (((size_t)detail.x - menu_x) < menu_w)
    {
      size_t index = (detail.y - menu_y) / menu_padding;
      // if (index < btn_len)
      if (index >= 0 && index < btn_len)
      {
        if (detail.wasPressed())
        {
          select_menu(index);
          ;
        }
        else if (index == cursor_index)
        {
          if (detail.wasClicked())
          {
            exec_menu(MODE_ST, index);
          }
        }
      }
    }
  }

  if (M5.BtnA.wasClicked())
  {
    prtln("BtnA Cliked! [prev]", D1_SERI);
    MODE_ST--;
    if (MODE_ST < MENU01)
      MODE_ST = MENU_END;

    disp_init();
    setup_menu(MODE_ST);
    delay(500);
  }
  else if (M5.BtnC.wasClicked())
  {
    prtln("BtnC Cliked!  [next]", D1_SERI);
    MODE_ST++;
    if (MODE_ST > MENU_END)
      MODE_ST = MENU01;

    disp_init();
    setup_menu(MODE_ST);
    delay(500);
  }
  else if (M5.BtnB.wasClicked())
  {
    prtln("BtnB Cliked!  [exit]", D1_SERI);
    MODE_ST = MODE00;
    disp_init();
    MODE00_disp();
    delay(500);
  }
}

void M5Disp(String msg, int32_t x, int32_t y)
{
  M5.Display.setTextScroll(false);
  M5.Display.setTextDatum(0);
  M5.Display.setCursor(x, y);
  // SPACE for cleanning
  M5.Display.print("                                  ");
  ;
  M5.Display.setCursor(x, y);
  M5.Display.print(msg.c_str());
}
