// /////////////////////////////////////////////////////////////////////////
// C++ code automatically generated by hif2sc
// Part of HIFSuite - Version 2017.05.1-antlia
// Site: www.hifsuite.com - Contact: hifsuite@edalab.it
//
// HIFSuite copyright: EDALab s.r.l. - Networked Embedded Systems
// Site: www.edalab.it - Contact: info@edalab.it
// /////////////////////////////////////////////////////////////////////////


#include "../inc/memory.hpp"




memory::memory() :
    result_rdy_old(false),
    result_old(uint16_t(0U)),
    accelerometer_old(uint16_t(0U)),
    oeb_old(false),
    we_n_old(false),
    sync_old(false),
    vpab_old(false),
    datao_old(uint8_t(0U)),
    addr_old(uint16_t(0U)),
    rst_old(false),
    clk_old(false),
    hif_a2t_data(
    false,
    false,
    uint16_t(0U),
    uint8_t(0U),
    uint8_t(0U),
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    uint16_t(0U),
    uint16_t(0U),
    false,
    uint16_t(0U),
    false),
    data_mspw(),
    datai_mspw(),
    state(uint8_t(0U)),
    state_sig_var(uint8_t(0U)),
    ram(),
    rom(),
    memory_addr_switch(false),
    memory_addr(uint16_t(0U)),
    data_mspw_new(),
    datai_mspw_new(),
    state_new(uint8_t(0U)),
    process_in_queue(false),
    flag_initial_process_executed(false),
    flag_process_executed(false),
    flag_state(false),
    flag_process_1_executed(false),
    flag_clk(false),
    flag_addr(false),
    flag_datai_mspw(false),
    flag_data_mspw(false),
    flag_process_0_process_2_executed(false),
    ACCELEROMETER_HIGH_ADDRESS(8187UL),
    ACCELEROMETER_LOW_ADDRESS(8186UL),
    DATA_HIGH_ADDRESS(8185UL),
    DATA_LOW_ADDRESS(8184UL),
    RESULT_HIGH_ADDRESS(8183UL),
    RESULT_LOW_ADDRESS(8182UL),
    DATA_RDY_ADDRESS(8181UL),
    RESULT_RDY_ADDRESS(8180UL),
    ST_START(uint8_t(0U)),
    ST_1(uint8_t(1U)),
    ST_2(uint8_t(2U)),
    ST_3(uint8_t(3U)),
    ST_4(uint8_t(4U)),
    ST_5(uint8_t(5U)),
    ST_6(uint8_t(6U)),
    ST_7(uint8_t(7U)),
    ST_8(uint8_t(8U)),
    ST_9(uint8_t(9U)),
    ST_10(uint8_t(10U)),
    ST_11(uint8_t(11U)),
    ST_12(uint8_t(12U)),
    ST_13(uint8_t(13U)),
    ST_14(uint8_t(14U)),
    ST_15(uint8_t(15U))

{
    for (int ind = 15L; ind >= 0L; ind = ind - 1)
    {
        data_mspw[ind] = false;
    }
    for (int ind_0 = 7L; ind_0 >= 0L; ind_0 = ind_0 - 1)
    {
        datai_mspw[ind_0] = false;
    }
    for (int ind_1 = 32767L; ind_1 >= 0L; ind_1 = ind_1 - 1)
    {
        ram[ind_1] = uint8_t(0U);
    }
    for (int ind_2 = 8191L; ind_2 >= 0L; ind_2 = ind_2 - 1)
    {
        rom[ind_2] = uint8_t(0U);
    }
    for (int ind_3 = 15L; ind_3 >= 0L; ind_3 = ind_3 - 1)
    {
        data_mspw_new[ind_3] = false;
    }
    for (int ind_4 = 7L; ind_4 >= 0L; ind_4 = ind_4 - 1)
    {
        datai_mspw_new[ind_4] = false;
    }

}


memory::~memory()
{}


