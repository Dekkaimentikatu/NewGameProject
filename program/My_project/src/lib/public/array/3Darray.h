#pragma once
#include <vector>
#include <stdexcept>
#include <cstddef>

using namespace std;

template <typename T>
class C_3D_ARRAY 
{
public:

    // コンストラクタ
    C_3D_ARRAY(size_t x,
        size_t y,
        size_t z,
        const T& init = T())
        : x_(x),
        y_(y),
        z_(z),
        data_(x* y* z, init)
    {
    }

    //安全アクセス用制御
    T& at(size_t x,
        size_t y,
        size_t z)
    {
        //範囲チェック
        check_range(x, y, z);
        //要素を返す
        return data_[index(x, y, z)];
    }

    //const版安全アクセス用制御
    const T& at(size_t x,
        size_t y,
        size_t z) const
    {
        //範囲チェック
        check_range(x, y, z);
        //要素を返す
        return data_[index(x, y, z)];
    }

    //operator() でアクセス
    T& operator()(size_t x,
        size_t y,
        size_t z)
    {
        return at(x, y, z);
    }

    //const版operator()
    const T& operator()(size_t x,
        size_t y,
        size_t z) const
    {
        return at(x, y, z);
    }

    //サイズ取得
    size_t size_x() const { return x_; }
    size_t size_y() const { return y_; }
    size_t size_z() const { return z_; }

    //初期化
    void fill(const T& value)
    {
        fill(data_.begin(),
            data_.end(),
            value);
    }

    //サイズを変更
    void resize(std::size_t x,
        std::size_t y,
        std::size_t z)
    {
        x_ = x;
        y_ = y;
        z_ = z;

        data_.resize(x * y * z);
    }

    //生ポインタ取得
    T* data()
    {
        return data_.data();
    }

private:

    //配列の各次元の長さ
    size_t x_;
    size_t y_;
    size_t z_;

    //配列生成用の仮配列;
    vector<T> data_;

    //3次元から1次元に変換
    size_t index(size_t x,
        size_t y,
        size_t z) const
    {
        //3次元の座標を1次元の座標に変換
        return x * y_ * z_
            + y * z_
            + z;
    }

    //範囲チェック
    void check_range(size_t x,
        size_t y,
        size_t z) const
    {
        //範囲外かどうかチェック
        if (x >= x_ ||
            y >= y_ ||
            z >= z_)
        {
            //例外処理メッセージ
            throw out_of_range(
                "C_3D_ARRAY index out of range");
        }
    }
};