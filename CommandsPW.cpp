#include <400x_GlobalDefines.h>
#include <Intel4004.h>
#include <CommandsPW.h>

#include <stdio.h> //ist entfernbar

/* 
*   Intel4004 Emulator
*   Gruppe: Tobias Traiser, Kilian Wachter, Pascal Wildermuth, Shaig Rustamov
*   Projektabgabe C 2.Semester - 18.07.2021
*/

void comm_fim(Intel4004 *processor, int rp) //fertig
{
    processor->control.raw++;
    UCommand data;
    data.data = processor->rompointer->read(processor->control);
    processor->register_pair[rp] = data.data;
    processor->working_register[rp] = data.nibble.opr;
    processor->working_register[rp + 1] = data.nibble.opa;
    processor->ticks += 8;
}

void comm_jcn(Intel4004 *processor, uint4_t adr_num)
{
    int jump = 0;

    if (((adr_num >> 3) % 2 == 0) && (((processor->accumulator == 0) && (adr_num >> 2) % 2 == 1) || ((processor->carry == 1) && (adr_num >> 1) % 2 == 1) || ((processor->testpin == 0) && (adr_num % 2 == 1))))
    {
        jump = 1;
    }

    if (((adr_num >> 3) % 2 == 1) && (((processor->accumulator != 0) || ((adr_num >> 2) % 2 == 0)) && ((processor->carry == 0) || ((adr_num >> 1) % 2 == 0)) && ((processor->testpin == 1) || ((adr_num % 2 == 0)))))
    {
        jump = 1;
    }

    processor->control.raw++;

    if (jump == 1)
    {
        uint12_t next_command = processor->rompointer->read(processor->control);
        uint12_t hv = (processor->getPC().banked.bank) << 8;
        hv = hv + next_command;
        processor->control.raw = hv - 1;
    }

    processor->ticks += 8;
}

void comm_src(Intel4004 *processor, uint4_t rp)
{
    processor->source_address.raw = processor->register_pair[rp];
}

void comm_fin(Intel4004 *processor, uint4_t adr_num)
{
    uint8_t register_pair0 = processor->register_pair[0];
    uint12_t high_bits = processor->control.banked.bank << 8;
    if (processor->control.banked.address == 0xFF)
    {
        high_bits += 0x100;
    }
    uint12_t data_address = high_bits + register_pair0;
    processor->register_pair[adr_num] = processor->getPtrToROM()->read(data_address);
    processor->ticks += 8;
}

void comm_jin(Intel4004 *processor, uint4_t adr_num)
{
    uint12_t new_address = processor->control.banked.bank << 8;
    if(processor->control.banked.address == 0xFF){new_address += 0x100;}
    new_address = new_address + processor->register_pair[adr_num];
    processor->control.raw = new_address - 1;
}

void comm_jun(Intel4004 *processor, uint12_t adr_num) //nur sprung mit ROM Addresse - sprung auf RAM nicht kapiert (kann auch nicht sein)
{
    processor->control.raw++;
    uint12_t next_command = processor->rompointer->read(processor->control);
    next_command = next_command + adr_num;
    processor->control.raw = next_command - 0x1;
    processor->ticks += 8;
}

void comm_jms(Intel4004 *processor, uint12_t adr_num)
{
    processor->control.raw++;
    uint12_t next_command = processor->rompointer->read(processor->control);
    processor->control.raw++;
    processor->stackpointer->push(processor->control.raw);
    next_command = next_command + adr_num;
    processor->control.raw = next_command - 0x1;
    processor->ticks += 8;
}

void comm_inc(Intel4004 *processor, uint4_t reg)
{
    if (processor->working_register[reg] == 15)
    {
        processor->working_register[reg] = 0;
    }
    else
    {
        processor->working_register[reg]++;
    }
}

void comm_isz(Intel4004 *processor, uint4_t adr_num)
{
    processor->working_register[adr_num] += 1;
    if (processor->working_register[adr_num] > 15)
    {
        processor->working_register[adr_num] -= 16;
    }

    if (processor->working_register[adr_num] != 0)
    {

        uint12_t new_address = (processor->getPC().banked.bank) << 8;
        processor->control.raw++;
        uint8_t rom_data = processor->rompointer->read(processor->control);
        if (processor->control.banked.address == 0xFF || processor->control.banked.address == 0xFE)
        {
            //Wir wissen nicht was passieren soll, wenn wir in Bank 8 sind und die Bänke incrementieren
            new_address += 0x100;
        }

        new_address = new_address + rom_data;

        processor->control.raw = new_address - 1;
        processor->ticks += 8;
    }
    else
    {
        processor->control.raw++;
    }
}

