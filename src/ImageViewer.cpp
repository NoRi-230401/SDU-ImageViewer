#include "ImageViewer.hpp"
#include "menu.hpp"
#include "util.hpp"
#include <Arduino_JSON.h>
#include <string.h>

const char *ImageViewer::VERSION = "v101";
const char *ImageViewer::DEFAULT_CONFIG_NAME = "/app/imgView/imgView.json";
String ImageViewer::DATA_DIR("/Pictures");
const char *ImageViewer::KEY_DATA_DIR = "DataDir";
const char *ImageViewer::KEY_AUTO_MODE = "AutoMode";
const char *ImageViewer::KEY_AUTO_MODE_INTERVAL = "AutoModeInterval";
const char *ImageViewer::KEY_AUTO_MODE_INTVAL_RND = "AutoModeRandomized";
static const char *EXT_JPG = ".jpg";
static const char *EXT_JPEG = ".jpeg";
static const char *EXT_BMP = ".bmp";
static const char *EXT_PNG = ".png";
static int32_t getDirection(void);

ImageViewer::ImageViewer(uint8_t isAutoMode, uint32_t autoModeInterval, bool isAutoModeIntvalRnd)
    : _isAutoMode(isAutoMode),
      _autoModeInterval(autoModeInterval),
      _isAutoModeIntvalRnd(isAutoModeIntvalRnd),
      _imageFiles{""},
      _nImageFiles(0),
      _pos(0),
      _prevUpdate(0),
      _interval(autoModeInterval)
{
    randomSeed(analogRead(0));
}

ImageViewer::~ImageViewer(void)
{
}

bool ImageViewer::begin(int bgColor)
{

    this->_orientation = M5.Lcd.getRotation();
    M5.Lcd.setRotation(this->_orientation);

    if (!SdBegin())
    {
        prtln("Failed to mount SD File System");
        return false;
    }

    M5.Lcd.setFileStorage(IV_FS);

    String msg = "Image Viewer " + String(VERSION);
    prtln(msg);

    if (!parse())
    {
        return false;
    }

    delay(DEFAULT_START_INTERVAL_MS);
    if (!setImageFileList())
    {
        return false;
    }

    M5.Lcd.clearScrollRect();
    M5.Lcd.setCursor(0, 0);

    delay(DEFAULT_START_INTERVAL_MS);
    M5.Lcd.clear();
    M5.Lcd.fillScreen(bgColor);

    if (this->_isAutoMode == AUTOMODE_OFF)
    {
        showImage(this->_imageFiles, this->_pos);
    }

    return true;
}

