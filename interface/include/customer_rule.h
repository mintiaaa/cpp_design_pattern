#ifndef CUSTOMER_RULE_H
#define CUSTOMER_RULE_H

#include <deque>
#include <iostream>
#include <memory>

/**
 * @brief 顧客情報
 *
 */
class PurchaseHistory
{
public:
    int productID;
    int totalAmount;
    int perchaseFrequencyPerMonth;
    float returnRate;
};

/**
 * @brief 顧客ルールを表現するための基底クラス
 *
 */
class ExcellentCustomerRule
{
public:
    virtual bool ok(const PurchaseHistory history) const = 0;
};

/**
 * @brief 購入数のルールを表現するための派生クラス
 *
 */
class GoldCustomerPurchaseAmountRule : public ExcellentCustomerRule
{
public:
    bool ok(const PurchaseHistory history) const override
    {
        return history.totalAmount > totalAmount;
    }
private:
    static constexpr int totalAmount = 100;
};

/**
 * @brief 購入頻度のルールを表現するための派生クラス
 *
 */
class PurchaseFrequencyRule : public ExcellentCustomerRule
{
    bool ok(const PurchaseHistory history) const override
    {
        return history.perchaseFrequencyPerMonth > purchaseFrecuencyPerMonth;
    }
private:
    static constexpr int purchaseFrecuencyPerMonth = 10;
};

/**
 * @brief 返品率のルールを表現するための派生クラス
 *
 */
class ReturnRateRule : public ExcellentCustomerRule
{
    bool ok(const PurchaseHistory history) const override
    {
        return history.returnRate < returnRate;
    }
private:
    static constexpr float returnRate = 0.001;
};

/**
 * @brief 優良顧客の方針(Policy)を表現するためのクラス
 *        条件を部品化しポリシーパターンでルールを構造化
 *
 */
class ExcellentCustomerPolicy
{
public:
    using Ptr = std::shared_ptr<ExcellentCustomerPolicy>;
    ExcellentCustomerPolicy()
    {
    }
    /**
     * @brief ポリシーにルールを追加する
     *
     * @param rule : 顧客の階級を決めるためのルール（派生クラスを渡すことを前提としている)
     */
    void add(std::unique_ptr<ExcellentCustomerRule> rule)
    {
        rules.emplace_back(std::move(rule));
    }

    /**
     * @brief ポリシーが全てのルールを満たしているか判定する
     *
     * @param history
     * @return true
     * @return false
     */
    bool complyWithAll(const PurchaseHistory history)
    {
        for(const auto& rule : rules){
            if(!rule->ok(history)){
                return false;
            }
        }
        return true;
    }
private:
    std::deque<std::unique_ptr<ExcellentCustomerRule>> rules;
};

#endif // CUSTOMER_RULE_H