void comm_add(Intel4004 *processor, uint4_t reg)
{
    uint4_t carry = processor->carry;
    uint4_t reg_data = processor->working_register[reg];
    int calculated_sum = processor->accumulator + carry + reg_data;
    if ((calculated_sum >> 4) > 0)
    {
        processor->accumulator = calculated_sum - 16;
        processor->carry = 1;
    }
    else
    {
        processor->accumulator = calculated_sum;
        processor->carry = 0;
    }
}

void comm_sub(Intel4004 *processor, uint4_t reg)
{
    uint4_t compl_carry;
    if (processor->getCarry() == true)
    {
        compl_carry = 0;
    }
    else
    {
        compl_carry = 1;
    }
    uint4_t compl_reg_data = (~(processor->working_register[reg]) << 4);
    compl_reg_data = compl_reg_data >> 4;
    int calculated_sum = processor->accumulator + compl_carry + compl_reg_data;
    if ((calculated_sum >> 4) > 0)
    {
        processor->accumulator = calculated_sum - 16;
        processor->carry = 1;
    }
    else
    {
        processor->accumulator = calculated_sum;
        processor->carry = 0;
    }
}

void comm_ld(Intel4004 *processor, uint4_t reg)
{
    processor->accumulator = processor->working_register[reg];
}

void comm_xch(Intel4004 *processor, uint4_t reg)
{
    uint4_t value = processor->getAccumulator();
    processor->accumulator = processor->getRegister((ERegister)reg);
    processor->working_register[reg] = value;
}

void comm_bbl(Intel4004 *processor, uint4_t adr_num)
{
    processor->accumulator = adr_num;
    processor->control = processor->stackpointer->pop();
}

void comm_ldm(Intel4004 *processor, uint4_t adr_num) 
{
    processor->accumulator = adr_num;
}

void comm_wrm(Intel4004 *processor)
{

    if (processor->rampointer->isRAMAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        processor->rampointer->writeRAMNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, processor->source_address.ram_data_character.register_data, processor->getAccumulator());
    }
}

void comm_wmp(Intel4004 *processor)
{
    if(processor->rampointer->isRAMAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_output_port.port)){
        processor->rampointer->writeToPortBuffer(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_output_port.port, processor->getAccumulator());
    }
}

void comm_wrr(Intel4004 *processor)
{
    processor->rompointer->writeToPort((EROMChip)processor->source_address.rom_io_port.port, processor->getAccumulator());
}

void comm_wpm(Intel4004 *processor)
{
    //only used with 4008/4009 or 4289
}

void comm_wr0(Intel4004 *processor)
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip))
    {
        processor->rampointer->writeStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip, (ERAMRegister)processor->source_address.ram_status_character.ram_register, 0, processor->getAccumulator());
    }
}

void comm_wr1(Intel4004 *processor)
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip))
    {
        processor->rampointer->writeStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip, (ERAMRegister)processor->source_address.ram_status_character.ram_register, 1, processor->getAccumulator());
    }
}

void comm_wr2(Intel4004 *processor)
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip))
    {
        processor->rampointer->writeStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip, (ERAMRegister)processor->source_address.ram_status_character.ram_register, 2, processor->getAccumulator());
    }
}

void comm_wr3(Intel4004 *processor)
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip))
    {
        processor->rampointer->writeStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_status_character.ram_chip, (ERAMRegister)processor->source_address.ram_status_character.ram_register, 3, processor->getAccumulator());
    }
}

void comm_sbm(Intel4004 *processor)
{
    if (processor->rampointer->isRAMAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        uint4_t compl_carry;
        if (processor->getCarry() == true)
        {
            compl_carry = 0;
        }
        else
        {
            compl_carry = 1;
        }
        uint4_t compl_ram_data = (~(processor->rampointer->readRAMNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, processor->source_address.ram_data_character.register_data)) << 4);
        compl_ram_data = compl_ram_data >> 4;
        int calculated_sum = processor->accumulator + compl_carry + compl_ram_data;
        if ((calculated_sum >> 4) > 0)
        {
            processor->accumulator = calculated_sum - 16;
            processor->carry = 1;
        }
        else
        {
            processor->accumulator = calculated_sum;
            processor->carry = 0;
        }
    }
}

void comm_rdm(Intel4004 *processor)
{
    if (processor->rampointer->isRAMAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        processor->accumulator = processor->rampointer->readRAMNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, processor->source_address.ram_data_character.register_data);
    }
}

void comm_rdr(Intel4004 *processor)
{
    processor->accumulator = processor->rompointer->readFromPort((EROMChip)processor->source_address.rom_io_port.port);
}

