#pragma once
#include <vector>
#include <stdexcept>
#include <cstddef>

using namespace std;

//3次元配列管理用のラッププログラム
template <typename T>
class C_3D_ARRAY 
{
public:

    //イテレーター型を定義
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;


    // コンストラクタ
    C_3D_ARRAY(size_t x,
        size_t y,
        size_t z,
        const T& init = T())
        : m_x(x),
        m_y(y),
        m_z(z),
        m_data(x* y* z, init)
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
        return m_data[index(x, y, z)];
    }

    //const版安全アクセス用制御
    const T& at(size_t x,
        size_t y,
        size_t z) const
    {
        //範囲チェック
        check_range(x, y, z);
        //要素を返す
        return m_data[index(x, y, z)];
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
    size_t size_x() const { return m_x; }
    size_t size_y() const { return m_y; }
    size_t size_z() const { return m_z; }

    //初期化
    void fill(const T& value)
    {
        fill(m_data.begin(),
            m_data.end(),
            value);
    }

    //サイズを変更
    void resize(std::size_t x,
        std::size_t y,
        std::size_t z)
    {
        m_x = x;
        m_y = y;
        m_z = z;

        m_data.resize(x * y * z);
    }

    //生ポインタ取得
    T* data()
    {
        return m_data.data();
    }

    //イテレーターをラップ
    iterator begin() { return m_data.begin(); }
    iterator end() { return m_data.end(); }

    const_iterator begin() const { return m_data.begin(); }
    const_iterator end() const { return m_data.end(); }

    const_iterator cbegin() const { return m_data.cbegin(); }
    const_iterator cend() const { return m_data.cend(); }

private:

    //配列の各次元の長さ
    size_t m_x;
    size_t m_y;
    size_t m_z;

    //配列
    vector<T> m_data;

    //3次元から1次元に変換
    size_t index(size_t x,
        size_t y,
        size_t z) const
    {
        //3次元の座標を1次元の座標に変換
        return x * m_y * m_z
            + y * m_z
            + z;
    }

    //範囲チェック
    void check_range(size_t x,
        size_t y,
        size_t z) const
    {
        //範囲外かどうかチェック
        if (x >= m_x ||
            y >= m_y ||
            z >= m_z)
        {
            //例外処理メッセージ
            throw out_of_range(
                "C_3D_ARRAY index out of range");
        }
    }
};