# SDU-ImageView

SD-Updaterに対応したファイル画像表示ツールです。<br>



## 手動（Manul）モード  <br>
  BtnA:逆順(backward)・BtnC:正順(forward)を押すたびにファイル名の並びで画像を切り替えて表示<br>
  <br>
  <br>

## Setting menu  ：BtnB長押しで入る。<br>
  ### AutoMode:<br>
  AutoMode時の画像の表示順の指定<br>
  
  　　0:off<br>
      1:forward<br>
      2:backward<br>
      3:random<br>
<br>

  ### AutoModeInterval<br>
  AutoMode時の画像の表示する間隔時間<br>
  <br>
      3sec<br>
      5sec<br>
      10sec<br>
  <br>

  ### AutoModeInterval Random<br>

  off<br>
  on<br>

<br>

  ### Load SD-Updater menu.bin<br>
<br>

 ### Save bin-file to SD<br>
<br>



## 設定ファイル
SDの"/app/imgView/imgView.json"を参照します。<br>
初期動作設定します。
{
  "AutoMode": 0,　　　　　　　　 ：　"0" to "3" 
  "AutoModeInterval": 5000,　　 ：  interval Time [mSec]
  "AutoModeRandomized": false,　：  "true" or "false"
  "DataDir" : "/Pictures"　　　 ：  画像フォルダ指定
}





br>  

## 対応ハードウエア
### 本体:　 M5Stack Core2
- M5Stack Core2 for AWS（動作確認している機種）<br>
- M5Stack Core2 <br>
- M5Stack Core2 v1.1　<br>
<br>

### SD:　 FAT32 format
SDは、相性等（？）で、動作が不安定になるものがありますので注意が必要です。</b><br>
<br><br>



## 使用方法
### 電源投入
電源投入直後のブート時に SD-UpdaterのLobby画面が現れます。<br>
その後、ソフトが立ち上がり、wifi等の設定が完了しますと接続情報が画面に表示されます。<br>
画像から、FileSystemは、SDを選択されていることが確認できます。（初期値）<br><br>
![画像](images/s-webdav01.jpg)<br><br>

<br>

### PCからのアクセス
PCは、win11での説明です。<br>
win11に標準搭載されているエクスプローラーというファイル管理用のソフトを使用します。<br>
エクスプローラー起動後、画面上部の入力箇所に全て半角文字で、<br>
 - <b>"￥￥webDav￥DavWWWRoot"</b>　と入力してください。<br><br>

または、webDav(HOSTNAME)の代わりに、<b>IPアドレス</b>を入れることもできます。<br>
 - <b>(例)　"￥￥192.168.0.16￥DavWWWRoot"</b>

<br><br>
![画像](images/s-pc01.png )<br>

接続が完了しますと、本体（M5Stack Core2）のSDまたは、SPIFFSのフォルダやファイルが画面表示されます。<br>
エクスプローラーでファイル操作することができるようになります。<br><br>

 - 画面にショートカットを作成するとアクセスが簡単になります。<br>

 - デスクトップの「PC」アイコンを右クリックし、ネットワークドライブの割り当てで使用することもできます。<br>

 - スマホ(Android/iPhone)やPC(Mac/Linuex)等でもWebDavは、接続できるようです。<br>
 （未確認）<br>
 <br>

<br><br>

### Special Mode : (BtnB)の長押し<br>
Special Modeの画面になり、FileSystemの変更(SD <-> SPIFFS)等ができます。<br>
![画像](images/s-webdav02.jpg )<br>
<br>
FileSystemが変更されますと、一度リブートします。<br>
その後、変更後のFileSystemが有効になります。<br>

<br><br>

## 参照情報
以下の情報を参照しました。<br>

ESPWebDAVライブラリ<br>
https://github.com/d-a-v/ESPWebDAV<br>

たなかまさゆき さん(@tnkmasayuki)<br>
https://lang-ship.com/blog/work/esp32-webdav/<br>

リナちゃん@chrmlinux03<br>
https://qiita.com/chrmlinux03/items/5d65893760dad6f4bee0<br>

このソフトのGitHub<br>
https://github.com/NoRi-230401/SDU-WebDav<br>

<br><br><br>





# M5Stackシリーズ用画像表示プログラム

M5Stackシリーズでファイルシステム（LittleFS）上にある画像を次々と表示するプログラムです。

以下の2種類の表示方法があります。

* 手動（Manul）モード  
  Aボタン（正順）・Cボタン（逆順）を押すたびに画像を切り替えて表示します。M5Dialの場合はダイヤルを左右（逆順・正順）に回すことで画像を切り替えます。
* 自動（Auto）モード  
  設定ファイルで指定した間隔（ミリ秒）で表示します。指定した表示間隔を最大値としたランダムの間隔で表示することもできます。

## コンパイル方法

