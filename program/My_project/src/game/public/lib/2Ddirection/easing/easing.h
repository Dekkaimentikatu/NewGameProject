#pragma once

class C_EASING
{
private:

	template<typename Ty>
	static constexpr Ty _0 = static_cast<Ty>(0);

	template<typename Ty>
	static constexpr Ty _1 = static_cast<Ty>(1);

	template<typename Ty>
	static constexpr Ty _2 = static_cast<Ty>(2);

public:



	template <typename Ty = float>
	[[nodiscard]] static inline Ty EasingInCubic(Ty time ,Ty total_time, Ty max = _1<Ty>, Ty min = _0<Ty>)
	{
		max -= min;
		time /= total_time;

		return max * time * time * time + min;
	}

	template<typename Ty = float>
	[[nodiscard]] static inline Ty InQuad(Ty time, Ty total_time, Ty max = _1<Ty>, Ty min = _0<Ty>)
	{
		max -= min;
		time /= total_time;

		return max * time * time + min;
	}

	template<typename Ty = float>
	[[nodiscard]] static inline Ty OutQuad(Ty time, Ty total_time, Ty max = _1<Ty>, Ty min = _0<Ty>)
	{
		max -= min;
		time /= total_time;

		return -max * time * (time - _2<Ty>) + min;
	}

	template<typename Ty = float>
	[[nodiscard]] static inline Ty InOutQuad(Ty time, Ty total_time, Ty max = _1<Ty>, Ty min = _0<Ty>)
	{
		max -= min;
		time /= total_time;

		if (time / _2<Ty> < _1<Ty>)
			return max / _2<Ty> *time * time + min;

		--time;

		return -max * (time * (time - _2<Ty>) - _1<Ty>) + min;
	}

};