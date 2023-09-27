#include "customer_rule.h"
#include "customer_info.h"

/**
 * @brief Get the Purchase History object(値は適当)
 *
 * @return PurchaseHistory
 */
PurchaseHistory getPurchaseHistory0(void)
{
    // TODO 値をコンソールから入力
    PurchaseHistory purchaseHistory = {
                                     .productID=30,
                                     .totalAmount=1000,
                                     .perchaseFrequencyPerMonth=30,
                                     .returnRate=0
                                    };
    return purchaseHistory;
}

PurchaseHistory getPurchaseHistory1(void)
{
    // TODO 値をコンソールから入力
    PurchaseHistory purchaseHistory = {
                                     .productID=30,
                                     .totalAmount=1000,
                                     .perchaseFrequencyPerMonth=1,
                                     .returnRate=0
                                    };
    return purchaseHistory;
}

int main(void)
{
    CustomerInfo::Ptr customer_info_ptr(new CustomerInfo());
    // 顧客情報を取得
    PurchaseHistory purchase_history0 = getPurchaseHistory0();
    PurchaseHistory purchase_history1 = getPurchaseHistory1();
    // 顧客情報をリストに登録
    customer_info_ptr->registCustomer(purchase_history0);
    customer_info_ptr->registCustomer(purchase_history1);
    // 顧客が優良かどうかを判定
    customer_info_ptr->judgeCustomerRules(0);
    customer_info_ptr->judgeCustomerRules(1);
    return 0;
}
