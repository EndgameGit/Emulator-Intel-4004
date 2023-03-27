#ifndef _COMMANDSPW_H_
#define _COMMANDSPW_H_

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

void comm_fim(Intel4004 *processor, int rp);

void comm_jcn(Intel4004 *processor, uint4_t adr_num);

void comm_src(Intel4004 *processor, uint4_t rp);

void comm_fin(Intel4004 *processor, uint4_t adr_num);

void comm_jin(Intel4004 *processor, uint4_t adr_num);

void comm_jun(Intel4004 *processor, uint12_t adr_num);

void comm_jms(Intel4004 *processor, uint12_t adr_num);

void comm_inc(Intel4004 *processor, uint4_t reg);

void comm_isz(Intel4004 *processor, uint4_t adr_num);

void comm_add(Intel4004 *processor, uint4_t reg);

void comm_sub(Intel4004 *processor, uint4_t reg);

void comm_ld(Intel4004 *processor, uint4_t reg);

void comm_xch(Intel4004 *processor, uint4_t reg);

void comm_bbl(Intel4004 *processor, uint4_t adr_num);

void comm_ldm(Intel4004 *processor, uint4_t adr_num);

void comm_wrm(Intel4004 *processor);

void comm_wmp(Intel4004 *processor);

void comm_wrr(Intel4004 *processor);

void comm_wpm(Intel4004 *processor);

void comm_wr0(Intel4004 *processor);

void comm_wr1(Intel4004 *processor);

void comm_wr2(Intel4004 *processor);

void comm_wr3(Intel4004 *processor);

void comm_sbm(Intel4004 *processor);

void comm_rdm(Intel4004 *processor);

void comm_rdr(Intel4004 *processor);

void comm_adm(Intel4004 *processor);

void comm_rd0(Intel4004 *processor);

void comm_rd1(Intel4004 *processor);

void comm_rd2(Intel4004 *processor);

void comm_rd3(Intel4004 *processor);

void comm_clb(Intel4004 *processor);

void comm_clc(Intel4004 *processor);

void comm_iac(Intel4004 *processor);

void comm_cmc(Intel4004 *processor);

void comm_cma(Intel4004 *processor);

void comm_ral(Intel4004 *processor);

void comm_rar(Intel4004 *processor);

void comm_tcc(Intel4004 *processor);

void comm_dac(Intel4004 *processor);

void comm_tcs(Intel4004 *processor);

void comm_stc(Intel4004 *processor);

void comm_daa(Intel4004 *processor);

void comm_kbp(Intel4004 *processor);

void comm_dcl(Intel4004 *processor);

#endif