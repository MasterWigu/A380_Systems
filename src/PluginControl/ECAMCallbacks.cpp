//
// Created by morei on 23/09/2020.
//

#include "ECAMCallbacks.h"

void lookupECAMDatarefs() {
    FUELMEMOS = (XPLMDataRef*) malloc(8*sizeof(XPLMDataRef));
    FUELPROC = (XPLMDataRef*) malloc(74*sizeof(XPLMDataRef));


    FUELMEMOS[0] = XPLMFindDataRef("A380/ecam/memos/fuel/cross_open");
    FUELMEMOS[1] = XPLMFindDataRef("A380/ecam/memos/fuel/cross_open_abn");
    FUELMEMOS[2] = XPLMFindDataRef("A380/ecam/memos/fuel/cold_xfr");
    FUELMEMOS[3] = XPLMFindDataRef("A380/ecam/memos/fuel/fwd_xfr_prog");
    FUELMEMOS[4] = XPLMFindDataRef("A380/ecam/memos/fuel/jettison_prog");
    FUELMEMOS[5] = XPLMFindDataRef("A380/ecam/memos/fuel/outr_xfr_prog");
    FUELMEMOS[6] = XPLMFindDataRef("A380/ecam/memos/fuel/outr_xfrd");
    FUELMEMOS[7] = XPLMFindDataRef("A380/ecam/memos/fuel/trim_xfrd");

    FUELPROC[0] = XPLMFindDataRef("A380/ecam/fuelproc/all_feeds_low");
    FUELPROC[1] = XPLMFindDataRef("A380/ecam/fuelproc/apu_feed_fault");
    FUELPROC[2] = XPLMFindDataRef("A380/ecam/fuelproc/apu_fvlv_nclosed");
    FUELPROC[3] = XPLMFindDataRef("A380/ecam/fuelproc/coll_1_nfull");
    FUELPROC[4] = XPLMFindDataRef("A380/ecam/fuelproc/coll_2_nfull");
    FUELPROC[5] = XPLMFindDataRef("A380/ecam/fuelproc/coll_3_nfull");
    FUELPROC[6] = XPLMFindDataRef("A380/ecam/fuelproc/coll_4_nfull");
    FUELPROC[7] = XPLMFindDataRef("A380/ecam/fuelproc/xfeed_vlv1_fault");
    FUELPROC[8] = XPLMFindDataRef("A380/ecam/fuelproc/xfeed_vlv2_fault");
    FUELPROC[9] = XPLMFindDataRef("A380/ecam/fuelproc/xfeed_vlv3_fault");
    FUELPROC[10] = XPLMFindDataRef("A380/ecam/fuelproc/xfeed_vlv4_fault");
    FUELPROC[11] = XPLMFindDataRef("A380/ecam/fuelproc/eng_lp1_fault");
    FUELPROC[12] = XPLMFindDataRef("A380/ecam/fuelproc/eng_lp2_fault");
    FUELPROC[13] = XPLMFindDataRef("A380/ecam/fuelproc/eng_lp3_fault");
    FUELPROC[14] = XPLMFindDataRef("A380/ecam/fuelproc/eng_lp4_fault");
    FUELPROC[15] = XPLMFindDataRef("A380/ecam/fuelproc/excess_aft_cg");
    FUELPROC[16] = XPLMFindDataRef("A380/ecam/fuelproc/feed1_low");
    FUELPROC[17] = XPLMFindDataRef("A380/ecam/fuelproc/feed2_low");
    FUELPROC[18] = XPLMFindDataRef("A380/ecam/fuelproc/feed3_low");
    FUELPROC[19] = XPLMFindDataRef("A380/ecam/fuelproc/feed4_low");
    FUELPROC[20] = XPLMFindDataRef("A380/ecam/fuelproc/feed1_pmps_fault");
    FUELPROC[21] = XPLMFindDataRef("A380/ecam/fuelproc/feed2_pmps_fault");
    FUELPROC[22] = XPLMFindDataRef("A380/ecam/fuelproc/feed3_pmps_fault");
    FUELPROC[23] = XPLMFindDataRef("A380/ecam/fuelproc/feed4_pmps_fault");
    FUELPROC[24] = XPLMFindDataRef("A380/ecam/fuelproc/feed1_main_fault");
    FUELPROC[25] = XPLMFindDataRef("A380/ecam/fuelproc/feed2_main_fault");
    FUELPROC[26] = XPLMFindDataRef("A380/ecam/fuelproc/feed3_main_fault");
    FUELPROC[27] = XPLMFindDataRef("A380/ecam/fuelproc/feed4_main_fault");
    FUELPROC[28] = XPLMFindDataRef("A380/ecam/fuelproc/feed1_stby_fault");
    FUELPROC[29] = XPLMFindDataRef("A380/ecam/fuelproc/feed2_stby_fault");
    FUELPROC[30] = XPLMFindDataRef("A380/ecam/fuelproc/feed3_stby_fault");
    FUELPROC[31] = XPLMFindDataRef("A380/ecam/fuelproc/feed4_stby_fault");
    FUELPROC[32] = XPLMFindDataRef("A380/ecam/fuelproc/feed12_low_level");
    FUELPROC[33] = XPLMFindDataRef("A380/ecam/fuelproc/feed34_low_level");
    FUELPROC[34] = XPLMFindDataRef("A380/ecam/fuelproc/fqms12_fault");
    FUELPROC[35] = XPLMFindDataRef("A380/ecam/fuelproc/inn_manxfr_done");
    FUELPROC[36] = XPLMFindDataRef("A380/ecam/fuelproc/inn_qty_lo");
    FUELPROC[37] = XPLMFindDataRef("A380/ecam/fuelproc/jettison");
    FUELPROC[38] = XPLMFindDataRef("A380/ecam/fuelproc/jettison_done");
    FUELPROC[39] = XPLMFindDataRef("A380/ecam/fuelproc/jettsion_fault");
    FUELPROC[40] = XPLMFindDataRef("A380/ecam/fuelproc/jettsion_not_closed");
    FUELPROC[41] = XPLMFindDataRef("A380/ecam/fuelproc/left_inn_pfault");
    FUELPROC[42] = XPLMFindDataRef("A380/ecam/fuelproc/right_inn_pfault");
    FUELPROC[43] = XPLMFindDataRef("A380/ecam/fuelproc/left_inn_aft_pfault");
    FUELPROC[44] = XPLMFindDataRef("A380/ecam/fuelproc/right_inn_aft_pfault");
    FUELPROC[45] = XPLMFindDataRef("A380/ecam/fuelproc/left_mid_aft_pfault");
    FUELPROC[46] = XPLMFindDataRef("A380/ecam/fuelproc/right_mid_aft_pfault");
    FUELPROC[47] = XPLMFindDataRef("A380/ecam/fuelproc/left_inn_fwd_pfault");
    FUELPROC[48] = XPLMFindDataRef("A380/ecam/fuelproc/right_inn_fwd_pfault");
    FUELPROC[49] = XPLMFindDataRef("A380/ecam/fuelproc/left_mid_fwd_pfault");
    FUELPROC[50] = XPLMFindDataRef("A380/ecam/fuelproc/right_mid_fwd_pfault");
    FUELPROC[51] = XPLMFindDataRef("A380/ecam/fuelproc/left_mid_pfault");
    FUELPROC[52] = XPLMFindDataRef("A380/ecam/fuelproc/right_mid_pfault");
    FUELPROC[53] = XPLMFindDataRef("A380/ecam/fuelproc/left_out_pfault");
    FUELPROC[54] = XPLMFindDataRef("A380/ecam/fuelproc/right_out_pfault");
    FUELPROC[55] = XPLMFindDataRef("A380/ecam/fuelproc/left_feeds_pfault");
    FUELPROC[56] = XPLMFindDataRef("A380/ecam/fuelproc/right_feeds_pfault");
    FUELPROC[57] = XPLMFindDataRef("A380/ecam/fuelproc/man_xfr_proc");
    FUELPROC[58] = XPLMFindDataRef("A380/ecam/fuelproc/man_mid_done");
    FUELPROC[59] = XPLMFindDataRef("A380/ecam/fuelproc/norm_alt_fault");
    FUELPROC[60] = XPLMFindDataRef("A380/ecam/fuelproc/norm_xfr_fault");
    FUELPROC[61] = XPLMFindDataRef("A380/ecam/fuelproc/outr_xfr_fault");
    FUELPROC[62] = XPLMFindDataRef("A380/ecam/fuelproc/outr_xfr_done");
    FUELPROC[63] = XPLMFindDataRef("A380/ecam/fuelproc/temp_low");
    FUELPROC[64] = XPLMFindDataRef("A380/ecam/fuelproc/trim_apu_lfault");
    FUELPROC[65] = XPLMFindDataRef("A380/ecam/fuelproc/trim_grv_fwdfault");
    FUELPROC[66] = XPLMFindDataRef("A380/ecam/fuelproc/trim_lpmp_fault");
    FUELPROC[67] = XPLMFindDataRef("A380/ecam/fuelproc/trim_rpmp_fault");
    FUELPROC[68] = XPLMFindDataRef("A380/ecam/fuelproc/trim_lrpmps_fault");
    FUELPROC[69] = XPLMFindDataRef("A380/ecam/fuelproc/trim_xfr_done");
    FUELPROC[70] = XPLMFindDataRef("A380/ecam/fuelproc/trim_xfr_fault");
    FUELPROC[71] = XPLMFindDataRef("A380/ecam/fuelproc/wings_balanced");
    FUELPROC[72] = XPLMFindDataRef("A380/ecam/fuelproc/wings_man_bal");
    FUELPROC[73] = XPLMFindDataRef("A380/ecam/fuelproc/wings_not_balanced");
}

void setFuelMemo(int id, bool state) {
    XPLMSetDatai(FUELMEMOS[id], state ? 1: 0);
}

void setFuelProc(int id, bool state) {
    XPLMSetDatai(FUELPROC[id], state ? 1: 0);
}


