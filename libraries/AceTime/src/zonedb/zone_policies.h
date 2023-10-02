// This file was generated by the following script:
//
//   $ /home/brian/src/AceTimeTools/src/acetimetools/tzcompiler.py
//     --input_dir /home/brian/src/AceTime/src/zonedb/tzfiles
//     --output_dir /home/brian/src/AceTime/src/zonedb
//     --tz_version 2023c
//     --action zonedb
//     --language arduino
//     --scope basic
//     --db_namespace zonedb
//     --start_year 2000
//     --until_year 2200
//
// using the TZ Database files
//
//   africa
//   antarctica
//   asia
//   australasia
//   backward
//   etcetera
//   europe
//   northamerica
//   southamerica
//
// from https://github.com/eggert/tz/releases/tag/2023c
//
// Supported Zones: 448 (228 zones, 220 links)
// Unsupported Zones: 148 (122 zones, 26 links)
//
// Requested Years: [2000,2200]
// Accurate Years: [2000,32767]
//
// Original Years:  [1844,2087]
// Generated Years: [1950,2023]
// Lower/Upper Truncated: [True,False]
//
// Estimator Years: [1950,2025]
// Max Buffer Size: 6
//
// Records:
//   Infos: 448
//   Eras: 240
//   Policies: 65
//   Rules: 367
//
// Memory (8-bits):
//   Context: 16
//   Rules: 3303
//   Policies: 195
//   Eras: 2640
//   Zones: 2964
//   Links: 2860
//   Registry: 896
//   Formats: 467
//   Letters: 29
//   Fragments: 116
//   Names: 4162 (original: 6534)
//   TOTAL: 17648
//
// Memory (32-bits):
//   Context: 24
//   Rules: 4404
//   Policies: 520
//   Eras: 3840
//   Zones: 5472
//   Links: 5280
//   Registry: 1792
//   Formats: 467
//   Letters: 41
//   Fragments: 138
//   Names: 4162 (original: 6534)
//   TOTAL: 26140
//
// DO NOT EDIT

#ifndef ACE_TIME_ZONEDB_ZONE_POLICIES_H
#define ACE_TIME_ZONEDB_ZONE_POLICIES_H

#include <zoneinfo/infos.h>

