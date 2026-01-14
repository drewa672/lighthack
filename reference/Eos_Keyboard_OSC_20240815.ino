#include <OSCBoards.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <OSCMatch.h>
#include <OSCMessage.h>
#include <OSCTiming.h>
#include <SLIPEncodedSerial.h>
#include <Keyboard.h>
#include "Adafruit_Keypad.h"

#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
 SLIPEncodedSerial SLIPSerial(Serial1); // Change to Serial1 or Serial2 etc. for boards with multiple serial ports that don’t have Serial
#endif

const String HANDSHAKE_QUERY = "ETCOSC?";
const String HANDSHAKE_REPLY = "OK";

void parseOSCMessage(String& msg)
{
  // check to see if this is the handshake string
  if (msg.indexOf(HANDSHAKE_QUERY) != -1)
  {
    // handshake string found!
    SLIPSerial.beginPacket();
    SLIPSerial.write((const uint8_t*)HANDSHAKE_REPLY.c_str(), (size_t)HANDSHAKE_REPLY.length());
    SLIPSerial.endPacket();
  }
}
const byte ROWS1 = 8; // rows
const byte COLS1 = 9; // columns
//define the symbols on the buttons of the keypads
char keys1[ROWS1][COLS1] = {
  {'a','b','c','d','e','f','g','h','i'},
  {'j','k','l','m','n','o','p','q','r'},
  {'s','t','u','v','w','x','y','z','A'},
  {'B','C','D','E','F','G','H','I','J'},
  {'K','L','M','N','O','P','Q','R','S'},
  {'T','U','V','W','X','Y','Z','1','2'},
  {'3','4','5','6','7','8','9','0','!'},
  {'@','#','$','%','^','&','*','(',')'}
};
byte rowPins1[ROWS1] = {30, 32, 34, 36, 38, 40, 42, 44}; //connect to the row pinouts of the keypad
byte colPins1[COLS1] = {31, 33, 35, 37, 39, 41, 43, 45, 47}; //connect to the column pinouts of the keypad
const byte ROWS2 = 8; // rows
const byte COLS2 = 9; // columns
//define the symbols on the buttons of the keypads
char keys2[ROWS2][COLS2] = {
  {'a','b','c','d','e','f','g','h','i'},
  {'j','k','l','m','n','o','p','q','r'},
  {'s','t','u','v','w','x','y','z','A'},
  {'B','C','D','E','F','G','H','I','J'},
  {'K','L','M','N','O','P','Q','R','S'},
  {'T','U','V','W','X','Y','Z','1','2'},
  {'3','4','5','6','7','8','9','0','!'},
  {'@','#','$','%','^','&','*','(',')'}
};
byte rowPins2[ROWS2] = {2, 3, 4, 5, 6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins2[COLS2] = {10, 11, 12, 13, 17, 18, 19, 20, 21}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad1 = Adafruit_Keypad( makeKeymap(keys1), rowPins1, colPins1, ROWS1, COLS1);
Adafruit_Keypad customKeypad2 = Adafruit_Keypad( makeKeymap(keys2), rowPins2, colPins2, ROWS2, COLS2);


void setup() {
  SLIPSerial.begin(9600);
  customKeypad1.begin();
  customKeypad2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  customKeypad1.tick();
  customKeypad2.tick();

while(customKeypad1.available()){
keypadEvent e = customKeypad1.read();

Serial.print((char)e.bit.KEY);
if(e.bit.EVENT == KEY_JUST_PRESSED) {
//a= Macro 801 Ctrl+Alt+1
if (e.bit.KEY == 'a') {
  OSCMessage msg("/eos/key/MACRO_801");
    msg.add((int32_t)analogRead(0));
}
//b= Macro 802 Ctrl+Alt+2
if (e.bit.KEY == 'b') {
  OSCMessage msg("/eos/key/MACRO_802");
    msg.add((int32_t)analogRead(0));
}
//c= Release Ctrl+Alt+S
if (e.bit.KEY == 'c') {
  OSCMessage msg("/eos/key/RELEASE_FADER");
    msg.add((int32_t)analogRead(0));
}
//d= Follow/Hang Shift+D
if (e.bit.KEY == 'd') {
  OSCMessage msg("/eos/key/FOLLOW");
    msg.add((int32_t)analogRead(0));
}
//e= Displays F9
if (e.bit.KEY == 'e') {
  OSCMessage msg("/eos/key/DISPLAYS");
    msg.add((int32_t)analogRead(0));
}
//f= Address|Patch Alt+A
if (e.bit.KEY == 'f') {
  OSCMessage msg("/eos/key/ADDRESS");
    msg.add((int32_t)analogRead(0));
}
//g= Encoder Display
if (e.bit.KEY == 'g') {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('\\');
  delay(100);
  Keyboard.releaseAll();
}
//h= S1 Alt+1
if (e.bit.KEY == 'h') {
  OSCMessage msg("/eos/key/CIA_SOFTKEY1");
    msg.add((int32_t)analogRead(0));
}
//i= S2 Alt+2
if (e.bit.KEY == 'i') {
  OSCMessage msg("/eos/key/CIA_SOFTKEY2");
    msg.add((int32_t)analogRead(0));
}
//j= Macro 803 Ctrl+Alt+3
if (e.bit.KEY == 'j') {
  OSCMessage msg("/eos/key/MACRO_803");
    msg.add((int32_t)analogRead(0));
}
//k= Macro 804 Ctrl+Alt+4
if (e.bit.KEY == 'k') {
  OSCMessage msg("/eos/key/MACRO_804");
    msg.add((int32_t)analogRead(0));
}
//l= Off Ctrl+Alt+O
if (e.bit.KEY == 'l') {
  OSCMessage msg("/eos/key/BUMP_OFF");
    msg.add((int32_t)analogRead(0));
}
//m= Assert Ctrl+Alt+A
if (e.bit.KEY == 'm') {
  OSCMessage msg("/eos/key/ASSERT");
    msg.add((int32_t)analogRead(0));
}
//n= Macro M
if (e.bit.KEY == 'n') {
  OSCMessage msg("/eos/key/MACRO");
    msg.add((int32_t)analogRead(0));
}
//o= Help Alt+/
if (e.bit.KEY == 'o') {
  OSCMessage msg("/eos/key/HELP");
    msg.add((int32_t)analogRead(0));
}
//p= Learn Alt+L
if (e.bit.KEY == 'p') {
  OSCMessage msg("/eos/key/LEARN");
    msg.add((int32_t)analogRead(0));
}
//q= Query Ctrl+Q
if (e.bit.KEY == 'q') {
  OSCMessage msg("/eos/key/QUERY");
    msg.add((int32_t)analogRead(0));
}
//r= Copy To C
if (e.bit.KEY == 'r') {
  OSCMessage msg("/eos/key/COPY_TO");
    msg.add((int32_t)analogRead(0));
}
//s= Macro 805 Ctrl+Alt+5
if (e.bit.KEY == 's') {
  OSCMessage msg("/eos/key/MACRO_805");
    msg.add((int32_t)analogRead(0));
}
//t= Macro 806 Ctrl+Alt+6
if (e.bit.KEY == 't') {
  OSCMessage msg("/eos/key/MACRO_806");
    msg.add((int32_t)analogRead(0));
}
//u= Got to Cue Zero 
if (e.bit.KEY == 'u') {
  OSCMessage msg("/eos/key/GO_TO_CUE_ZERO");
    msg.add((int32_t)analogRead(0));
}
//v= Stop FX Ctrl+Alt+E
if (e.bit.KEY == 'v') {
  OSCMessage msg("/eos/key/STOP_EFFECT");
    msg.add((int32_t)analogRead(0));
}
//w= Delete Delete
if (e.bit.KEY == 'w') {
  OSCMessage msg("/eos/key/DELETE");
    msg.add((int32_t)analogRead(0));
}
//x= Path CTRL+ALT+W
if (e.bit.KEY == 'x') {
  OSCMessage msg("/eos/key/COLOR_PATH");
    msg.add((int32_t)analogRead(0));
}
//y= Effect Alt+E
if (e.bit.KEY == 'y') {
  OSCMessage msg("/eos/key/EFFECT");
    msg.add((int32_t)analogRead(0));
}
//z= Go To Q Ctrl+G
if (e.bit.KEY == 'z') {
  OSCMessage msg("/eos/key/GO_TO_CUE");
    msg.add((int32_t)analogRead(0));
}
//A= Block B
if (e.bit.KEY == 'A') {
  OSCMessage msg("/eos/key/BLOCK");
    msg.add((int32_t)analogRead(0));
}
//B= Macro 807 CTRL+ALT+7
if (e.bit.KEY == 'B') {
  OSCMessage msg("/eos/key/MACRO_807");
    msg.add((int32_t)analogRead(0));
}
//C= Macro 808 Ctrl+Alt+8
if (e.bit.KEY == 'C') {
  OSCMessage msg("/eos/key/MACRO_808");
    msg.add((int32_t)analogRead(0));
}
//D= Freeze Ctrl+Alt+F
if (e.bit.KEY == 'D') {
  OSCMessage msg("/eos/key/PLAYBACK_FREEZE");
    msg.add((int32_t)analogRead(0));
}
//E= Load
if (e.bit.KEY == 'E') {
  OSCMessage msg("/eos/key/LOAD_PLAYBACK");
    msg.add((int32_t)analogRead(0));
}
//F= Part P
if (e.bit.KEY == 'F') {
  OSCMessage msg("/eos/key/PART");
    msg.add((int32_t)analogRead(0));
}
//G= Cue Q
if (e.bit.KEY == 'G') {
  OSCMessage msg("/eos/key/CUE");
    msg.add((int32_t)analogRead(0));
}
//H= Record R
if (e.bit.KEY == 'H') {
  OSCMessage msg("/eos/key/RECORD");
    msg.add((int32_t)analogRead(0));
}
//I= + +
if (e.bit.KEY == 'I') {
  OSCMessage msg("/eos/key/PLUS");
    msg.add((int32_t)analogRead(0));
}
//J= Thru T
if (e.bit.KEY == 'J') {
  OSCMessage msg("/eos/key/THRU");
    msg.add((int32_t)analogRead(0));
}
//K= Macro 809 Ctrl+Alt+9
if (e.bit.KEY == 'K') {
  OSCMessage msg("/eos/key/MACRO_809");
    msg.add((int32_t)analogRead(0));
}
//L= Macro 810 Ctrl+Alt+0
if (e.bit.KEY == 'L') {
  OSCMessage msg("/eos/key/MACRO_810");
    msg.add((int32_t)analogRead(0));
}
//M= Manual Override Ctrl+Alt+M
if (e.bit.KEY == 'M') {
  OSCMessage msg("/eos/key/MANUAL_OVERRIDE");
    msg.add((int32_t)analogRead(0));
}
//N= Timing Disable Ctrl+Alt+T
if (e.bit.KEY == 'N') {
  OSCMessage msg("/eos/key/TIMING_DISABLE");
    msg.add((int32_t)analogRead(0));
}
//O= Intensity Palette Alt+I
if (e.bit.KEY == 'O') {
  OSCMessage msg("/eos/key/INTENSITY_PALETTE");
    msg.add((int32_t)analogRead(0));
}
//P= Focus Palette Alt+F
if (e.bit.KEY == 'P') {
  OSCMessage msg("/eos/key/FOCUS_PALETTE");
    msg.add((int32_t)analogRead(0));
}
//Q= Record Only Ctrl+R
if (e.bit.KEY == 'Q') {
  OSCMessage msg("/eos/key/RECORD_ONLY");
    msg.add((int32_t)analogRead(0));
}
//R= 7 7
if (e.bit.KEY == 'R') {
  OSCMessage msg("/eos/key/7");
    msg.add((int32_t)analogRead(0));
}
//S= 8 8
if (e.bit.KEY == 'S') {
  OSCMessage msg("/eos/key/8");
    msg.add((int32_t)analogRead(0));
}
//V= Rate Ctrl+Alt+R
if (e.bit.KEY == 'V') {
  OSCMessage msg("/eos/key/RATE");
    msg.add((int32_t)analogRead(0));
}
//W= Fader Page Ctrl+P
if (e.bit.KEY == 'W') {
  OSCMessage msg("/eos/key/FADER_PAGES");
    msg.add((int32_t)analogRead(0));

}
//X= Color Palette Alt+C
if (e.bit.KEY == 'X') {
  OSCMessage msg("/eos/key/COLOR_PALETTE");
    msg.add((int32_t)analogRead(0));
}
//Y= Beam Palette Alt+B
if (e.bit.KEY == 'Y') {
  OSCMessage msg("/eos/key/BEAM_PALETTE");
    msg.add((int32_t)analogRead(0));
}
//Z= Update U
if (e.bit.KEY == 'Z') {
  OSCMessage msg("/eos/key/UPDATE");
    msg.add((int32_t)analogRead(0));
}
//1= 4 4
if (e.bit.KEY == '1') {
  OSCMessage msg("/eos/key/1");
    msg.add((int32_t)analogRead(0));
}
//2= 5 5
if (e.bit.KEY == '2') {
  OSCMessage msg("/eos/key/2");
    msg.add((int32_t)analogRead(0));
}
//3= Macro 1.1
if (e.bit.KEY == '3') {
  OSCMessage msg("/eos/key/MACRO_1.1");
    msg.add((int32_t)analogRead(0));
}
//4= Macro 2.1
if (e.bit.KEY == '4') {
  OSCMessage msg("/eos/key/MACRO_2.1");
    msg.add((int32_t)analogRead(0));
}
//5= Macro 3.1
if (e.bit.KEY == '5') {
  OSCMessage msg("/eos/key/MACRO_3.1");
    msg.add((int32_t)analogRead(0));
}
//6= Macro 4.1
if (e.bit.KEY == '6') {
  OSCMessage msg("/eos/key/MACRO_4.1");
    msg.add((int32_t)analogRead(0));
}
//7= Preset Alt+P
if (e.bit.KEY == '7') {
  OSCMessage msg("/eos/key/PRESET");
    msg.add((int32_t)analogRead(0));
}
//8= Sub S
if (e.bit.KEY == '8') {
  OSCMessage msg("/eos/key/SUBMASTER");
    msg.add((int32_t)analogRead(0));
}
//9= Group G
if (e.bit.KEY == '9') {
  OSCMessage msg("/eos/key/GROUP");
    msg.add((int32_t)analogRead(0));
}
//0= 1 1
if (e.bit.KEY == '0') {
  OSCMessage msg("/eos/key/1");
    msg.add((int32_t)analogRead(0));
}
//!= 2 2
if (e.bit.KEY == '!') {
  OSCMessage msg("/eos/key/2");
    msg.add((int32_t)analogRead(0));
}
//@= Macro 1
if (e.bit.KEY == '@') {
  OSCMessage msg("/eos/key/MACRO_1");
    msg.add((int32_t)analogRead(0));
}
//#= Macro 2
if (e.bit.KEY == '#') {
  OSCMessage msg("/eos/key/MACRO_2");
    msg.add((int32_t)analogRead(0));
}
//$= Macro 3
if (e.bit.KEY == '$') {
  OSCMessage msg("/eos/key/MACRO_3");
    msg.add((int32_t)analogRead(0));
}
//%= Macro 4
if (e.bit.KEY == '%') {
  OSCMessage msg("/eos/key/MACRO_4");
    msg.add((int32_t)analogRead(0));
}
//^= Shift Z
if (e.bit.KEY == '^') {
  OSCMessage msg("/eos/key/SHIFT");
    msg.add((int32_t)analogRead(0));
}
//&= Delay D
if (e.bit.KEY == '&') {
  OSCMessage msg("/eos/key/DELAY");
    msg.add((int32_t)analogRead(0));
}
//*= Time I
if (e.bit.KEY == '*') {
  OSCMessage msg("/eos/key/TIME");
    msg.add((int32_t)analogRead(0));
}
//(= Clear Backspace
if (e.bit.KEY == '(') {
  OSCMessage msg("/eos/key/BACKSPACE");
    msg.add((int32_t)analogRead(0));
}
//)= 0 0
if (e.bit.KEY == ')') {
  OSCMessage msg("/eos/key/0");
    msg.add((int32_t)analogRead(0));
}
Serial.println(" pressed");
}
else if(e.bit.EVENT == KEY_JUST_RELEASED) Keyboard.releaseAll();
}
while(customKeypad2.available()){
keypadEvent f = customKeypad2.read();

Serial.print((char)f.bit.KEY);
if(f.bit.EVENT == KEY_JUST_PRESSED) {
//a= S3 Alt+3
if (f.bit.KEY == 'a') {
  OSCMessage msg("/eos/key/CIA_SOFTKEY3");
    msg.add((int32_t)analogRead(0));
}
//b= S4 Alt+4
if (f.bit.KEY == 'b') {
  OSCMessage msg("/eos/key/CIA_SOFTKEY4");
    msg.add((int32_t)analogRead(0));
}
//c= S5 Alt+5
if (f.bit.KEY == 'c') {
  OSCMessage msg("/eos/key/CIA_SOFTKEY5");
    msg.add((int32_t)analogRead(0));
}
//d= S6 Alt+6
if (f.bit.KEY == 'd') {
  OSCMessage msg("/eos/key/CIA_SOFTKEY6");
    msg.add((int32_t)analogRead(0));
}
//e= More SK
if (f.bit.KEY == 'e') {
  OSCMessage msg("/eos/key/MORE_SOFTKEYS");
    msg.add((int32_t)analogRead(0));
}
//f= Live F1
if (f.bit.KEY == 'f') {
  OSCMessage msg("/eos/key/LIVE");
    msg.add((int32_t)analogRead(0));
}
//g= Blind F2
if (f.bit.KEY == 'g') {
  OSCMessage msg("/eos/key/PREVIEW");
    msg.add((int32_t)analogRead(0));
}
//h= Stage F6
if (f.bit.KEY == 'h') {
  OSCMessage msg("/eos/key/STAGING_MODE");
    msg.add((int32_t)analogRead(0));
}
//i= Help Alt+/
if (f.bit.KEY == 'i') {
  OSCMessage msg("/eos/key/HELP");
    msg.add((int32_t)analogRead(0));
}
//j= Recall From E
if (f.bit.KEY == 'j') {
  OSCMessage msg("/eos/key/RECALL_FROM");
    msg.add((int32_t)analogRead(0));
}
//k= Label L
if (f.bit.KEY == 'k') {
  OSCMessage msg("/eos/key/LABEL");
    msg.add((int32_t)analogRead(0));
}
//l= Offset Ctrl+O
if (f.bit.KEY == 'l') {
  OSCMessage msg("/eos/key/OFFSET");
    msg.add((int32_t)analogRead(0));
}
//m= About Y
if (f.bit.KEY == 'm') {
  OSCMessage msg("/eos/key/ABOUT");
    msg.add((int32_t)analogRead(0));
}
//n= Park K
if (f.bit.KEY == 'n') {
  OSCMessage msg("/eos/key/PARK");
    msg.add((int32_t)analogRead(0));
}
//o= Intesnity Alt+.
if (f.bit.KEY == 'o') {
  OSCMessage msg("/eos/key/INTENSITY_CAT");
    msg.add((int32_t)analogRead(0));
}
//p= Focus Ctrl+Alt+,
if (f.bit.KEY == 'p') {
  OSCMessage msg("/eos/key/FOCUS_CAT");
    msg.add((int32_t)analogRead(0));
}
//q= Color Ctrl+Alt+[
if (f.bit.KEY == 'q') {
  OSCMessage msg("/eos/key/COLOR_CAT");
    msg.add((int32_t)analogRead(0));
}
//r= Magic Sheet Alt+M
if (f.bit.KEY == 'r') {
  OSCMessage msg("/eos/key/MAGIC_SHEET");
    msg.add((int32_t)analogRead(0));
}
//s= Assert Ctrl+W
if (f.bit.KEY == 's') {
  OSCMessage msg("/eos/key/ASSERT");
    msg.add((int32_t)analogRead(0));
}
//t= Undo Ctrl+X
if (f.bit.KEY == 't') {
  OSCMessage msg("/eos/key/UNDO");
    msg.add((int32_t)analogRead(0));
}
//u= High Backslash
if (f.bit.KEY == 'u') {
  OSCMessage msg("/eos/key/HIGHLIGHT");
    msg.add((int32_t)analogRead(0));
}
//v= Fan W
if (f.bit.KEY == 'v') {
  OSCMessage msg("/eos/key/FAN");
    msg.add((int32_t)analogRead(0));
}
//w= Capture Ctrl+Alt+P
if (f.bit.KEY == 'w') {
  OSCMessage msg("/eos/key/CAPTURE");
    msg.add((int32_t)analogRead(0));
}
//x= Shutter Alt+,
if (f.bit.KEY == 'x') {
  OSCMessage msg("/eos/key/SHUTTER_CAT");
    msg.add((int32_t)analogRead(0));
}
//y= Image Ctlr+Alt+]
if (f.bit.KEY == 'y') {
  OSCMessage msg("/eos/key/IMAGE_CAT");
    msg.add((int32_t)analogRead(0));
}
//z= Form Ctrl+Alt+;
if (f.bit.KEY == 'z') {
  OSCMessage msg("/eos/key/FORM_CAT");
    msg.add((int32_t)analogRead(0));
}
//A= Snapshot Ctrl+S
if (f.bit.KEY == 'A') {
  OSCMessage msg("/eos/key/SNAPSHOT");
    msg.add((int32_t)analogRead(0));
}
//B= - Minus
if (f.bit.KEY == 'B') {
  OSCMessage msg("/eos/key/MINUS");
    msg.add((int32_t)analogRead(0));
}
//C= Slash /
if (f.bit.KEY == 'C') {
  OSCMessage msg("/eos/key/SLASH");
    msg.add((int32_t)analogRead(0));
}
//D= Mark K
if (f.bit.KEY == 'D') {
  OSCMessage msg("/eos/key/MARK");
    msg.add((int32_t)analogRead(0));
}
//E= Sneak N
if (f.bit.KEY == 'E') {
  OSCMessage msg("/eos/key/SNEAK");
    msg.add((int32_t)analogRead(0));

  SLIPSerial.beginPacket();  
    msg.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message

  delay(20);
}
//F= Select Last Ctrl+L
if (f.bit.KEY == 'F') {
  OSCMessage msg("/eos/key/SELECT_LAST");
    msg.add((int32_t)analogRead(0));
}
//G= Clear Command Line Shift+Backspace
if (f.bit.KEY == 'G') {
  OSCMessage msg("/eos/key/RESET_COMMAND_LINE");
    msg.add((int32_t)analogRead(0));
}
//H= Clear Label Ctrl+Backspace
if (f.bit.KEY == 'H') {
  OSCMessage msg("/eos/key/CLEAR_TEXT");
    msg.add((int32_t)analogRead(0));
}
//I= Parameters Ctrl+D
if (f.bit.KEY == 'I') {
  OSCMessage msg("/eos/key/PARAMETERS");
    msg.add((int32_t)analogRead(0));
}
//J= ML Controls F7
if (f.bit.KEY == 'J') {
  OSCMessage msg("/eos/key/OPEN_ML_CONTROLS");
    msg.add((int32_t)analogRead(0));
}
//K= 9 9
if (f.bit.KEY == 'K') {
  OSCMessage msg("/eos/key/9");
    msg.add((int32_t)analogRead(0));
}
//L= RemDim H
if (f.bit.KEY == 'L') {
  OSCMessage msg("/eos/key/REM_DIM");
    msg.add((int32_t)analogRead(0));
}
//M= +% Ctrl+Alt+=
if (f.bit.KEY == 'M') {
  OSCMessage msg("/eos/key/PLUS10");
    msg.add((int32_t)analogRead(0));
}
//N= Home HOME
if (f.bit.KEY == 'N') {
  OSCMessage msg("/eos/key/HOME");
    msg.add((int32_t)analogRead(0));
}
//O= Select Manual Ctrl+M
if (f.bit.KEY == 'O') {
  OSCMessage msg("/eos/key/SELECT_MANUAL");
    msg.add((int32_t)analogRead(0));
}
//P= Escape ESC
if (f.bit.KEY == 'P') {
  OSCMessage msg("/eos/key/ESCAPE");
    msg.add((int32_t)analogRead(0));
}
//Q= Up UP_ARROW
if (f.bit.KEY == 'Q') {
  OSCMessage msg("/eos/key/ARROW_UP");
    msg.add((int32_t)analogRead(0));
}
//R= Select Ctrl+RETURN
if (f.bit.KEY == 'R') {
  OSCMessage msg("/eos/key/SELECT");
    msg.add((int32_t)analogRead(0));
}
//!= Back Ctrl+SPACE
if (f.bit.KEY == '!') {
  OSCMessage msg("/eos/key/BACK");
    msg.add((int32_t)analogRead(0));
}
//T= 6 6
if (f.bit.KEY == 'T') {
  OSCMessage msg("/eos/key/6");
    msg.add((int32_t)analogRead(0));
}
//U= Out O
if (f.bit.KEY == 'U') {
  OSCMessage msg("/eos/key/OUT");
    msg.add((int32_t)analogRead(0));
}
//V= -% Ctrl+Alt+-
if (f.bit.KEY == 'V') {
  OSCMessage msg("/eos/key/MINUS10");
    msg.add((int32_t)analogRead(0));
}
//W= Trace J
if (f.bit.KEY == 'W') {
  OSCMessage msg("/eos/key/TRACE");
    msg.add((int32_t)analogRead(0));
}
//X= Select Active Ctrl+A
if (f.bit.KEY == 'X') {
  OSCMessage msg("/eos/key/SELECT_ACTIVE");
    msg.add((int32_t)analogRead(0));
}
//Y= Left Arrow
if (f.bit.KEY == 'Y') {
  OSCMessage msg("/eos/key/ARROW_LEFT");
    msg.add((int32_t)analogRead(0));
}
//Z= Down Arrow
if (f.bit.KEY == 'Z') {
  OSCMessage msg("/eos/key/ARROW_DOWN");
    msg.add((int32_t)analogRead(0));
}
//1= Right Arrow
if (f.bit.KEY == '1') {
  OSCMessage msg("/eos/key/ARROW_RIGHT");
    msg.add((int32_t)analogRead(0));
}
//3= 3 3 
if (f.bit.KEY == '3') {
  OSCMessage msg("/eos/key/3");
    msg.add((int32_t)analogRead(0));
}
//4= Full F
if (f.bit.KEY == '4') {
  OSCMessage msg("/eos/key/FULL");
    msg.add((int32_t)analogRead(0));
}
//5= Level Ctrl+V
if (f.bit.KEY == '5') {
  OSCMessage msg("/eos/key/LEVEL");
    msg.add((int32_t)analogRead(0));
}
//6=Qonly X
if (f.bit.KEY == '6') {
  OSCMessage msg("/eos/key/Q_ONLY");
    msg.add((int32_t)analogRead(0));
}
//7= Last PAGE_UP
if (f.bit.KEY == '7') {
  OSCMessage msg("/eos/key/LAST");
    msg.add((int32_t)analogRead(0));
}
//8= Tab TAB
if (f.bit.KEY == '8') {
  OSCMessage msg("/eos/key/SHEET");
    msg.add((int32_t)analogRead(0));
}
//9= Flexi F3
if (f.bit.KEY == '9') {
  OSCMessage msg("/eos/key/FLEXI_PARTITION_TOGGLE");
    msg.add((int32_t)analogRead(0));
}
//0= Time Ctrl+Alt+[
if (f.bit.KEY == '0') {
  OSCMessage msg("/eos/key/TIME");
    msg.add((int32_t)analogRead(0));
}
//)= Go Spacebar
if (f.bit.KEY == ')') {
  OSCMessage msg("/eos/key/GO");
    msg.add((int32_t)analogRead(0));

}
//@= . .
if (f.bit.KEY == '@') {
  OSCMessage msg("/eos/key/POINT");
    msg.add((int32_t)analogRead(0));
}
//#= At A
if (f.bit.KEY == '#') {
  OSCMessage msg("/eos/key/AT");
    msg.add((int32_t)analogRead(0));
}
//$= Enter RETURN
if (f.bit.KEY == '$') {
  OSCMessage msg("/eos/key/ENTER");
    msg.add((int32_t)analogRead(0));
}
//^= Next PAGE_DOWN
if (f.bit.KEY == '^') {
  OSCMessage msg("/eos/key/NEXT");
    msg.add((int32_t)analogRead(0));
}
//0= Format F4
if (f.bit.KEY == '0') {
  OSCMessage msg("/eos/key/FORMAT");
    msg.add((int32_t)analogRead(0));
}
//*= Expand F5
if (f.bit.KEY == '*') {
  OSCMessage msg("/eos/key/EXPAND");
    msg.add((int32_t)analogRead(0));
}
//(= Data Ctrl+D
if (f.bit.KEY == '(') {
  OSCMessage msg("/eos/key/DATA");
    msg.add((int32_t)analogRead(0));

}

Serial.println(" pressed");
}

else if(f.bit.EVENT == KEY_JUST_RELEASED) Keyboard.releaseAll();

}
  delay(10);
}
