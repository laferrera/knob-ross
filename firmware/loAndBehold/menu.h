#pragma once
#ifndef MENU_H
#define MENU_H
#include "src/GEM/GEM_adafruit_gfx.h"
// #include <GEM_adafruit_gfx.h>
#include <vector>
#include <string>

enum modes { MAIN_MENU, PERFORMANCE, CHANNEL, TEMPO, LEARN, GLOBAL, TWO_HEADED_MONSTER}
curMode = MAIN_MENU;
// curMode = PERFORMANCE;

const char *channelStr = "Channel";
const char *mainMenuStr = "Main Menu";
const char *performanceMenuStr = "Twist";
const char *tempoMenuStr = "Tempo";
const char *learnMenuStr = "Learn";
const char *globalMenuStr = "Global";
const char *twoHeadedMonsterStr = "Two-Headed Monster";
const char *channelsMenuStr = "Channels";
const char *AmpItemStr = "Amp";
const char *FreqItemStr = "Freq";
const char *CCItemStr = "MIDI CC";
const char *phaseItemStr = "Phase";
const char *WaveItemStr = "Wave";
const char *clipItemStr = "Clip";
const char *knobItemStr = "Knob Dest";
const char *channelItemStr = "Channel Dest";
const char *outputItemStr = "Output Dest";
const char *waveformItemStr = "Waveform";
const char *lfoAmpOffsetItemStr = "Offset";

// list<GEMPage> pages;
// list<GEMItem> items;

std::vector<GEMPage> pages;
std::vector<GEMPage> channelPages;
std::vector<std::vector <GEMItem>> channelPageItems;
std::vector<std::vector<GEMItem>> channelPageLinks;
// TODO make arrays or vectors for the different channelMenuItems 
// std::vector<void (*)()> dirtyChannelFunctions;

// void dirtyChannel(u_int8_t index);
// void dirtyChannel1(){dirtyChannel(1);};
// void dirtyChannel2(){dirtyChannel(2);};
// void dirtyChannel3(){dirtyChannel(3);};
// void dirtyChannel4(){dirtyChannel(4);};
// void dirtyChannel5(){dirtyChannel(5);};
// void dirtyChannel6(){dirtyChannel(6);};
// void dirtyChannel7(){dirtyChannel(7);};
// void dirtyChannel8(){dirtyChannel(8);};



// this example https://github.com/Spirik/GEM/blob/master/examples/AdafruitGFX/Example-03_Party-Hard/Example-03_Party-Hard.ino
GEM_adafruit_gfx menu(display, GEM_POINTER_ROW, GEM_ITEMS_COUNT_AUTO, 12);