[PlatformIO IDE](https://platformio.org/platformio-ide)環境でコンパイルします。機種に合わせて環境を選択してください。

デフォルトの表示の向きは機種ごとに違います。

| 機種            | 環境                  | デフォルトの表示の向き |
| :-------------- | :---------------------| :--------------------- |
| M5Stack BASIC   | env:m5stack-basic     | 1                      |
| M5Stack Fire    | env:m5stack-fire      | 1                      |
| M5Go            | env:m5stack-m5go      | 1                      |
| M5Stack Core2   | env:m5stack-core2     | 1                      |
| M5Stack Core3   | env:m5stack-core3     | 1                      |
| M5Stick C       | env:m5stick-c         | 0                      |
| M5Stick C Plus  | env:m5stick-c-plus    | 0                      |
| M5Stick C Plus2 | env:m5stick-c-plus2   | 0                      |
| M5ATOM S3       | env:m5stack-atoms3    | 0                      |
| M5Dial          | env:m5stack-dial      | 0                      |
| M5Cardputer     | env:m5stack-cardputer | 1                      |
| M5DinMeter      | env:m5stack-din-meter | 0                      |
| CoreInk         | env:m5stack-coreink   | 0                      |
| M5Paper         | env:m5stack-paper     | 1                      |

## 設定ファイル

設定ファイル`data/image-viewer.json`で以下を設定できます。

* `AutoMode`  
  自動表示モードのオン（`true`）・オフ（`false`）
* `AutoModeInterval`  
  自動表示モードのときの画像の切り替え間隔（ミリ秒）
* `AutoModeRandomized`  
  ランダム切り替え間隔モードのオン（`true`）・オフ（`false`）
* `AutoRotation`
  IMUを内蔵している機種で表示を自動的に向きに追従させるか（`true`）・追従させないか（`false`）
* `Orientation`  
  表示の向き（[`M5GFX::setRotation()`](https://docs.m5stack.com/ja/arduino/m5gfx/m5gfx_functions#setrotation)に渡す値）

設定ファイルがない場合は，自動モードはオフ（`false`），切り替え間隔は 3 秒（3000 ミリ秒），ランダム切り替え間隔モードはオフ（`false`），画面の向きに追従させる（`true`），表示の向きはデフォルトの表示の向きになります。

```json
{
  "AutoMode": false,
  "AutoModeInterval": 3000,
  "AutoModeRandomized": false,
  "AutoRotation": false,
  "Orientation": 1
}
```

`AutoRotation`を`false`に設定し，`Orientation`の値を指定することで表示の向きを固定することができます。

```json
{
  "AutoMode": false,
  "AutoModeInterval": 3000,
  "AutoModeRandomized": false,
  "AutoRotation": true
}
```

ランダム切り替え間隔モードをオンにすると，0 ミリ秒から`AutoModeInterval`で指定したミリ秒の間のランダムな間隔で画像を切り替えます。

この設定ファイルは次の「表示する画像のアップロード」の際に画像と一緒に実機のファイルシステムにアップロードされます。

## 表示する画像のアップロード

表示する画像ファイル（PNG，JPEG，BMP）を`data`ディレクトリに置き，以下のいずれかの方法で実機にアップロードします。

* PlatformIO メニューから「Upload Filesystem Image」を選択する。
* コマンドラインから`pio run --target uploadfs`を実行する。

このとき，設定ファイル`data/image-viewer.json`も含め，`data`ディレイクトリに置かれているファイルはすべて実機にアップロードされます。

## 実行方法

プログラムを起動すると，ファイルシステムにある画像ファイル（PNG，JPEG，BMP）を順に表示します。通常は設定ファイルで指定したモードで起動します。Aボタンを押しながら起動すると，設定にかかわらず自動モードになります。

IMUが使える場合は，画面の向きに合わせて表示が自動的に切り替わります。

起動すると以下の画面が表示されます。設定ファイルがない場合`Config:`の情報は表示されません。

```text
Image Viewer v1.0.5
Config:
 /image-viewer.json
 AutoMode: false
 Interval: 3000ms
 Randomized: false
 AutoRotation: true
 Orientation: CW_0, CW_90, CW_180, CW_270, CCW_0, CCW_90, CCW_180, or CCW_270
Mode:
 Manual, Auto, or Auto(Forced)
Rotation:
 Auto, No, or No(IMU disabled)
Image Files:
 画像ファイル1
 画像ファイル2
 ...
 画像ファイルN
```

ファイルシステム上に画像ファイルがない場合は，以下のように表示されます。

```text
Image Viewer v1.0.5
Config:
 /image-viewer.json
 AutoMode: false
 Interval: 3000ms
 Randomized: false
 AutoRotation: true
 Orientation: CW_0, CW_90, CW_180, CW_270, CCW_0, CCW_90, CCW_180, or CCW_270
Mode:
 Manual, Auto, or Auto(Forced)
Rotation:
 Auto, No, or No(IMU disabled)
No image files found
```

画面に画像一覧が表示されてから一定時間（デフォルトは 3 秒）が経過すると表示モードに応じて画面に画像が表示されます。

## 配布用ファームウェアの作成方法

配布用ファームウェアファイルは以下のいずれかの方法で生成できます。

* PlatformIO メニューから「Custom/Generate User Custom」を選択する。
* コマンドラインから`pio run --target firmware`を実行する。

`firmware`ディレクトリに`[機種名]_[名前]_firmware_[バージョン].bin`ファイルが生成されます。

生成されるファームウェアの設定に関しては，`platformio.ini`ファイルの`image-viewer`セクションにある以下の項目を参照してください。

* 機種名  
  `custom_firmware_target`  
  各機種を表す文字列が各環境ごとに定義されています。  
  例：M5Stack Basic = m5basic
* ファームウェアの名前  
  `custom_firmware_name`（初期値：`image_viewer`）
* ファームウェアのバージョンが書かれているファイル名  
  `custom_firmware_version_file` （初期値：`ImageViewer.cpp`）  
  ソースコードの書かれている`"vX.Y.Z"`から`X.Y.Z`の値を抽出します。
* ファームウェアの拡張子（ドットは不要）  
  `custom_firmware_suffix`（初期値：`bin`）
* 生成先ディレクトリ  
  `custom_firmware_dir`（初期値：`firmware`）
