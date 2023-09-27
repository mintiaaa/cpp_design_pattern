#ifndef MAGIC_H
#define MAGIC_H

#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <iostream>

enum MagicType
{
    fire,
    shiden,
    hellFire
};

/**
 * @brief 魔法使用者のパラメータ
 *
 */
class Member
{
public:
    // TODO 各変数をintではなく値オブジェクトにする
    int level;
    int agility;
    int vitality;
    int magicAttack;
};


/**
 * @brief 魔法に関するパラメータを管理するためのクラス
 *
 */
class Magic
{
public:
    Magic(const MagicType magicType, const Member member)
    {
        switch(magicType)
        {
            // switch文を複数個所に記載せず一か所に集約
            // 本当はインターフェースにするべき
            case fire:
                name = "ファイア";
                costMagicPoint = 2;
                attackPower = 20 * static_cast<int>(member.level * 0.5);
                costTechnicalPoint = 0;
                break;
            case shiden:
                name = "紫電";
                costMagicPoint = 5 + static_cast<int>(member.level * 0.2);
                attackPower = 50 + static_cast<int>(member.level * 1.5);
                costTechnicalPoint = 5;
                break;
            case hellFire:
                name = "地獄の業火";
                costMagicPoint = 16;
                attackPower = 200 + static_cast<int>(member.level * 0.5 + member.vitality * 0.2);
                costTechnicalPoint = 20 + static_cast<int>(member.level * 0.4);
                break;
            default:
                throw std::invalid_argument("[Error] Failed to generate magic");
        }
    }
private:
    std::string name;
    int costMagicPoint;     // 魔法を唱えるのに必要なマジックポイント
    int attackPower;        // 魔法の攻撃力
    int costTechnicalPoint; // 魔法を唱えるのに必要な技術力
};

/**
 * @brief インターフェースを活用する場合の実装
 *
 */
class MagicForInterface
{
public:
    virtual std::string name() = 0;
    virtual int costMagicPoint() = 0;
};

/**
 * @brief 魔法(Fire)クラス,　Interfaceを継承
 *
 */
class Fire : public MagicForInterface
{
public:
    Fire(const Member member)
    {
        this->member = member;
    }

    std::string name() override
    {
        return "ファイア";
    }
    // TODO 値オブジェクトにする
    int costMagicPoint() override
    {
        return 2;
    }
private:
    Member member;
};

/**
 * @brief 魔法(Shiden)クラス,　Interfaceを継承
 *
 */
class Shiden : public MagicForInterface
{
public:
    Shiden(const Member member)
    {
        this->member = member;
    }

    std::string name() override
    {
        return "紫電";
    }
    // TODO 値オブジェクトにする
    int costMagicPoint() override
    {
        return 5;
    }
private:
    Member member;
};


void howToUse()
{
    // 使い方
    // memberの値セット
    Member member = {};
    // 組み込み型以外はスマポを配列にできない(はず)
    std::vector<std::unique_ptr<MagicForInterface>> magicList;

    std::unique_ptr<Fire> fire(new Fire(member));
    std::unique_ptr<Shiden> shiden(new Shiden(member));
    magicList.push_back(std::move(fire));
    magicList.push_back(std::move(shiden));

    // リスコフの置換原則: インターフェースを継承したインスタンスの種類によって処理を変えてはならない(分岐してはいけない)
    for(const auto& magic_ptr: magicList)
    {
        std::cout << "Magic Name: " << magic_ptr->name() << std::endl;
    }

}



#endif // MAGIC_H
