#ifndef CUSTOMER_INFO_H
#define CUSTOMER_INFO_H

#include "customer_rule.h"
#include "map"

/**
 * @brief 顧客情報を管理するためのクラス
 *
 */
class CustomerInfo
{
public:
    using Ptr = std::shared_ptr<CustomerInfo>;
    /**
     * @brief コンストラクタ
     *
     */
    CustomerInfo()
        : ecp_ptr(new ExcellentCustomerPolicy())
    {
        registCustomerRules();
    }
    /**
     * @brief 新しい顧客情報を登録する
     *
     * @param purchaseHistory
     */
    void registCustomer(const PurchaseHistory purchaseHistory)
    {
        unsigned int id = 0;
        try{
            id = getNewCustomerID();
        }catch(std::range_error ex){
            std::cerr << ex.what() << std::endl;
            exit(1);
        }
        std::cout << "registed new customer " << id << std::endl;
        purchaseHistoryList[id] = purchaseHistory;
    }
    /**
     * @brief リストに登録されている顧客の数を取得する
     *
     * @return size_t
     */
    size_t getCustomerNum(void)
    {
        return purchaseHistoryList.size();
    }
    /**
     * @brief 顧客が優良かどうかを判定し結果を表示する
     *
     * @param customer_id
     */
    void judgeCustomerRules(const unsigned int customer_id)
    {
        if(!existsCustomer(customer_id)){
            throw std::range_error("[ERROR] customer not exists");
            std::cout << "hogehoge" << std::endl;
            return;
        }
        bool isGoodCustomer = ecp_ptr->complyWithAll(purchaseHistoryList[customer_id]);
        if(isGoodCustomer){
            std::cout << "Customer Id " << customer_id << " is Good Customer" << std::endl;
        }else{
            std::cout << "Customer Id " << customer_id << " is not Good Customer" << std::endl;
        }
    }
protected:
    /**
     * @brief 顧客が優良かを判定するためのルールを登録する
     *
     */
    void registCustomerRules()
    {
        ecp_ptr->add(std::move(std::unique_ptr<ExcellentCustomerRule>(new GoldCustomerPurchaseAmountRule())));
        ecp_ptr->add(std::move(std::unique_ptr<ExcellentCustomerRule>(new PurchaseFrequencyRule())));
        ecp_ptr->add(std::move(std::unique_ptr<ExcellentCustomerRule>(new ReturnRateRule())));
    }
    /**
     * @brief 新しい顧客IDを発行する
     *
     * @return unsigned int
     */
    unsigned int getNewCustomerID(void)
    {
        for(unsigned int i=0; i<MAX_CUSTOMER_NUM; i++)
        {
            if(purchaseHistoryList.count(i) == 0) return i;
        }
        throw std::range_error("[ERROR] customer list is full");
    }
    /**
     * @brief 顧客がリストに登録済みかどうかを判定する
     *
     * @param customer_id
     * @return true
     * @return false
     */
    bool existsCustomer(const unsigned int customer_id)
    {
        return purchaseHistoryList.count(customer_id) != 0;
    }

private:
    std::map<int, PurchaseHistory> purchaseHistoryList;
    ExcellentCustomerPolicy::Ptr ecp_ptr;
    static constexpr unsigned int MAX_CUSTOMER_NUM = 100;
};

#endif // CUSTOMER_INFO_H