void comm_adm(Intel4004 *processor)
{
    if (processor->rampointer->isRAMAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        uint4_t ram_value = processor->rampointer->readRAMNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, processor->source_address.ram_data_character.register_data);
        uint4_t carry_value = processor->carry;
        int calculated_sum = processor->accumulator + ram_value + carry_value;
        if ((calculated_sum >> 4) > 0)
        {
            processor->accumulator = calculated_sum - 16;
            processor->carry = 1;
        }
        else
        {
            processor->accumulator = calculated_sum;
            processor->carry = 0;
        }
    }
}

void comm_rd0(Intel4004 *processor) //fertig
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        processor->accumulator = processor->rampointer->readStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, 0);
    }
}

void comm_rd1(Intel4004 *processor) //fertig
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        processor->accumulator = processor->rampointer->readStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, 1);
    }
}

void comm_rd2(Intel4004 *processor) //fertig
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        processor->accumulator = processor->rampointer->readStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, 2);
    }
}

void comm_rd3(Intel4004 *processor) //fertig
{
    if (processor->rampointer->isStatusAdrAccessable(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip))
    {
        processor->accumulator = processor->rampointer->readStatusNibble(processor->selected_ram_bank, (ERAMChip)processor->source_address.ram_data_character.ram_chip, (ERAMRegister)processor->source_address.ram_data_character.ram_register, 3);
    }
}

void comm_clb(Intel4004 *processor)
{
    processor->carry = 0;
    processor->accumulator = 0;
}

void comm_clc(Intel4004 *processor)
{
    processor->carry = 0;
}

void comm_iac(Intel4004 *processor)
{
    if (processor->accumulator == 15)
    {
        processor->accumulator = 0;
        processor->carry = 1;
    }
    else
    {
        processor->accumulator += 1;
        processor->carry = 0;
    }
}

void comm_cmc(Intel4004 *processor)
{
    if (processor->carry == 0)
    {
        processor->carry = 1;
    }
    else
    {
        processor->carry = 0;
    }
}

void comm_cma(Intel4004 *processor)
{
    processor->accumulator = ~processor->accumulator;
}

void comm_ral(Intel4004 *processor)
{
    uint4_t HV = 0;
    if (processor->carry == 1)
    {
        HV = 1;
    }
    if (processor->accumulator >= 8)
    {
        processor->carry = 1;
    }
    else
    {
        processor->carry = 0;
    }
    processor->accumulator = processor->accumulator << 1;
    if (processor->accumulator >= 16)
    {
        processor->accumulator -= 16;
    }

    if (HV == 1)
    {
        processor->accumulator += 1;
    }
}

void comm_rar(Intel4004 *processor)
{
    uint4_t HV = 0;
    if (processor->carry == 1)
    {
        HV = 1;
    }

    if (processor->accumulator % 2 == 1)
    {
        processor->carry = 1;
    }
    else
    {
        processor->carry = 0;
    }
    processor->accumulator = processor->accumulator >> 1;
    if (HV == 1)
    {
        processor->accumulator += 8;
    }
}

void comm_tcc(Intel4004 *processor)
{
    if (processor->carry == 0)
    {
        processor->accumulator = 0;
    }
    else
    {
        processor->accumulator = 1;
    }
    processor->carry = 0;
}

void comm_dac(Intel4004 *processor)
{
    if (processor->accumulator == 0)
    {
        processor->accumulator = 15;
        processor->carry = 0;
    }
    else
    {
        processor->accumulator -= 1;
        processor->carry = 1;
    }
}

void comm_tcs(Intel4004 *processor)
{
    if (processor->carry == 0)
    {
        processor->accumulator = 9;
    }
    else
    {
        processor->accumulator = 10;
    }
    processor->carry = 0;
}

void comm_stc(Intel4004 *processor)
{
    processor->carry = 1;
}

void comm_daa(Intel4004 *processor)
{
    if (processor->accumulator > 9 || processor->carry == 1)
    {
        if (processor->accumulator > 9)
        {
            processor->carry = 1;
        }
        processor->accumulator += 6;
        if (processor->accumulator >= 16)
        {
            processor->accumulator -= 16;
        }
    }
}

void comm_kbp(Intel4004 *processor)
{
    if (processor->accumulator == 4)
    {
        processor->accumulator = 3;
    }
    else if (processor->accumulator == 8)
    {
        processor->accumulator = 4;
    }
    else if (processor->accumulator > 2)
    {
        processor->accumulator = 15;
    }
}

void comm_dcl(Intel4004 *processor) //fertig
{
    uint4_t bank;
    if (processor->accumulator < 8)
    {
        bank = processor->accumulator;
    }
    else
    {
        bank = processor->accumulator - 8;
    }
    processor->selected_ram_bank = (ERAMBank)bank;
}