void memory::initial_process()
{
    hif_verilog_standard::hif_verilog__system_readmemh( "./roms/rom.mem", rom, 0L,
             8191L, 0L, 8191L );
    state_sig_var = ST_START;
    state_new = state_sig_var;
    hif_a2t_data.datai = uint8_t(0U);
    hif_a2t_data.irq_n = false;
    hif_a2t_data.nmi_n = false;
    hif_a2t_data.res_n = false;
    hif_a2t_data.rdy = false;
    hif_a2t_data.sob_n = false;
    hif_a2t_data.data_rdy = false;
    hif_a2t_data.data = uint16_t(0U);
}


void memory::process()
{
    if (ST_START == state_sig_var)
    {
        datai_mspw_new[7L] = false;
        datai_mspw_new[6L] = false;
        datai_mspw_new[5L] = false;
        datai_mspw_new[4L] = false;
        datai_mspw_new[3L] = false;
        datai_mspw_new[2L] = false;
        datai_mspw_new[1L] = false;
        datai_mspw_new[0L] = false;
        hif_a2t_data.irq_n = false;
        hif_a2t_data.nmi_n = false;
        hif_a2t_data.res_n = false;
        hif_a2t_data.rdy = false;
        hif_a2t_data.sob_n = false;
        hif_a2t_data.data_rdy = false;
        data_mspw_new[15L] = false;
        data_mspw_new[14L] = false;
        data_mspw_new[13L] = false;
        data_mspw_new[12L] = false;
        data_mspw_new[11L] = false;
        data_mspw_new[10L] = false;
        data_mspw_new[9L] = false;
        data_mspw_new[8L] = false;
        data_mspw_new[7L] = false;
        data_mspw_new[6L] = false;
        data_mspw_new[5L] = false;
        data_mspw_new[4L] = false;
        data_mspw_new[3L] = false;
        data_mspw_new[2L] = false;
        data_mspw_new[1L] = false;
        data_mspw_new[0L] = false;
    }
    else if (ST_1 == state_sig_var)
    {
        hif_a2t_data.rdy = true;
        hif_a2t_data.sob_n = true;
        hif_a2t_data.irq_n = false;
        hif_a2t_data.nmi_n = false;
        hif_a2t_data.res_n = false;
    }
    else if (ST_2 == state_sig_var)
    {
        hif_a2t_data.res_n = false;
    }
    else if (ST_5 == state_sig_var)
    {
        hif_a2t_data.nmi_n = true;
    }
    else if (ST_11 == state_sig_var)
    {
        hif_a2t_data.nmi_n = false;
    }
    else if (ST_13 == state_sig_var)
    {
        hif_a2t_data.res_n = true;
    }
}


