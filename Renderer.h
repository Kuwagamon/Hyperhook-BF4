#pragma once
#include <Windows.h>
#include <vector>
#include <array>
#include "imgui.h"

//Ah yes, good old Renderer class that was writen for CSGO ISurface interface then recoded as (mostly) imgui wrapper..

enum StringFlag;
enum class StringStyle;
class BoundingBox;

class Renderer
{
public:
	static void DrawStringDbg(const ImVec2& min, bool center, const char* msg, ...);
	static void DrawString(const ImVec2& min, DWORD stringFlag, const ImColor & color , const char* msg, ...);
	static void DrawRectFilled(const ImVec2& vLT, const ImVec2& vRB, const ImColor& col);
	static void DrawRectFilled(const BoundingBox& bb, const ImColor& col);
	static void DrawRectGradient(const ImVec2& min, const ImVec2& max, const ImColor& leftTop, const ImColor& rightTop, const ImColor& leftBot, const ImColor& rightBot);
	static void DrawRectGradient(const BoundingBox& bb, const ImColor& leftTop, const ImColor& rightTop, const ImColor& leftBot, const ImColor& rightBot);
	static void DrawRoundedRectFilled(const ImVec2& min, const ImVec2& max, float rnd, const ImColor& col);
	static void DrawRoundedRectFilled(const BoundingBox& bb, float rnd, const ImColor& col);
	static void DrawRoundedRect(const ImVec2& min, const ImVec2& max, float rnd, const ImColor& col);
	static void DrawRoundedRect(const BoundingBox& bb, float rnd, const ImColor& col);
	static void DrawRect(const ImVec2& min, const ImVec2& max, const ImColor& col);
	static void DrawRect(const BoundingBox& bb, const ImColor& col);
	static void DrawRectOutlined(const ImVec2& min, const ImVec2& max, const ImColor& col, const ImColor& outline = ImColor::Black());
	static void DrawRectOutlined(const BoundingBox& bb, const ImColor& col, const ImColor& outline = ImColor::Black());
	static void DrawCircle(const ImVec2& pos, float rad, float step, const ImColor& color);
	static void DrawCircleFilled(const ImVec2& pos, float rad, float step, const ImColor& Color );
	static void DrawCircleOutlined(const ImVec2& pos, int rad, int seg, const ImColor& col);
	static void DrawCircleProgressBar(const ImVec2& pos, int rad, int seg, float value, float maxValue, const ImColor& color, float thickness = 1.0f, bool outline = false, ImVec2* lastPointsOut = nullptr);
	static void DrawLine(const ImVec2& pos1, const ImVec2& pos2, const ImColor& col);
	static void DrawLine(const BoundingBox& bb, const ImColor& col);
	static void DrawLine(const std::vector<ImVec2>& points, const ImColor& col);
	static void DrawTriangleFilled(const std::array<ImVec2, 3>& points, const ImColor& color );
	static void DrawTriangle(const std::array<ImVec2, 3>& points, const ImColor& color );
	static void DrawCountingBar(const ImVec2& center, const ImVec2& size, float value, float maxValue, const ImColor& color = ImColor(0, 128, 255, 144));
	static void DrawProgressBar(const ImVec2& center, const ImVec2& size, float value, float maxValue, const ImColor& color = ImColor(0, 128, 255, 144));
	static void DrawImageRotated(ImTextureID tex_id, const ImVec2& center, const ImVec2& size, float angle, const ImColor& color);
	static void DrawSpeedometer(const ImVec2& pos, float scale, float min, float max, float value);

	static ImVec2 GetTextSize(const char* msg, ...);
	static ImVec2 GetCursorPos();

	//    1--------2
	//   /|       /|
	//  / |      / |
	// 5--------4  |
	// |  |	    |  |
	// |  0-----|--3 
	// | /      | / 
	// |/       |/
	// 6--------7		
	static void DrawBox(const std::array<ImVec2, 8>& points, const ImColor& color);

	//broken for now
	static void DrawBox(const ImVec2& center, const ImVec2& size, float angle, const ImColor& color);
};

enum StringFlag
{
	NONE = 0,
	CENTER_X = 1 << 1,
	RIGHT_X = 1 << 2,
	TOP_Y = 1 << 3,
	CENTER_Y = 1 << 4,
};

enum class StringStyle
{
	RECT						= 0,
	RECT_FILLED					= 1,
	RECT_FILLED_BORDER			= 2,
	ROUNDED_RECT				= 3,
	ROUNDED_RECT_FILLED			= 4,
	ROUNDED_RECT_FILLED_BORDER	= 5,
};

class BoundingBox
{
public:
	float left, top, right, bot;

	BoundingBox() : left(0.f), top(0.f), right(0.f), bot(0.f) {};
	BoundingBox(const float left, const float top, const float right, const float bot);
	BoundingBox(const ImVec2& min, const ImVec2& max);

