/*
    ストラテジパターン確認用
    Context: Car
    Strategy: BrakeInterface
    ConcreateStrategy: Brake, BrakeWithABS
*/

#ifndef BRAKE_H
#define BRAKE_H

#include <memory>
#include <iostream>

/**
 * @brief ストラテジ
 *
 */
class BrakeInterface
{
public:
    // 引数無しのコンストラクタを削除
    BrakeInterface() = delete;
    BrakeInterface(const int offset)
        : output(0)
    {
        this->offset = offset;
    }
    // 仮想関数
    virtual ~BrakeInterface() = default;
    virtual void apply(void) = 0;
protected:
    // 値オブジェクトにしても良いかも？
    int output;
    int offset;
    // c++17以前はｎインターフェースconstexprにinlineが無いとエラーになる
    inline static constexpr int MAX_OUTPUT = 1000;
};

/**
 * @brief ConcreateStrategy1
 *
 */
class NormalBrake : public BrakeInterface
{
public:
    NormalBrake() = delete;
    // 基底クラスのコンストラクタ呼び出し
    NormalBrake(const int offset) : BrakeInterface::BrakeInterface(offset){}
    // brake出力最大
    void apply(void) override
    {
        output = std::max(0, std::min(MAX_OUTPUT, BRAKE_VALUE + offset));
        std::cout << "normal brake is applied" << std::endl;
        std::cout << "output = " << output << std::endl;
    }
private:
    static constexpr int BRAKE_VALUE = 300;

};

/**
 * @brief ConcreateStrategy2
 *
 */
class BrakeWithABS : public BrakeInterface
{
public:
    BrakeWithABS() = delete;
    // 基底クラスのコンストラクタ呼び出し
    BrakeWithABS(const int offset) : BrakeInterface::BrakeInterface(offset){}
    // brake出力最大
    void apply(void) override
    {
        output = std::max(0, std::min(MAX_OUTPUT, BRAKE_VALUE + offset));
        std::cout << "ABS brake is applied!!" << std::endl;
        std::cout << "output = " << output << std::endl;
    }
private:
    static constexpr int BRAKE_VALUE = 500;

};

/**
 * @brief Context
 *
 */
class Car
{
public:
    // 引数無しのコンストラクタは使わない
    Car() = delete;
    template <typename brakeT>
    Car(brakeT* brake): brake(std::make_unique<brakeT>(*brake)){};
    // ストラテジの関数を呼び出す。実装はConcreteStorategyに定義（隠蔽）
    void applyBrake(void)
    {
        brake->apply();
    }
private:
    // interfaceをメンバにするときはオブジェクトにはできない
    std::unique_ptr<BrakeInterface> brake;
    // accelなどもstrategyにして所持すると良い
};



#endif // BRAKE_H