void memory::process_1()
{
    memory_addr = hif_a2t_data.addr & uint16_t(8191U);
    memory_addr_switch = static_cast< uint16_t >( hif_a2t_data.addr >> uint16_t
        (15U) ) & uint16_t(1U);
    if (!memory_addr_switch && !hif_a2t_data.we_n)
    {
        ram[static_cast< int32_t >( memory_addr )] = hif_a2t_data.datao;
    }
    else if (!memory_addr_switch && hif_a2t_data.we_n)
    {
        datai_mspw_new[7L] = static_cast< uint8_t >( ram[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(7U) ) & uint8_t(1U);
        datai_mspw_new[6L] = static_cast< uint8_t >( ram[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(6U) ) & uint8_t(1U);
        datai_mspw_new[5L] = static_cast< uint8_t >( ram[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(5U) ) & uint8_t(1U);
        datai_mspw_new[4L] = static_cast< uint8_t >( ram[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(4U) ) & uint8_t(1U);
        datai_mspw_new[3L] = static_cast< uint8_t >( ram[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(3U) ) & uint8_t(1U);
        datai_mspw_new[2L] = static_cast< uint8_t >( ram[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(2U) ) & uint8_t(1U);
        datai_mspw_new[1L] = static_cast< uint8_t >( ram[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(1U) ) & uint8_t(1U);
        datai_mspw_new[0L] = ram[static_cast< int32_t >( memory_addr )] & uint8_t
            (1U);
    }
    else if (memory_addr_switch && hif_a2t_data.we_n)
    {
        datai_mspw_new[7L] = static_cast< uint8_t >( rom[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(7U) ) & uint8_t(1U);
        datai_mspw_new[6L] = static_cast< uint8_t >( rom[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(6U) ) & uint8_t(1U);
        datai_mspw_new[5L] = static_cast< uint8_t >( rom[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(5U) ) & uint8_t(1U);
        datai_mspw_new[4L] = static_cast< uint8_t >( rom[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(4U) ) & uint8_t(1U);
        datai_mspw_new[3L] = static_cast< uint8_t >( rom[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(3U) ) & uint8_t(1U);
        datai_mspw_new[2L] = static_cast< uint8_t >( rom[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(2U) ) & uint8_t(1U);
        datai_mspw_new[1L] = static_cast< uint8_t >( rom[static_cast< int32_t >
            ( memory_addr )] >> uint8_t(1U) ) & uint8_t(1U);
        datai_mspw_new[0L] = rom[static_cast< int32_t >( memory_addr )] & uint8_t
            (1U);
    }
}


void memory::datai_mspw_proc_tgt()
{
    hif_a2t_data.datai = static_cast< uint8_t >( static_cast< uint8_t >( static_cast<
         uint8_t >( static_cast< uint8_t >( static_cast< uint8_t >( static_cast<
         uint8_t >( static_cast< uint8_t >( datai_mspw[1L] << uint8_t(1U) ) | static_cast<
         uint8_t >( datai_mspw[0L] ) ) | static_cast< uint8_t >( datai_mspw[2L]
         << uint8_t(2U) ) ) | static_cast< uint8_t >( datai_mspw[3L] << uint8_t
        (3U) ) ) | static_cast< uint8_t >( datai_mspw[4L] << uint8_t(4U) ) ) | static_cast<
         uint8_t >( datai_mspw[5L] << uint8_t(5U) ) ) | static_cast< uint8_t >(
         datai_mspw[6L] << uint8_t(6U) ) ) | static_cast< uint8_t >( datai_mspw
        [7L] << uint8_t(7U) );
}


void memory::data_mspw_proc_tgt()
{
    hif_a2t_data.data = static_cast< uint16_t >( static_cast< uint16_t >( static_cast<
         uint16_t >( static_cast< uint16_t >( static_cast< uint16_t >( static_cast<
         uint16_t >( static_cast< uint16_t >( static_cast< uint16_t >( static_cast<
         uint16_t >( static_cast< uint16_t >( static_cast< uint16_t >( static_cast<
         uint16_t >( static_cast< uint16_t >( static_cast< uint16_t >( static_cast<
         uint16_t >( data_mspw[1L] << uint16_t(1U) ) | static_cast< uint16_t >(
         data_mspw[0L] ) ) | static_cast< uint16_t >( data_mspw[2L] << uint16_t
        (2U) ) ) | static_cast< uint16_t >( data_mspw[3L] << uint16_t(3U) ) ) |
         static_cast< uint16_t >( data_mspw[4L] << uint16_t(4U) ) ) | static_cast<
         uint16_t >( data_mspw[5L] << uint16_t(5U) ) ) | static_cast< uint16_t >
        ( data_mspw[6L] << uint16_t(6U) ) ) | static_cast< uint16_t >( data_mspw
        [7L] << uint16_t(7U) ) ) | static_cast< uint16_t >( data_mspw[8L] << uint16_t
        (8U) ) ) | static_cast< uint16_t >( data_mspw[9L] << uint16_t(9U) ) ) |
         static_cast< uint16_t >( data_mspw[10L] << uint16_t(10U) ) ) | static_cast<
         uint16_t >( data_mspw[11L] << uint16_t(11U) ) ) | static_cast< uint16_t
         >( data_mspw[12L] << uint16_t(12U) ) ) | static_cast< uint16_t >( data_mspw
        [13L] << uint16_t(13U) ) ) | static_cast< uint16_t >( data_mspw[14L] <<
         uint16_t(14U) ) ) | static_cast< uint16_t >( data_mspw[15L] << uint16_t
        (15U) );
}


void memory::process_0_process_2()
{
    if (hif_a2t_data.rst == true)
    {
        state_sig_var = ST_START;
        state_new = state_sig_var;
    }
    else
    {
        if (ST_START == state_sig_var)
        {
            state_sig_var = ST_1;
            state_new = state_sig_var;
        }
        else if (ST_1 == state_sig_var)
        {
            state_sig_var = ST_2;
            state_new = state_sig_var;
        }
        else if (ST_2 == state_sig_var)
        {
            state_sig_var = ST_3;
            state_new = state_sig_var;
        }
        else if (ST_3 == state_sig_var)
        {
            state_sig_var = ST_4;
            state_new = state_sig_var;
        }
        else if (ST_4 == state_sig_var)
        {
            state_sig_var = ST_5;
            state_new = state_sig_var;
        }
        else if (ST_5 == state_sig_var)
        {
            state_sig_var = ST_6;
            state_new = state_sig_var;
        }
        else if (ST_6 == state_sig_var)
        {
            state_sig_var = ST_7;
            state_new = state_sig_var;
        }
        else if (ST_7 == state_sig_var)
        {
            state_sig_var = ST_8;
            state_new = state_sig_var;
        }
        else if (ST_8 == state_sig_var)
        {
            state_sig_var = ST_9;
            state_new = state_sig_var;
        }
        else if (ST_9 == state_sig_var)
        {
            state_sig_var = ST_10;
            state_new = state_sig_var;
        }
        else if (ST_10 == state_sig_var)
        {
            state_sig_var = ST_11;
            state_new = state_sig_var;
        }
        else if (ST_11 == state_sig_var)
        {
            state_sig_var = ST_12;
            state_new = state_sig_var;
        }
        else if (ST_12 == state_sig_var)
        {
            state_sig_var = ST_13;
            state_new = state_sig_var;
        }
        else if (ST_13 == state_sig_var || ST_15 == state_sig_var)
        {
            state_sig_var = ST_14;
            state_new = state_sig_var;
        }
        else if (ST_14 == state_sig_var)
        {
            state_sig_var = ST_15;
            state_new = state_sig_var;
        }
    }
    ram[ACCELEROMETER_HIGH_ADDRESS] = static_cast< uint16_t >( hif_a2t_data.accelerometer
         >> uint16_t(8U) ) & uint16_t(255U);
    ram[ACCELEROMETER_LOW_ADDRESS] = hif_a2t_data.accelerometer;
    hif_a2t_data.data_rdy = ram[DATA_RDY_ADDRESS] & uint8_t(1U);
    data_mspw_new[7L] = static_cast< uint8_t >( ram[DATA_LOW_ADDRESS] >> uint8_t
        (7U) ) & uint8_t(1U);
    data_mspw_new[6L] = static_cast< uint8_t >( ram[DATA_LOW_ADDRESS] >> uint8_t
        (6U) ) & uint8_t(1U);
    data_mspw_new[5L] = static_cast< uint8_t >( ram[DATA_LOW_ADDRESS] >> uint8_t
        (5U) ) & uint8_t(1U);
    data_mspw_new[4L] = static_cast< uint8_t >( ram[DATA_LOW_ADDRESS] >> uint8_t
        (4U) ) & uint8_t(1U);
    data_mspw_new[3L] = static_cast< uint8_t >( ram[DATA_LOW_ADDRESS] >> uint8_t
        (3U) ) & uint8_t(1U);
    data_mspw_new[2L] = static_cast< uint8_t >( ram[DATA_LOW_ADDRESS] >> uint8_t
        (2U) ) & uint8_t(1U);
    data_mspw_new[1L] = static_cast< uint8_t >( ram[DATA_LOW_ADDRESS] >> uint8_t
        (1U) ) & uint8_t(1U);
    data_mspw_new[0L] = ram[DATA_LOW_ADDRESS] & uint8_t(1U);
    data_mspw_new[15L] = static_cast< uint8_t >( ram[DATA_HIGH_ADDRESS] >> uint8_t
        (7U) ) & uint8_t(1U);
    data_mspw_new[14L] = static_cast< uint8_t >( ram[DATA_HIGH_ADDRESS] >> uint8_t
        (6U) ) & uint8_t(1U);
    data_mspw_new[13L] = static_cast< uint8_t >( ram[DATA_HIGH_ADDRESS] >> uint8_t
        (5U) ) & uint8_t(1U);
    data_mspw_new[12L] = static_cast< uint8_t >( ram[DATA_HIGH_ADDRESS] >> uint8_t
        (4U) ) & uint8_t(1U);
    data_mspw_new[11L] = static_cast< uint8_t >( ram[DATA_HIGH_ADDRESS] >> uint8_t
        (3U) ) & uint8_t(1U);
    data_mspw_new[10L] = static_cast< uint8_t >( ram[DATA_HIGH_ADDRESS] >> uint8_t
        (2U) ) & uint8_t(1U);
    data_mspw_new[9L] = static_cast< uint8_t >( ram[DATA_HIGH_ADDRESS] >> uint8_t
        (1U) ) & uint8_t(1U);
    data_mspw_new[8L] = ram[DATA_HIGH_ADDRESS] & uint8_t(1U);
    ram[RESULT_RDY_ADDRESS] = hif_a2t_data.result_rdy;
    ram[RESULT_HIGH_ADDRESS] = static_cast< uint16_t >( hif_a2t_data.result >> uint16_t
        (8U) ) & uint16_t(255U);
    ram[RESULT_LOW_ADDRESS] = hif_a2t_data.result;
}


void memory::update_input_queue( bool synch_phase )
{
    process_in_queue = false;
    if (hif_a2t_data.clk != clk_old)
    {
        clk_old = hif_a2t_data.clk;
        flag_clk = true;
        process_in_queue = true;
    }
    else
    {
        flag_clk = false;
    }
    rst_old = hif_a2t_data.rst;
    if (hif_a2t_data.addr != addr_old)
    {
        addr_old = hif_a2t_data.addr;
        flag_addr = true;
        process_in_queue = true;
    }
    else
    {
        flag_addr = false;
    }
    datao_old = hif_a2t_data.datao;
    vpab_old = hif_a2t_data.vpab;
    sync_old = hif_a2t_data.sync;
    we_n_old = hif_a2t_data.we_n;
    oeb_old = hif_a2t_data.oeb;
    accelerometer_old = hif_a2t_data.accelerometer;
    result_old = hif_a2t_data.result;
    result_rdy_old = hif_a2t_data.result_rdy;
}


void memory::update_event_queue()
{
    process_in_queue = false;
    if (!(data_mspw[0L] == data_mspw_new[0L] && data_mspw[1L] == data_mspw_new[1L
        ] && data_mspw[2L] == data_mspw_new[2L] && data_mspw[3L] == data_mspw_new
        [3L] && data_mspw[4L] == data_mspw_new[4L] && data_mspw[5L] == data_mspw_new
        [5L] && data_mspw[6L] == data_mspw_new[6L] && data_mspw[7L] == data_mspw_new
        [7L] && data_mspw[8L] == data_mspw_new[8L] && data_mspw[9L] == data_mspw_new
        [9L] && data_mspw[10L] == data_mspw_new[10L] && data_mspw[11L] == data_mspw_new
        [11L] && data_mspw[12L] == data_mspw_new[12L] && data_mspw[13L] == data_mspw_new
        [13L] && data_mspw[14L] == data_mspw_new[14L] && data_mspw[15L] == data_mspw_new
        [15L]))
    {
        data_mspw[15L] = data_mspw_new[15L];
        data_mspw[14L] = data_mspw_new[14L];
        data_mspw[13L] = data_mspw_new[13L];
        data_mspw[12L] = data_mspw_new[12L];
        data_mspw[11L] = data_mspw_new[11L];
        data_mspw[10L] = data_mspw_new[10L];
        data_mspw[9L] = data_mspw_new[9L];
        data_mspw[8L] = data_mspw_new[8L];
        data_mspw[7L] = data_mspw_new[7L];
        data_mspw[6L] = data_mspw_new[6L];
        data_mspw[5L] = data_mspw_new[5L];
        data_mspw[4L] = data_mspw_new[4L];
        data_mspw[3L] = data_mspw_new[3L];
        data_mspw[2L] = data_mspw_new[2L];
        data_mspw[1L] = data_mspw_new[1L];
        data_mspw[0L] = data_mspw_new[0L];
        flag_data_mspw = true;
        process_in_queue = true;
    }
    else
    {
        flag_data_mspw = false;
    }
    if (!(datai_mspw[0L] == datai_mspw_new[0L] && datai_mspw[1L] == datai_mspw_new
        [1L] && datai_mspw[2L] == datai_mspw_new[2L] && datai_mspw[3L] == datai_mspw_new
        [3L] && datai_mspw[4L] == datai_mspw_new[4L] && datai_mspw[5L] == datai_mspw_new
        [5L] && datai_mspw[6L] == datai_mspw_new[6L] && datai_mspw[7L] == datai_mspw_new
        [7L]))
    {
        datai_mspw[7L] = datai_mspw_new[7L];
        datai_mspw[6L] = datai_mspw_new[6L];
        datai_mspw[5L] = datai_mspw_new[5L];
        datai_mspw[4L] = datai_mspw_new[4L];
        datai_mspw[3L] = datai_mspw_new[3L];
        datai_mspw[2L] = datai_mspw_new[2L];
        datai_mspw[1L] = datai_mspw_new[1L];
        datai_mspw[0L] = datai_mspw_new[0L];
        flag_datai_mspw = true;
        process_in_queue = true;
    }
    else
    {
        flag_datai_mspw = false;
    }
    if (state != state_new)
    {
        state = state_new;
        flag_state = true;
        process_in_queue = true;
    }
    else
    {
        flag_state = false;
    }
}


void memory::flag_elaboration()
{
    flag_process_executed = false;
    if (flag_state)
    {
        process();
        flag_process_executed = true;
    }
    flag_process_1_executed = false;
    if (flag_clk || flag_addr)
    {
        process_1();
        flag_process_1_executed = true;
    }
    if (flag_datai_mspw)
    {
        datai_mspw_proc_tgt();
    }
    if (flag_data_mspw)
    {
        data_mspw_proc_tgt();
    }
    flag_process_0_process_2_executed = false;
    if (flag_clk)
    {
        process_0_process_2();
        flag_process_0_process_2_executed = true;
    }
}


void memory::synch_elaboration()
{
    update_input_queue( true );
    flag_elaboration();
    flag_clk = false;
    flag_addr = false;
    update_event_queue();
}


void memory::simulate( memory_iostruct * io_exchange, int32_t & cycles_number )
{
    hif_a2t_data.clk = io_exchange->clk;
    hif_a2t_data.rst = io_exchange->rst;
    hif_a2t_data.addr = io_exchange->addr;
    hif_a2t_data.datao = io_exchange->datao;
    hif_a2t_data.vpab = io_exchange->vpab;
    hif_a2t_data.sync = io_exchange->sync;
    hif_a2t_data.we_n = io_exchange->we_n;
    hif_a2t_data.oeb = io_exchange->oeb;
    hif_a2t_data.accelerometer = io_exchange->accelerometer;
    hif_a2t_data.result = io_exchange->result;
    hif_a2t_data.result_rdy = io_exchange->result_rdy;
    cycles_number = cycles_number + 1L;
    synch_elaboration();
    while (process_in_queue)
    {
        flag_elaboration();
        update_event_queue();
    }
    io_exchange->datai = hif_a2t_data.datai;
    io_exchange->irq_n = hif_a2t_data.irq_n;
    io_exchange->nmi_n = hif_a2t_data.nmi_n;
    io_exchange->sob_n = hif_a2t_data.sob_n;
    io_exchange->res_n = hif_a2t_data.res_n;
    io_exchange->rdy = hif_a2t_data.rdy;
    io_exchange->data = hif_a2t_data.data;
    io_exchange->data_rdy = hif_a2t_data.data_rdy;
}


void memory::start_of_simulation()
{
    initial_process();
    flag_initial_process_executed = true;
    process();
    flag_process_executed = true;
    process_1();
    flag_process_1_executed = true;
    datai_mspw_proc_tgt();
    data_mspw_proc_tgt();
    process_0_process_2();
    flag_process_0_process_2_executed = true;
    update_event_queue();
}


void memory::initialize()
{
    start_of_simulation();
}


void memory::finalize()
{
}




