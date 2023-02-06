#include <gtest/gtest.h>
#include "Invoice.h"

TEST(InvoiceUnitTest, basicConstructor){
    Currency cur(100, 50);
    Invoice invoice("1", cur, 18);
    ASSERT_EQ(invoice.getName(), "1");
    ASSERT_EQ(invoice.getNetAmount(), cur);
    EXPECT_NEAR(invoice.getVatRate(), 0.18, 0.01);
}

TEST(InvoiceUnitTest, calculateVat){
    Currency cur(10000, 0);
    Invoice invoice("1", cur, 18);
    Currency calculatedVat = invoice.calculateVat();
    Currency result(1800, 0);
    ASSERT_TRUE(calculatedVat == result);
}