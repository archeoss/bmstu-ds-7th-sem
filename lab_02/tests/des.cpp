#include "des.h"

TEST(DES, set1)
{
    sym_test<DES>(DES_NESSIE_SET_1);
}

TEST(DES, set2)
{
    sym_test<DES>(DES_NESSIE_SET_2);
}

TEST(DES, set3)
{
    sym_test<DES>(DES_NESSIE_SET_3);
}