// SelectOptionInt twoFiveSixArr[] = {{"-127", -127}, {"-126", -126}, {"-125", -125}, {"-124", -124}, {"-123", -123}, {"-122", -122}, {"-121", -121}, {"-120", -120}, {"-119", -119}, {"-118", -118}, {"-117", -117}, {"-116", -116}, {"-115", -115}, {"-114", -114}, {"-113", -113}, {"-112", -112}, {"-111", -111}, {"-110", -110}, {"-109", -109}, {"-108", -108}, {"-107", -107}, {"-106", -106}, {"-105", -105}, {"-104", -104}, {"-103", -103}, {"-102", -102}, {"-101", -101}, {"-100", -100}, {"-99", -99}, {"-98", -98}, {"-97", -97}, {"-96", -96}, {"-95", -95}, {"-94", -94}, {"-93", -93}, {"-92", -92}, {"-91", -91}, {"-90", -90}, {"-89", -89}, {"-88", -88}, {"-87", -87}, {"-86", -86}, {"-85", -85}, {"-84", -84}, {"-83", -83}, {"-82", -82}, {"-81", -81}, {"-80", -80}, {"-79", -79}, {"-78", -78}, {"-77", -77}, {"-76", -76}, {"-75", -75}, {"-74", -74}, {"-73", -73}, {"-72", -72}, {"-71", -71}, {"-70", -70}, {"-69", -69}, {"-68", -68}, {"-67", -67}, {"-66", -66}, {"-65", -65}, {"-64", -64}, {"-63", -63}, {"-62", -62}, {"-61", -61}, {"-60", -60}, {"-59", -59}, {"-58", -58}, {"-57", -57}, {"-56", -56}, {"-55", -55}, {"-54", -54}, {"-53", -53}, {"-52", -52}, {"-51", -51}, {"-50", -50}, {"-49", -49}, {"-48", -48}, {"-47", -47}, {"-46", -46}, {"-45", -45}, {"-44", -44}, {"-43", -43}, {"-42", -42}, {"-41", -41}, {"-40", -40}, {"-39", -39}, {"-38", -38}, {"-37", -37}, {"-36", -36}, {"-35", -35}, {"-34", -34}, {"-33", -33}, {"-32", -32}, {"-31", -31}, {"-30", -30}, {"-29", -29}, {"-28", -28}, {"-27", -27}, {"-26", -26}, {"-25", -25}, {"-24", -24}, {"-23", -23}, {"-22", -22}, {"-21", -21}, {"-20", -20}, {"-19", -19}, {"-18", -18}, {"-17", -17}, {"-16", -16}, {"-15", -15}, {"-14", -14}, {"-13", -13}, {"-12", -12}, {"-11", -11}, {"-10", -10}, {"-9", -9}, {"-8", -8}, {"-7", -7}, {"-6", -6}, {"-5", -5}, {"-4", -4}, {"-3", -3}, {"-2", -2}, {"-1", -1}, {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"11", 11}, {"12", 12}, {"13", 13}, {"14", 14}, {"15", 15}, {"16", 16}, {"17", 17}, {"18", 18}, {"19", 19}, {"20", 20}, {"21", 21}, {"22", 22}, {"23", 23}, {"24", 24}, {"25", 25}, {"26", 26}, {"27", 27}, {"28", 28}, {"29", 29}, {"30", 30}, {"31", 31}, {"32", 32}, {"33", 33}, {"34", 34}, {"35", 35}, {"36", 36}, {"37", 37}, {"38", 38}, {"39", 39}, {"40", 40}, {"41", 41}, {"42", 42}, {"43", 43}, {"44", 44}, {"45", 45}, {"46", 46}, {"47", 47}, {"48", 48}, {"49", 49}, {"50", 50}, {"51", 51}, {"52", 52}, {"53", 53}, {"54", 54}, {"55", 55}, {"56", 56}, {"57", 57}, {"58", 58}, {"59", 59}, {"60", 60}, {"61", 61}, {"62", 62}, {"63", 63}, {"64", 64}, {"65", 65}, {"66", 66}, {"67", 67}, {"68", 68}, {"69", 69}, {"70", 70}, {"71", 71}, {"72", 72}, {"73", 73}, {"74", 74}, {"75", 75}, {"76", 76}, {"77", 77}, {"78", 78}, {"79", 79}, {"80", 80}, {"81", 81}, {"82", 82}, {"83", 83}, {"84", 84}, {"85", 85}, {"86", 86}, {"87", 87}, {"88", 88}, {"89", 89}, {"90", 90}, {"91", 91}, {"92", 92}, {"93", 93}, {"94", 94}, {"95", 95}, {"96", 96}, {"97", 97}, {"98", 98}, {"99", 99}, {"100", 100}, {"101", 101}, {"102", 102}, {"103", 103}, {"104", 104}, {"105", 105}, {"106", 106}, {"107", 107}, {"108", 108}, {"109", 109}, {"110", 110}, {"111", 111}, {"112", 112}, {"113", 113}, {"114", 114}, {"115", 115}, {"116", 116}, {"117", 117}, {"118", 118}, {"119", 119}, {"120", 120}, {"121", 121}, {"122", 122}, {"123", 123}, {"124", 124}, {"125", 125}, {"126", 126}, {"127", 127}};
SelectOptionInt oneTwoEightArr[] = {{"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"11", 11}, {"12", 12}, {"13", 13}, {"14", 14}, {"15", 15}, {"16", 16}, {"17", 17}, {"18", 18}, {"19", 19}, {"20", 20}, {"21", 21}, {"22", 22}, {"23", 23}, {"24", 24}, {"25", 25}, {"26", 26}, {"27", 27}, {"28", 28}, {"29", 29}, {"30", 30}, {"31", 31}, {"32", 32}, {"33", 33}, {"34", 34}, {"35", 35}, {"36", 36}, {"37", 37}, {"38", 38}, {"39", 39}, {"40", 40}, {"41", 41}, {"42", 42}, {"43", 43}, {"44", 44}, {"45", 45}, {"46", 46}, {"47", 47}, {"48", 48}, {"49", 49}, {"50", 50}, {"51", 51}, {"52", 52}, {"53", 53}, {"54", 54}, {"55", 55}, {"56", 56}, {"57", 57}, {"58", 58}, {"59", 59}, {"60", 60}, {"61", 61}, {"62", 62}, {"63", 63}, {"64", 64}, {"65", 65}, {"66", 66}, {"67", 67}, {"68", 68}, {"69", 69}, {"70", 70}, {"71", 71}, {"72", 72}, {"73", 73}, {"74", 74}, {"75", 75}, {"76", 76}, {"77", 77}, {"78", 78}, {"79", 79}, {"80", 80}, {"81", 81}, {"82", 82}, {"83", 83}, {"84", 84}, {"85", 85}, {"86", 86}, {"87", 87}, {"88", 88}, {"89", 89}, {"90", 90}, {"91", 91}, {"92", 92}, {"93", 93}, {"94", 94}, {"95", 95}, {"96", 96}, {"97", 97}, {"98", 98}, {"99", 99}, {"100", 100}, {"101", 101}, {"102", 102}, {"103", 103}, {"104", 104}, {"105", 105}, {"106", 106}, {"107", 107}, {"108", 108}, {"109", 109}, {"110", 110}, {"111", 111}, {"112", 112}, {"113", 113}, {"114", 114}, {"115", 115}, {"116", 116}, {"117", 117}, {"118", 118}, {"119", 119}, {"120", 120}, {"121", 121}, {"122", 122}, {"123", 123}, {"124", 124}, {"125", 125}, {"126", 126}, {"127", 127}};
SelectOptionInt noteValueArr[] = {{"Bar", 0}, {"1/2", 1}, {"1/4", 2}, {"1/8", 3}, {"1/16", 4}, {"1/32", 5}, {"1/64", 6}, {"1/128", 7}};
SelectOptionInt noteValueAmountArr[] = {{"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"11", 11}, {"12", 12}, {"13", 13}, {"14", 14}, {"15", 15}, {"16", 16}};
SelectOptionInt lfoWaveArr[] = {{"None", LFO_NONE}, {"Sine", LFO_SIN}, {"Triangle", LFO_TRI}, {"Saw", LFO_SAW}, {"Ramp", LFO_RAMP}, {"Square", LFO_SQUARE}, {"Smooth", LFO_SMOOTH}, {"Random", LFO_RANDOM}};
SelectOptionFloat negOneToOneArr[] = {{"-1.00",-1.00},{"-0.99",-0.99},{"-0.98",-0.98},{"-0.97",-0.97},{"-0.96",-0.96},{"-0.95",-0.95},{"-0.94",-0.94},{"-0.93",-0.93},{"-0.92",-0.92},{"-0.91",-0.91},{"-0.90",-0.90},{"-0.89",-0.89},{"-0.88",-0.88},{"-0.87",-0.87},{"-0.86",-0.86},{"-0.85",-0.85},{"-0.84",-0.84},{"-0.83",-0.83},{"-0.82",-0.82},{"-0.81",-0.81},{"-0.80",-0.80},{"-0.79",-0.79},{"-0.78",-0.78},{"-0.77",-0.77},{"-0.76",-0.76},{"-0.75",-0.75},{"-0.74",-0.74},{"-0.73",-0.73},{"-0.72",-0.72},{"-0.71",-0.71},{"-0.70",-0.70},{"-0.69",-0.69},{"-0.68",-0.68},{"-0.67",-0.67},{"-0.66",-0.66},{"-0.65",-0.65},{"-0.64",-0.64},{"-0.63",-0.63},{"-0.62",-0.62},{"-0.61",-0.61},{"-0.60",-0.60},{"-0.59",-0.59},{"-0.58",-0.58},{"-0.57",-0.57},{"-0.56",-0.56},{"-0.55",-0.55},{"-0.54",-0.54},{"-0.53",-0.53},{"-0.52",-0.52},{"-0.51",-0.51},{"-0.50",-0.50},{"-0.49",-0.49},{"-0.48",-0.48},{"-0.47",-0.47},{"-0.46",-0.46},{"-0.45",-0.45},{"-0.44",-0.44},{"-0.43",-0.43},{"-0.42",-0.42},{"-0.41",-0.41},{"-0.40",-0.40},{"-0.39",-0.39},{"-0.38",-0.38},{"-0.37",-0.37},{"-0.36",-0.36},{"-0.35",-0.35},{"-0.34",-0.34},{"-0.33",-0.33},{"-0.32",-0.32},{"-0.31",-0.31},{"-0.30",-0.30},{"-0.29",-0.29},{"-0.28",-0.28},{"-0.27",-0.27},{"-0.26",-0.26},{"-0.25",-0.25},{"-0.24",-0.24},{"-0.23",-0.23},{"-0.22",-0.22},{"-0.21",-0.21},{"-0.20",-0.20},{"-0.19",-0.19},{"-0.18",-0.18},{"-0.17",-0.17},{"-0.16",-0.16},{"-0.15",-0.15},{"-0.14",-0.14},{"-0.13",-0.13},{"-0.12",-0.12},{"-0.11",-0.11},{"-0.10",-0.10},{"-0.09",-0.09},{"-0.08",-0.08},{"-0.07",-0.07},{"-0.06",-0.06},{"-0.05",-0.05},{"-0.04",-0.04},{"-0.03",-0.03},{"-0.02",-0.02},{"-0.01",-0.01},{"0.00",0.00},{"0.01",0.01},{"0.02",0.02},{"0.03",0.03},{"0.04",0.04},{"0.05",0.05},{"0.06",0.06},{"0.07",0.07},{"0.08",0.08},{"0.09",0.09},{"0.10",0.10},{"0.11",0.11},{"0.12",0.12},{"0.13",0.13},{"0.14",0.14},{"0.15",0.15},{"0.16",0.16},{"0.17",0.17},{"0.18",0.18},{"0.19",0.19},{"0.20",0.20},{"0.21",0.21},{"0.22",0.22},{"0.23",0.23},{"0.24",0.24},{"0.25",0.25},{"0.26",0.26},{"0.27",0.27},{"0.28",0.28},{"0.29",0.29},{"0.30",0.30},{"0.31",0.31},{"0.32",0.32},{"0.33",0.33},{"0.34",0.34},{"0.35",0.35},{"0.36",0.36},{"0.37",0.37},{"0.38",0.38},{"0.39",0.39},{"0.40",0.40},{"0.41",0.41},{"0.42",0.42},{"0.43",0.43},{"0.44",0.44},{"0.45",0.45},{"0.46",0.46},{"0.47",0.47},{"0.48",0.48},{"0.49",0.49},{"0.50",0.50},{"0.51",0.51},{"0.52",0.52},{"0.53",0.53},{"0.54",0.54},{"0.55",0.55},{"0.56",0.56},{"0.57",0.57},{"0.58",0.58},{"0.59",0.59},{"0.60",0.60},{"0.61",0.61},{"0.62",0.62},{"0.63",0.63},{"0.64",0.64},{"0.65",0.65},{"0.66",0.66},{"0.67",0.67},{"0.68",0.68},{"0.69",0.69},{"0.70",0.70},{"0.71",0.71},{"0.72",0.72},{"0.73",0.73},{"0.74",0.74},{"0.75",0.75},{"0.76",0.76},{"0.77",0.77},{"0.78",0.78},{"0.79",0.79},{"0.80",0.80},{"0.81",0.81},{"0.82",0.82},{"0.83",0.83},{"0.84",0.84},{"0.85",0.85},{"0.86",0.86},{"0.87",0.87},{"0.88",0.88},{"0.89",0.89},{"0.90",0.90},{"0.91",0.91},{"0.92",0.92},{"0.93",0.93},{"0.94",0.94},{"0.95",0.95},{"0.96",0.96},{"0.97",0.97},{"0.98",0.98},{"0.99",0.99},{"1.00",1.00}};
SelectOptionFloat oneTwoEightDecimalArr[] = {{"0", -1.00}, {"1", -0.98}, {"2", -0.97}, {"3", -0.95}, {"4", -0.94}, {"5", -0.92}, {"6", -0.91}, {"7", -0.89}, {"8", -0.87}, {"9", -0.86}, {"10", -0.84}, {"11", -0.83}, {"12", -0.81}, {"13", -0.80}, {"14", -0.78}, {"15", -0.76}, {"16", -0.75}, {"17", -0.73}, {"18", -0.72}, {"19", -0.70}, {"20", -0.69}, {"21", -0.67}, {"22", -0.65}, {"23", -0.64}, {"24", -0.62}, {"25", -0.61}, {"26", -0.59}, {"27", -0.57}, {"28", -0.56}, {"29", -0.54}, {"30", -0.53}, {"31", -0.51}, {"32", -0.50}, {"33", -0.48}, {"34", -0.46}, {"35", -0.45}, {"36", -0.43}, {"37", -0.42}, {"38", -0.40}, {"39", -0.39}, {"40", -0.37}, {"41", -0.35}, {"42", -0.34}, {"43", -0.32}, {"44", -0.31}, {"45", -0.29}, {"46", -0.28}, {"47", -0.26}, {"48", -0.24}, {"49", -0.23}, {"50", -0.21}, {"51", -0.20}, {"52", -0.18}, {"53", -0.17}, {"54", -0.15}, {"55", -0.13}, {"56", -0.12}, {"57", -0.10}, {"58", -0.09}, {"59", -0.07}, {"60", -0.06}, {"61", -0.04}, {"62", -0.02}, {"63", -0.01}, {"64", 0.01}, {"65", 0.02}, {"66", 0.04}, {"67", 0.06}, {"68", 0.07}, {"69", 0.09}, {"70", 0.10}, {"71", 0.12}, {"72", 0.13}, {"73", 0.15}, {"74", 0.17}, {"75", 0.18}, {"76", 0.20}, {"77", 0.21}, {"78", 0.23}, {"79", 0.24}, {"80", 0.26}, {"81", 0.28}, {"82", 0.29}, {"83", 0.31}, {"84", 0.32}, {"85", 0.34}, {"86", 0.35}, {"87", 0.37}, {"88", 0.39}, {"89", 0.40}, {"90", 0.42}, {"91", 0.43}, {"92", 0.45}, {"93", 0.46}, {"94", 0.48}, {"95", 0.50}, {"96", 0.51}, {"97", 0.53}, {"98", 0.54}, {"99", 0.56}, {"100", 0.57}, {"101", 0.59}, {"102", 0.61}, {"103", 0.62}, {"104", 0.64}, {"105", 0.65}, {"106", 0.67}, {"107", 0.69}, {"108", 0.70}, {"109", 0.72}, {"110", 0.73}, {"111", 0.75}, {"112", 0.76}, {"113", 0.78}, {"114", 0.80}, {"115", 0.81}, {"116", 0.83}, {"117", 0.84}, {"118", 0.86}, {"119", 0.87}, {"120", 0.89}, {"121", 0.91}, {"122", 0.92}, {"123", 0.94}, {"124", 0.95}, {"125", 0.97}, {"126", 0.98}, {"127", 1.00}};
SelectOptionFloat freqArr[] = {{"0.001hz", 0.001f}, {"0.002hz", 0.002f}, {"0.005hz", 0.005f}, {"0.01hz", 0.01f}, {"0.02hz", 0.02f}, {"0.05hz", 0.05f}, {"0.1hz", 0.1f}, {"0.2hz", 0.2f}, {"0.5hz", 0.5f}, {"1hz", 1.0f}, {"2hz", 2.0f}, {"5hz", 5.0f}, {"10hz", 10.0f}, {"20hz", 20.0f}, {"50hz", 50.0f}, {"100hz", 100.0f}, {"200hz", 200.0f}, {"300hz", 300.0f}, {"400hz", 400.0f}, {"500hz", 500.0f}};
SelectOptionInt channelDestinationsArr[] = {{"1", 0}, {"2", 1}, {"3", 2}, {"4", 3}, {"5", 4}, {"6", 5}, {"7", 6}, {"8", 7}, {"9", 8}, {"10", 9}, {"11", 10}, {"12", 11}, {"13", 12}, {"14", 13}, {"15", 14}, {"16", 15}};
SelectOptionInt encoderDestinationsArr[] = {{"Amp", ENC_AMP}, {"Freq", ENC_FREQ}, {"Wave", ENC_WAVEFORM}, {"Offset", ENC_OFFSET}};
SelectOptionInt outputDestinationsArr[] = {{"Bus", OUT_BUS}, {"Amp", OUT_AMP}, {"Freq", OUT_FREQ}, {"Wave", OUT_WAVEFORM}, {"Offset", OUT_OFFSET},{"MIDI", OUT_MIDI}};
SelectOptionInt midiCCArr[] = {{"102", 102}, {"103", 103}, {"104", 104}, {"105", 105}, {"106", 106}, {"107", 107}, {"108", 108}, {"109", 109}, {"110", 110}, {"111", 111}, {"112", 112}, {"113", 113}, {"114", 114}, {"115", 115}, {"116", 116}, {"117", 117}, {"118", 118}, {"119", 119}, {"120", 120}, {"121", 121}, {"122", 122}, {"123", 123}, {"124", 124}, {"125", 125}, {"126", 126}, {"127", 127}};
SelectOptionInt clipModeArr[] = {{"Hard", CLIP_HARD}, {"Scale", CLIP_SCALE}, {"Bounce", CLIP_BOUNCE}};
// s="{"
// i = -1.00
// while i < 1.01
//     s += "{"
//     s += '"' + ('%.2f' % i) + '"' + "," + ('%.2f' % i)
//     s += "},"
//     i += 0.01
// end
// puts  s

GEMPage mainMenuPage(mainMenuStr);
void setModeToPerformance();
void setLfoAmp();
void setLfoFreq();
void setLfoWave();
GEMItem performanceMenuItemButton(performanceMenuStr, setModeToPerformance);
GEMPage channelsMenuPage(channelsMenuStr);
GEMPage tempoMenuPage(tempoMenuStr);
GEMPage learnMenuPage(learnMenuStr);
GEMPage globalMenuPage(globalMenuStr);
GEMPage twoHeadedMonsterMenuPage(twoHeadedMonsterStr);
GEMItem channelsMenuLink(channelsMenuStr, channelsMenuPage);
GEMItem tempoMenuLink(tempoMenuStr, tempoMenuPage);
GEMItem learnMenuLink(learnMenuStr, learnMenuPage);
GEMItem globalMenuLink(globalMenuStr, globalMenuPage);
GEMItem twoHeadedMonsterMenuLink(twoHeadedMonsterStr, twoHeadedMonsterMenuPage);

// GEMItem menuItemInt("Number:", bad_ui_number);

// GEMSelect twoFiveSixSelect(sizeof(twoFiveSixArr) / sizeof(SelectOptionInt), twoFiveSixArr);
GEMSelect oneTwoEightSelect(sizeof(oneTwoEightArr) / sizeof(SelectOptionInt), oneTwoEightArr);
GEMSelect negOneToOneSelect(sizeof(negOneToOneArr) / sizeof(SelectOptionFloat), negOneToOneArr);
GEMSelect freqSelect(sizeof(freqArr) / sizeof(SelectOptionFloat), freqArr);
GEMSelect waveSelect(sizeof(lfoWaveArr) / sizeof(SelectOptionInt), lfoWaveArr);
GEMSelect channelSelect(sizeof(channelDestinationsArr) / sizeof(SelectOptionInt), channelDestinationsArr);
GEMSelect outputDestinationSelect(sizeof(outputDestinationsArr) / sizeof(SelectOptionInt), outputDestinationsArr);
GEMSelect encoderSelect(sizeof(encoderDestinationsArr) / sizeof(SelectOptionInt), encoderDestinationsArr);
GEMSelect midiCCSelect(sizeof(midiCCArr) / sizeof(SelectOptionInt), midiCCArr);
GEMSelect clipModeSelect(sizeof(clipModeArr) / sizeof(SelectOptionInt), clipModeArr);
GEMPage menuPageMain(mainMenuStr);

void setupMainMenu() {
  channelsMenuPage.setParentMenuPage(mainMenuPage);
  tempoMenuPage.setParentMenuPage(mainMenuPage);
  learnMenuPage.setParentMenuPage(mainMenuPage);
  globalMenuPage.setParentMenuPage(mainMenuPage);
  mainMenuPage.addMenuItem(channelsMenuLink);
  mainMenuPage.addMenuItem(performanceMenuItemButton);
  // mainMenuPage.addMenuItem(tempoMenuLink);
  // mainMenuPage.addMenuItem(learnMenuLink);
  // mainMenuPage.addMenuItem(globalMenuLink);
  // mainMenuPage.addMenuItem(twoHeadedMonsterMenuLink);
  menu.setMenuPageCurrent(mainMenuPage);
}

// void setupBankMenu(Bank bank){

// }

// void setupDirtyChannelFunctions(){
//   dirtyChannelFunctions.push_back(dirtyChannel1);
//   dirtyChannelFunctions.push_back(dirtyChannel2);
// }

void dirtyChannel() {
  Serial.println("Dirty channel");
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    channels[i]->lfo->SetFreq(channels[i]->lfoFreq);
    channels[i]->lfo->SetAmp(channels[i]->lfoAmp);
    channels[i]->lfo->SetWaveform(channels[i]->lfoWave);
    // channels[i]->channelDestination = channels[channels[i]->channelDestinationIndex];
    if(channels[i]->channelDestinationIndex == i){
      channels[i]->outputDestination = OUT_BUS;
    }
    // TODO if channel destination is self, set output destination to amp,
    // hide the channels outputDest menu
  }
}

void setupChannelMenu(Channel *channels[]){
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    std::vector<GEMItem> channelItemHolder;

    // todo fix this string issue....
    //  String channelName = "Channel " + String(i);
    //  const char *channelStr = channelName.c_str();
    //  // char *channelStr = channelName.c_str();

    GEMPage *channelPage = new GEMPage(channelStr);
    channelPages.push_back(*channelPage);
    GEMItem *channelPageLink = new GEMItem(channelStr, channelPage);

    GEMItem *encoderDestination = new GEMItem(knobItemStr, channels[i]->encoderDestination, encoderSelect);
    channelItemHolder.push_back(*encoderDestination);
    // not sure why, but adding a callback fixed a crash....
    GEMItem *channelDestination = new GEMItem(channelItemStr, channels[i]->channelDestinationIndex, channelSelect, dirtyChannel);
    channelItemHolder.push_back(*channelDestination);
    GEMItem *outputDestination = new GEMItem(outputItemStr, channels[i]->outputDestination, outputDestinationSelect);
    channelItemHolder.push_back(*outputDestination);
    GEMItem *channelAmp = new GEMItem(AmpItemStr, channels[i]->lfoAmp, negOneToOneSelect, dirtyChannel);
    channelItemHolder.push_back(*channelAmp);
    GEMItem *channelFreq = new GEMItem(FreqItemStr, channels[i]->lfoFreq, freqSelect, dirtyChannel);
    channelItemHolder.push_back(*channelFreq);
    GEMItem *channelWave = new GEMItem(waveformItemStr, channels[i]->lfoWave, waveSelect, dirtyChannel);
    channelItemHolder.push_back(*channelWave);
    GEMItem *channelCC = new GEMItem(CCItemStr, channels[i]->cc, midiCCSelect);
    channelItemHolder.push_back(*channelCC);
    GEMItem *channelPhase = new GEMItem(phaseItemStr, channels[i]->phase, oneTwoEightSelect);
    channelItemHolder.push_back(*channelPhase);
    GEMItem *clipMode = new GEMItem(clipItemStr, channels[i]->clipMode, clipModeSelect);
    channelItemHolder.push_back(*clipMode);
    GEMItem *lfoAmpOffset = new GEMItem(lfoAmpOffsetItemStr, channels[i]->lfoAmpOffset, negOneToOneSelect);
    channelItemHolder.push_back(*lfoAmpOffset);

    channelPage->addMenuItem(*channelFreq);
    channelPage->addMenuItem(*channelAmp);
    channelPage->addMenuItem(*channelWave);
    channelPage->addMenuItem(*lfoAmpOffset);
    channelPage->addMenuItem(*encoderDestination);
    channelPage->addMenuItem(*channelDestination);
    channelPage->addMenuItem(*outputDestination);
    channelPage->addMenuItem(*clipMode);
    channelPage->addMenuItem(*channelPhase);
    channelPage->addMenuItem(*channelCC);
  
    channelsMenuPage.addMenuItem(*channelPageLink);
    channelPage->setParentMenuPage(channelsMenuPage);
    channelPageItems.push_back(channelItemHolder);
  }
}

void setModeToPerformance(){
  Serial.println("Setting mode to performance");
  curMode = PERFORMANCE;
  menu.clearContext();
  // menu.context.exit();
}

#endif