bool ImageViewer::update(void)
{
    const uint32_t t = millis();
    int32_t direction = getDirection();
    size_t imgPos = this->_pos;
    size_t imgLen = this->_nImageFiles;
    uint8_t AUTO_MODE = this->_isAutoMode;
    bool INTVAL_RND = this->_isAutoModeIntvalRnd;

    if (AUTO_MODE == AUTOMODE_OFF)
    {
        switch (direction)
        {
        case 1:
            if (imgPos >= imgLen - 1)
                imgPos = 0;
            else
                imgPos++;
            break;

        case -1:
            if (imgPos <= 0)
                imgPos = imgLen - 1;
            else
                imgPos--;
            break;

        default:
            return false;
        }
        this->_pos = imgPos;
        showImage(this->_imageFiles, this->_pos);

        prtln("t = " + String(t, 10), D1_SERI);
        prtln("direction = " + String(direction, 10), D1_SERI);
        prtln("imgPos = " + String(imgPos, 10), D1_SERI);
        prtln("imgLen = " + String(imgLen, 10), D1_SERI);
        prtln("AUTO_MODE = " + String(AUTO_MODE, 10), D1_SERI);
        prtln("prvUpdate = " + String(this->_prevUpdate, 10), D1_SERI);
        prtln("interval  = " + String(this->_interval, 10), D1_SERI);
        return true;
    }
    else if (!INTVAL_RND && (t - this->_prevUpdate >= this->_interval))
    {
        switch (AUTO_MODE)
        {
        case AUTOMODE_FORWARD:
            if (imgPos >= imgLen - 1)
                imgPos = 0;
            else
                imgPos++;
            break;

        case AUTOMODE_BACKRWARD:
            if (imgPos <= 0)
                imgPos = imgLen - 1;
            else
                imgPos--;
            break;

        case AUTOMODE_RND:
            imgPos = random(imgLen);
            break;

        default:
            return false;
        }
        this->_pos = imgPos;
        showImage(this->_imageFiles, this->_pos);

        prtln("t = " + String(t, 10), D1_SERI);
        prtln("direction = " + String(direction, 10), D1_SERI);
        prtln("imgPos = " + String(imgPos, 10), D1_SERI);
        prtln("imgLen = " + String(imgLen, 10), D1_SERI);
        prtln("AUTO_MODE = " + String(AUTO_MODE, 10), D1_SERI);
        prtln("prvUpdate = " + String(this->_prevUpdate, 10), D1_SERI);
        prtln("interval  = " + String(this->_interval, 10), D1_SERI);

        this->_prevUpdate = t;
        return true;
    }

    else if (INTVAL_RND && (t - this->_prevUpdate >= this->_intervalRnd))
    {
        switch (AUTO_MODE)
        {
        case AUTOMODE_FORWARD:
            if (imgPos >= imgLen - 1)
                imgPos = 0;
            else
                imgPos++;
            break;

        case AUTOMODE_BACKRWARD:
            if (imgPos <= 0)
                imgPos = imgLen - 1;
            else
                imgPos--;
            break;

        case AUTOMODE_RND:
            imgPos = random(imgLen);
            break;

        default:
            return false;
        }
        this->_pos = imgPos;
        showImage(this->_imageFiles, this->_pos);

        prtln("t = " + String(t, 10), D1_SERI);
        prtln("direction = " + String(direction, 10), D1_SERI);
        prtln("imgPos = " + String(imgPos, 10), D1_SERI);
        prtln("imgLen = " + String(imgLen, 10), D1_SERI);
        prtln("AUTO_MODE = " + String(AUTO_MODE, 10), D1_SERI);
        prtln("prvUpdate = " + String(this->_prevUpdate, 10), D1_SERI);
        prtln("interval2 = " + String(this->_intervalRnd, 10), D1_SERI);

        this->_intervalRnd = random(this->_interval);
        if (this->_intervalRnd <= 100)
            this->_intervalRnd = 100;

        this->_prevUpdate = t;
        return true;
    }

    return false;
}

bool ImageViewer::setImageFileList(const String &path)
{
    File root = IV_FS.open(path.c_str(), "r");
    if (!root and !root.isDirectory())
    {
        String msg = "Failed to open \"" + DATA_DIR + "\"";
        prtln(msg);
        return false;
    }
    else
    {
        String msg =
            "Success to open image data folder :  \"" + DATA_DIR + "\"";
        prtln(msg);
    }

    File f = root.openNextFile();
    while (f && this->_nImageFiles < MAX_IMAGE_FILES)
    {
        if (!f.isDirectory() && isImageFile(f))
        {
            this->_imageFiles[this->_nImageFiles] = DATA_DIR + "/" + f.name();
            ++this->_nImageFiles;
        }
        f = root.openNextFile();
    }

    if (this->_nImageFiles == 0)
    {
        prtln("No image files found");
        return false;
    }
    else
    {
        //  --- sort -------------------------------------------
        size_t N = this->_nImageFiles;
        for (int i = 0; i < N - 1; ++i)
        {
            for (int j = 0; j < N - 1; ++j)
            {
                if (this->_imageFiles[j] > this->_imageFiles[j + 1])
                {
                    // swap
                    String tmp = this->_imageFiles[j];
                    this->_imageFiles[j] = this->_imageFiles[j + 1];
                    this->_imageFiles[j + 1] = tmp;
                }
            }
        }
    }

    prtln("Image Files:");
    for (size_t c = 0; c < this->_nImageFiles; ++c)
    {
        String msg = " " + String(this->_imageFiles[c]);
        prtln(msg);
        delay(FILE_LIST_DISPLAY_INTERVAL_MS);
    }
    return true;
}

uint8_t ImageViewer::getAutoMode()
{
    return _isAutoMode;
}

void ImageViewer::setAutoMode(uint8_t mode)
{
    _isAutoMode = mode;
    _intervalRnd = 0;
}

uint32_t ImageViewer::getIntval()
{
    return _interval;
}

void ImageViewer::setIntval(uint32_t intval)
{
    _interval = intval;
    _intervalRnd = 0;
}

bool ImageViewer::getIntvalRnd()
{
    return _isAutoModeIntvalRnd;
}

void ImageViewer::setIntvalRnd(bool intvalRnd)
{
    _isAutoModeIntvalRnd = intvalRnd;
    _intervalRnd = 0;
}