	static BoundingBox Zero();

	const BoundingBox& operator=(const BoundingBox& rhs)
	{
		left = rhs.left;
		top = rhs.top;
		right = rhs.right;
		bot = rhs.bot;
		return *this;
	}
	const BoundingBox& operator=(const float v)
	{
		left = v;
		top = v;
		right = v;
		bot = v;
		return *this;
	}
	constexpr bool operator==(const BoundingBox& rhs) const
	{
		return (
			this->left == rhs.left
			&& this->top == rhs.top
			&& this->right == rhs.right
			&& this->bot == rhs.bot);
	}
	constexpr bool operator==(const float v) const
	{
		return (
			this->left == v
			&& this->top == v
			&& this->right == v
			&& this->bot == v);
	}
	constexpr bool operator!=(const BoundingBox& rhs) const
	{
		return (
			this->left != rhs.left
			&& this->top != rhs.top
			&& this->right != rhs.right
			&& this->bot != rhs.bot);
	}
	constexpr bool operator!=(const float v) const
	{
		return (
			this->left != v
			&& this->top != v
			&& this->right != v
			&& this->bot != v);
	}

	const BoundingBox operator+(const BoundingBox& rhs) const
	{
		return BoundingBox(
			this->left + rhs.left,
			this->top + rhs.top,
			this->right + rhs.right,
			this->bot + rhs.bot);
	}
	const BoundingBox operator-(const BoundingBox& rhs) const
	{
		return BoundingBox(
			this->left - rhs.left,
			this->top - rhs.top,
			this->right - rhs.right,
			this->bot - rhs.bot);
	}
	const BoundingBox operator*(const BoundingBox& rhs) const
	{
		return BoundingBox(
			this->left * rhs.left,
			this->top * rhs.top,
			this->right * rhs.right,
			this->bot * rhs.bot);
	}
	const BoundingBox operator/(const BoundingBox& rhs)
	{
		return rhs != 0.f ?
			BoundingBox(
				this->left / rhs.left,
				this->top / rhs.top,
				this->right / rhs.right,
				this->bot / rhs.bot) : *this = -1.f;
	}

	const BoundingBox& operator+=(const BoundingBox& rhs)
	{
		left += rhs.left;
		top += rhs.top;
		right += rhs.right;
		bot += rhs.bot;
		return *this;
	}
	const BoundingBox& operator-=(const BoundingBox& rhs)
	{
		left -= rhs.left;
		top -= rhs.top;
		right -= rhs.right;
		bot -= rhs.bot;
		return *this;
	}
	const BoundingBox& operator*=(const BoundingBox& rhs)
	{
		left *= rhs.left;
		top *= rhs.top;
		right *= rhs.right;
		bot *= rhs.bot;
		return *this;
	}
	const BoundingBox& operator/=(const BoundingBox& rhs)
	{
		if (rhs != 0.f)
		{
			left /= rhs.left;
			top /= rhs.top;
			right /= rhs.right;
			bot /= rhs.bot;
		}
		else *this = -1.f;
		return *this;
	}

	const BoundingBox operator+(const float v) const
	{
		return BoundingBox(
			this->left + v,
			this->top + v,
			this->right + v,
			this->bot + v);
	}
	const BoundingBox operator-(const float v) const
	{
		return BoundingBox(
			this->left - v,
			this->top - v,
			this->right - v,
			this->bot - v);
	}
	const BoundingBox operator*(const float v) const
	{
		return BoundingBox(
			this->left * v,
			this->top * v,
			this->right * v,
			this->bot * v);
	}
	const BoundingBox operator/(const float v)
	{
		return v != 0.f ?
			BoundingBox(
				this->left / v,
				this->top / v,
				this->right / v,
				this->bot / v) : *this = -1.f;
	}

	const BoundingBox& operator+=(const float v)
	{
		left += v;
		top += v;
		right += v;
		bot += v;
		return *this;
	}
	const BoundingBox& operator-=(const float v)
	{
		left -= v;
		top -= v;
		right -= v;
		bot -= v;
		return *this;
	}
	const BoundingBox& operator*=(const float v)
	{
		left *= v;
		top *= v;
		right *= v;
		bot *= v;
		return *this;
	}
	const BoundingBox& operator/=(const float v)
	{
		if (v != 0.f)
		{
			left /= v;
			top /= v;
			right /= v;
			bot /= v;
		}
		else *this = -1.f;
		return *this;
	}

public:
	ImVec2		GetMin() const;
	ImVec2		GetMax() const;
	ImVec2		GetMinBot() const;
	ImVec2		GetMaxTop() const;
	ImVec2		GetSize() const;
	ImVec2		GetCenter() const;

	bool		IsValid() const;
};