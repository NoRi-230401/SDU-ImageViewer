# SDU-ImageViewer

SD-Updaterに対応した画像ファイルの表示ツールです。<br>
SD上の<b>"/Pictures"フォルダ</b>内の画像ファイル(jpg/png形式)を対象とします。<br>
最大５０枚。フォルダは、設定ファイルで変更可能です。<br>

※画像と設定ファイルのサンプルを用意しています。SDにフォルダを作成してコピーしてご使用ください。<br>



## 手動（Manul）モード  <br>
  <b>BtnA:逆順(backward)・BtnC:正順(forward)</b>を押すたびに、<b>ファイル名の並び</b>で画像を切り替えて表示します。<br>
  サンプルの画像ファイルは、０～９までの数字順に並ぶよう名前を付けてます。<br>
  <br>


## 自動（Auto）モード  <br>
  設定ファイル（"/app/imgView/imgView.json"）に従い表示。<br>
  または、<b>BtnBの長押し</b>で、設定メニュー（SettingMenu）で変更する。<br>
<br>
  
  ### AutoMode:<br>
  AutoMode時の画像の表示順の指定する。<br>
  <br>

      0:off　... AutoModeを使用しない
      1:forward
      2:backward
      3:random
<br>

  ### AutoModeInterval<br>
  AutoMode時の画像の表示する間隔時間の設定<br>
  設定ファイルでは、[mSEC]単位で設定する。<br>

    SettingMenuでは、次の３択
      3sec
      5sec
      10sec
  <br>

  ### AutoModeIntvalRnd<br>

  画像表示間隔のMaxを上のAutoMode Interval時間として、その範囲内で表示間隔をランダムにするかどうか指定できる。<br>
    
    false : off
    true  : on
  <br>
  <br>

## 設定メニュー（SettingMenu）：BtnB長押し<br>
  
  ![画像](images/menu-all.jpg )<br>
  
  <b>BtnA: prev</b>　前のmenu<br>
  <b>BtnB: exit</b>　SettingMenuを抜ける<br>
  <b>BtnC: next</b>　次のmenu<br>
<br>

  ### 1.AutoMode:<br>
  AutoMode時の画像の表示順の指定<br>

      0:off
      1:forward
      2:backward
      3:random
<br>

  ### 2.AutoMode Interval<br>
  AutoMode時の画像の表示する間隔時間<br>
  
      3sec
      5sec
      10sec
  <br>

  ### 3.AutoMode Interval Random<br>
  
      off
      on
  <br>
  
  ### 4.Load SD-Updater menu.bin<br>
<br>
SD-Updaterの menu.bin を呼出し、他のアプリに切り替えます。<br>
<br>

 ### 5.Save bin-file to SD<br>
現在動いてるアプリをSDにbinファイルとして保存します。<br>
<br>

 ### 6.Power Off<br>
電源を切ります。<br>
<br><br>

## 設定ファイル
設定ファイルは、SDの"/app/imgView/imgView.json" です。<br>
初期動作の設定を行います。<br>

※設定ファイルがない場合には、次の初期値で動作します。<br>
"AutoMode"　　　　    --> "0" [off]<br>
"AutoModeInterval" 　 --> 3000 [mSec]<br>
"AutoModeIntvalRnd" 　--> "false" [off]<br>
"DataDir"　　　　　　--> "/Pictures"　<br>
<br>

"/app/imgView/imgView.json"のサンプル<br>

```json
{
  "AutoMode": 0,
  "AutoModeInterval": 4000,
  "AutoModeIntvalRnd": true,
  "DataDir" : "/Pictures"
}
```
  "AutoMode"　　　　 -->  "0" to "3" <br>
  "AutoModeInterval"     　 -->  interval Time [mSec]<br>
  "AutoModeIntvalRnd"      -->  "true" or "false"<br>
  "DataDir"  　 --> 　"/Pictures" 画像フォルダ指定<br>
<br>  <br>  


## 対応ハードウエア
### 本体:　 M5Stack Core2
- M5Stack Core2 for AWS（動作確認している機種）<br>
- M5Stack Core2 <br>
<br>

### SD:　 FAT32 format
SDは、相性等があるので動作が不安定になるものがありますので注意が必要です。</b><br>
<br><br>


## 参照情報
次のソフトウエアを参考にさせていただきました。ありがとうございます。<br>
SAITO, Tetsuya：3110さん m5stack-image-viewer<br>
https://github.com/3110/m5stack-image-viewer

<br>

このソフトのGitHub<br>
https://github.com/NoRi-230401/SDU-ImageViewer

<br><br><br>