void ImageViewer::showImage(const String images[], size_t p)
{
    const char *filename = images[p].c_str();
    String msg = "showImage FileName = " + String(filename);
    prtln(msg, D1_SERI);

    M5.Lcd.startWrite();
    if (isJpeg(filename))
    {
        M5.Lcd.drawJpgFile(filename, 0, 0, M5.Display.width(),
                           M5.Display.height(), 0, 0, 0.0F, 0.0F,
                           middle_center);
    }
    else if (isPng(filename))
    {
        M5.Lcd.drawPngFile(filename, 0, 0, M5.Display.width(),
                           M5.Display.height(), 0, 0, 0.0F, 0.0F,
                           middle_center);
    }
    else if (isBmp(filename))
    {
        M5.Lcd.drawBmpFile(filename, 0, 0, M5.Display.width(),
                           M5.Display.height(), 0, 0, 0.0F, 0.0F,
                           middle_center);
    }
    else
    {
        String msg2 = "ignore: " + String(filename);
        prtln(msg2, D1_SERI);
    }
    M5.Lcd.endWrite();
}

bool ImageViewer::hasExt(const char *filename, const char *ext) const
{
    if (filename == nullptr)
    {
        return false;
    }
    if (ext == nullptr)
    {
        return false;
    }
    const char *p = strrchr(filename, '.');
    return p != nullptr && strcasecmp(ext, p) == 0;
}

bool ImageViewer::isJpeg(const char *filename) const
{
    if (filename == nullptr)
    {
        return false;
    }
    return hasExt(filename, EXT_JPG) || hasExt(filename, EXT_JPEG);
}

bool ImageViewer::isPng(const char *filename) const
{
    if (filename == nullptr)
    {
        return false;
    }
    return hasExt(filename, EXT_PNG);
}

bool ImageViewer::isBmp(const char *filename) const
{
    if (filename == nullptr)
    {
        return false;
    }
    return hasExt(filename, EXT_BMP);
}

bool ImageViewer::isImageFile(const File &f) const
{
    const char *name = f.name();
    return isJpeg(name) || isPng(name) || isBmp(name);
}

bool ImageViewer::parse(const char *config)
{
    if (config == nullptr)
    {
        prtln("config is null");
        return false;
    }
    const String filename = config;

    if (!IV_FS.exists(filename))
    {
        String msg = filename + " is not found";
        prtln(msg);
        return true; // use default
    }
    String msg = "Config: " + filename;
    prtln(msg);

    File f = IV_FS.open(filename, "r");
    if (!f)
    {
        String msg = " E: failed to open";
        prtln(msg);
        return false;
    }
    uint8_t buf[f.size()] = {0};
    f.read(buf, sizeof(buf));
    f.close();

    JSONVar o = JSON.parse((const char *)buf);
    if (JSON.typeof(o) == "undefined")
    {
        prtln(" E: parse");
        return false;
    }
    if (o.hasOwnProperty(KEY_AUTO_MODE))
    {
        this->_isAutoMode = (uint8_t)o[KEY_AUTO_MODE];
    }
    msg = " AutoMode: " + String(this->_isAutoMode, 10);
    prtln(msg);

    if (o.hasOwnProperty(KEY_AUTO_MODE_INTERVAL))
    {
        this->_autoModeInterval = (uint32_t)o[KEY_AUTO_MODE_INTERVAL];
        this->_interval = _autoModeInterval;
    }
    msg = " AutoModeInterval: " + String(this->_autoModeInterval, 10);
    prtln(msg);
    msg = "_Interval: " + String(this->_interval, 10);
    prtln(msg);

    if (o.hasOwnProperty(KEY_AUTO_MODE_INTVAL_RND))
    {
        this->_isAutoModeIntvalRnd = (bool)o[KEY_AUTO_MODE_INTVAL_RND];
    }
    msg = " AutoMode Interval Randomized: " +
          String(this->_isAutoModeIntvalRnd ? "true" : "false");
    prtln(msg);

    // --- DATA_DIR ---
    if (o.hasOwnProperty(KEY_DATA_DIR))
    {
        String getStr1 = JSON.stringify(o[KEY_DATA_DIR]);
        int len = getStr1.length();
        String getStr2 = getStr1.substring(1, len - 1);
        DATA_DIR = getStr2;
        prtln("DATA_DIR = " + DATA_DIR);
    }

    return true;
}

static int32_t getDirection(void)
{
    if (M5.BtnA.wasClicked())
    {
        prtln("BtnA was Clicked!", D1_SERI);
        return -1;
    }
    else if (M5.BtnC.wasClicked())
    {
        prtln("BtnC was Clicked!", D1_SERI);
        return 1;
    }
    else
    {
        return 0;
    }
}
