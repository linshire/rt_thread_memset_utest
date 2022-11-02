/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-2      linshire   the first version
 */

#include <rtthread.h>
#include "utest.h"
#include <stdio.h>



/*TEST_SIZE_SPACE * sizeof(rt_base_t) chars*/

#define TEST_SIZE_SPACE 4

ALIGN(RT_ALIGN_SIZE)

static void test_memset_base(void)
{
    rt_uint8_t i = 0;
    rt_uint8_t result = 0;
    rt_base_t test_space[TEST_SIZE_SPACE];

    /*init test_space with filling 0*/
    for(i = 0; i < TEST_SIZE_SPACE * sizeof(rt_base_t); i++)
    {
        *((rt_uint8_t *)test_space + i) = 0x00;
    }

    /* fill with 1 using memset*/
    rt_memset(((rt_uint8_t *)test_space + 1), 0xff, sizeof(rt_base_t));

    /*result & every char which is in rt_base_t*/
    result = *((rt_uint8_t *)test_space + 1);

    uassert_int_equal(result, 0xff);

    for(i = 0; i < sizeof(rt_base_t); i++)
    {
    result &= *((rt_uint8_t *)test_space + 1 + i);
    uassert_int_equal(result, 0xff);
    }
    result &= 0xff;

    uassert_int_equal(result, 0xff);

    /*init result*/
    uassert_false(*(rt_uint8_t *)test_space);

    for(i =0; i < (TEST_SIZE_SPACE - 1) * sizeof(rt_base_t) - 1;i++ )

        uassert_false(*((rt_uint8_t *)test_space + sizeof(rt_base_t) + 1 + i));

}

// static void test_memset_uint8(void)
// {
//     rt_uint8_t i = 0;
//     rt_uint8_t result = 0;
//     rt_base_t test_space[TEST_SIZE_SPACE] = {0};
//     /* fill with 1 */
//     rt_memset((rt_uint8_t *)test_space + 1, 0xff, sizeof(rt_base_t));

//     result = *((rt_uint8_t *)test_space + 1);

//     for(i = 0; i < sizeof(rt_base_t); i++)
//     {
//     result &= *((rt_uint8_t *)test_space + 2 + i);
//     }
//     result &= 0xff;

//     uassert_int_equal(result, 0xff);
// }


static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(test_memset_base);
}
UTEST_TC_EXPORT(testcase, "NOT ALIGN(RT_ALIGN_SIZE) test", utest_tc_init, utest_tc_cleanup, 10);