namespace ace_time {
namespace zonedb {

//---------------------------------------------------------------------------
// Supported policies: 65
//---------------------------------------------------------------------------

extern const basic::ZonePolicy kZonePolicyAN;
extern const basic::ZonePolicy kZonePolicyAQ;
extern const basic::ZonePolicy kZonePolicyAS;
extern const basic::ZonePolicy kZonePolicyAT;
extern const basic::ZonePolicy kZonePolicyAV;
extern const basic::ZonePolicy kZonePolicyAW;
extern const basic::ZonePolicy kZonePolicyArmenia;
extern const basic::ZonePolicy kZonePolicyAus;
extern const basic::ZonePolicy kZonePolicyAzer;
extern const basic::ZonePolicy kZonePolicyBarb;
extern const basic::ZonePolicy kZonePolicyBelize;
extern const basic::ZonePolicy kZonePolicyBrazil;
extern const basic::ZonePolicy kZonePolicyC_Eur;
extern const basic::ZonePolicy kZonePolicyCO;
extern const basic::ZonePolicy kZonePolicyCR;
extern const basic::ZonePolicy kZonePolicyCanada;
extern const basic::ZonePolicy kZonePolicyChatham;
extern const basic::ZonePolicy kZonePolicyChile;
extern const basic::ZonePolicy kZonePolicyCook;
extern const basic::ZonePolicy kZonePolicyCuba;
extern const basic::ZonePolicy kZonePolicyDhaka;
extern const basic::ZonePolicy kZonePolicyEU;
extern const basic::ZonePolicy kZonePolicyEUAsia;
extern const basic::ZonePolicy kZonePolicyEcuador;
extern const basic::ZonePolicy kZonePolicyEire;
extern const basic::ZonePolicy kZonePolicyFiji;
extern const basic::ZonePolicy kZonePolicyGuat;
extern const basic::ZonePolicy kZonePolicyHK;
extern const basic::ZonePolicy kZonePolicyHaiti;
extern const basic::ZonePolicy kZonePolicyHoliday;
extern const basic::ZonePolicy kZonePolicyHond;
extern const basic::ZonePolicy kZonePolicyIran;
extern const basic::ZonePolicy kZonePolicyIraq;
extern const basic::ZonePolicy kZonePolicyJapan;
extern const basic::ZonePolicy kZonePolicyJordan;
extern const basic::ZonePolicy kZonePolicyLH;
extern const basic::ZonePolicy kZonePolicyLebanon;
extern const basic::ZonePolicy kZonePolicyMacau;
extern const basic::ZonePolicy kZonePolicyMauritius;
extern const basic::ZonePolicy kZonePolicyMexico;
extern const basic::ZonePolicy kZonePolicyMoldova;
extern const basic::ZonePolicy kZonePolicyMoncton;
extern const basic::ZonePolicy kZonePolicyMongol;
extern const basic::ZonePolicy kZonePolicyNC;
extern const basic::ZonePolicy kZonePolicyNZ;
extern const basic::ZonePolicy kZonePolicyNamibia;
extern const basic::ZonePolicy kZonePolicyNic;
extern const basic::ZonePolicy kZonePolicyPRC;
extern const basic::ZonePolicy kZonePolicyPakistan;
extern const basic::ZonePolicy kZonePolicyPara;
extern const basic::ZonePolicy kZonePolicyPeru;
extern const basic::ZonePolicy kZonePolicyPhil;
extern const basic::ZonePolicy kZonePolicyROK;
extern const basic::ZonePolicy kZonePolicyRussiaAsia;
extern const basic::ZonePolicy kZonePolicySA;
extern const basic::ZonePolicy kZonePolicySalv;
extern const basic::ZonePolicy kZonePolicyTaiwan;
extern const basic::ZonePolicy kZonePolicyThule;
extern const basic::ZonePolicy kZonePolicyTonga;
extern const basic::ZonePolicy kZonePolicyTunisia;
extern const basic::ZonePolicy kZonePolicyUS;
extern const basic::ZonePolicy kZonePolicyUruguay;
extern const basic::ZonePolicy kZonePolicyVanuatu;
extern const basic::ZonePolicy kZonePolicyWinn;
extern const basic::ZonePolicy kZonePolicyZion;


//---------------------------------------------------------------------------
// Unsupported policies: 69
//---------------------------------------------------------------------------

// Albania {unused}
// Algeria {unused}
// Arg {unused}
// Austria {unused}
// Belgium {unused}
// Bermuda {unused}
// Bulg {unused}
// CA {unused}
// Chicago {unused}
// Cyprus {unused}
// Czech {unused}
// DR {unused}
// Denver {unused}
// Detroit {unused}
// E-Eur {unused}
// E-EurAsia {unused}
// Edm {unused}
// Egypt {Found 2 transitions in year/month '2010-09'}
// EgyptAsia {unused}
// Falk {unused}
// Finland {unused}
// France {unused}
// GB-Eire {unused}
// Germany {unused}
// Greece {unused}
// Guam {unused}
// Halifax {unused}
// Hungary {unused}
// Indianapolis {unused}
// Italy {unused}
// Kyrgyz {unused}
// Latvia {unused}
// Libya {unused}
// Louisville {unused}
// Malta {unused}
// Marengo {unused}
// Menominee {unused}
// Morocco {unused}
// NBorneo {unused}
// NT_YK {unused}
// NYC {unused}
// Palestine {Found 2 transitions in year/month '2040-10'}
// Perry {unused}
// Pike {unused}
// Poland {unused}
// Port {unused}
// Pulaski {unused}
// Regina {unused}
// Romania {unused}
// Russia {unused}
// SanLuis {unused}
// Shang {unused}
// SovietZone {unused}
// Spain {unused}
// SpainAfrica {unused}
// StJohns {unused}
// Starke {unused}
// Sudan {unused}
// Swift {unused}
// Swiss {unused}
// Syria {unused}
// Toronto {unused}
// Troll {unused}
// Turkey {unused}
// Vanc {unused}
// Vincennes {unused}
// W-Eur {unused}
// WS {unused}
// Yukon {unused}


//---------------------------------------------------------------------------
// Notable zone policies: 5
//---------------------------------------------------------------------------

// Belize {LETTER 'CST' not single character}
// Eire {SAVE '-1:00' is a negative DST}
// LH {SAVE '0:30' different from 1:00}
// Moncton {AT '0:01' not multiple of :15 min}
// Namibia {
//   LETTER 'CAT' not single character,
//   LETTER 'WAT' not single character,
//   SAVE '-1:00' is a negative DST,
// }


}
}

#endif
