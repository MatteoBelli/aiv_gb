#include <aiv_unit_test.h>
#include <aiv_gb.h>

TEST(ld_sp_d16)
{
    printf("Stirlani");
    aiv_gameboy gb;

    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x31;
    gb.cartridge[1] = 0x01;
    gb.cartridge[2] = 0x02;
    aiv_gb_tick(&gb);
    ASSERT_THAT(gb.sp == 0x0201);
    ASSERT_THAT(gb.ticks == 12);
    ASSERT_THAT(gb.pc == 3);
}
TEST(inc_sp)
{
    printf("Stirlani");
    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x33;
    aiv_gb_tick(&gb);

    ASSERT_THAT(gb.sp == 1);
    ASSERT_THAT(gb.ticks == 8);
}
TEST(inc_HL_value)
{
    printf("Stirlani");

    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x34;
    gb.hl = 1;
    u8_t val = aiv_gb_memory_read8(&gb, gb.hl);

    aiv_gb_tick(&gb);

    u8_t val2 = aiv_gb_memory_read8(&gb, gb.hl);

    ASSERT_THAT(val < val2);
    ASSERT_THAT(gb.ticks == 12);
    u8_t flag = aiv_gb_get_flag(&gb, NEG);
    ASSERT_THAT(flag == 0);
}
TEST(inc_HL_value_zero)
{
    printf("Stirlani");

    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x34;
    gb.cartridge[1] = 0xff;
    gb.hl = 1;
    aiv_gb_tick(&gb);


    ASSERT_THAT(gb.ticks == 12);
    u8_t flag = aiv_gb_get_flag(&gb, ZERO);
    ASSERT_THAT(flag == 128);
}
TEST(inc_HL_value_half_zero)
{
    printf("Stirlani");

    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x34;
    gb.cartridge[1] = 0x0f;
    gb.hl = 1;
    aiv_gb_tick(&gb);


    ASSERT_THAT(gb.ticks == 12);
    u8_t flag = aiv_gb_get_flag(&gb, HALF);
    ASSERT_THAT(flag == 32);
}
TEST(dec_HL_value)
{
    printf("Stirlani");

    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x35;
    gb.cartridge[1] = 0x02;

    gb.hl = 1;
    u8_t val = aiv_gb_memory_read8(&gb, gb.hl);

    aiv_gb_tick(&gb);

    u8_t val2 = aiv_gb_memory_read8(&gb, gb.hl);
    printf("%i", val2);

    ASSERT_THAT(val > val2);
    ASSERT_THAT(gb.ticks == 12);
    u8_t flag = aiv_gb_get_flag(&gb, NEG);
    ASSERT_THAT(flag == 64);
}
TEST(dec_HL_value_zero)
{
    printf("Stirlani: ");

    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x35;
    gb.cartridge[1] = 0x01;

    gb.hl = 1;
    aiv_gb_tick(&gb);

    ASSERT_THAT(gb.ticks == 12);
    
    u8_t flag = aiv_gb_get_flag(&gb, ZERO);
    ASSERT_THAT(flag == 128);

}
TEST(dec_HL_value_half_zero)
{
    printf("Stirlani: ");

    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x35;
    gb.cartridge[1] = 0xaf;

    gb.hl = 1;
    aiv_gb_tick(&gb);

    ASSERT_THAT(gb.ticks == 12);
    
    u8_t flag = aiv_gb_get_flag(&gb, HALF);
    ASSERT_THAT(flag == 32);

}
TEST(jr)
{
    printf("Stirlani: ");
    aiv_gameboy gb;
    aiv_gb_init(&gb);

    gb.cartridge[0] = 0x30;
    gb.cartridge[1] = 0x01;
    gb.cartridge[2] = 0x02;
    aiv_gb_tick(&gb);
}
void aiv_gb_tests_run_opcodes_30()
{
    RUN_TEST(ld_sp_d16);
    RUN_TEST(inc_sp);
    RUN_TEST(inc_HL_value);
    RUN_TEST(inc_HL_value_zero);
    RUN_TEST(inc_HL_value_half_zero);
    RUN_TEST(dec_HL_value);
    RUN_TEST(dec_HL_value_zero);
    RUN_TEST(dec_HL_value_half_zero);
    RUN_TEST(jr);

}