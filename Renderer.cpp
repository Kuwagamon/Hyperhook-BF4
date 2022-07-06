#include "stdafx.h"
#include "Renderer.h"
#include "Globals.h"
#include "MenuBackground.h"
#include <array>
#include <algorithm>
#include <D3D11.h>
#include <D3DX11tex.h>

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{
	return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

void Renderer::DrawStringDbg(const ImVec2& min, bool center, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);

	ImVec2 vSize = ImGui::CalcTextSize(buf);
	ImVec2 vMin = min;

	if (center)
	{
		vMin.x -= vSize.x * 0.5f;
		vMin.y -= vSize.y * 0.5f;
	}

	ImGui::GetBackgroundDrawList()->AddText(vMin, ImColor(255, 255, 255), buf);
}

void Renderer::DrawString(const ImVec2& min, DWORD stringFlag, const ImColor& color , const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);

	ImVec2 vSize = ImGui::CalcTextSize(buf);
	ImVec2 vMin = min;

	//Position adjusting
	if (stringFlag & StringFlag::CENTER_X)
		vMin.x -= vSize.x * 0.5f;
	if (stringFlag & StringFlag::CENTER_Y)
		vMin.y -= vSize.y * 0.5f;
	if (stringFlag & StringFlag::TOP_Y)
		vMin.y -= vSize.y;
	if (stringFlag & StringFlag::RIGHT_X)
		vMin.x -= vSize.x;

	ImGui::GetBackgroundDrawList()->AddText(ImVec2(vMin.x + 1, vMin.y), ImColor(0.1f, 0.1f, 0.1f), buf);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(vMin.x - 1, vMin.y), ImColor(0.1f, 0.1f, 0.1f), buf);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(vMin.x, vMin.y + 1), ImColor(0.1f, 0.1f, 0.1f), buf);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(vMin.x, vMin.y - 1), ImColor(0.1f, 0.1f, 0.1f), buf);

	ImGui::GetBackgroundDrawList()->AddText(vMin, ImColor(color), buf);
}

void Renderer::DrawRectFilled(const ImVec2& vLT, const ImVec2& vRB, const ImColor& col)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(vLT, vRB, ImColor(col));
}

void Renderer::DrawRectFilled(const BoundingBox& bb, const ImColor& col)
{
	DrawRectFilled(ImVec2(bb.left, bb.top), ImVec2(bb.right, bb.bot), col);
}

void Renderer::DrawRectGradient(const ImVec2& min, const ImVec2& max, const ImColor& leftTop, const ImColor& rightTop, const ImColor& leftBot, const ImColor& rightBot)
{
	ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(min, max, (leftTop), (rightTop), (rightBot), (leftBot));
}

void Renderer::DrawRectGradient(const BoundingBox& bb, const ImColor& leftTop, const ImColor& rightTop, const ImColor& leftBot, const ImColor& rightBot)
{
	DrawRectGradient(bb.GetMin(), bb.GetMax(), leftTop, rightTop, leftBot, rightBot);
}

void Renderer::DrawRoundedRectFilled(const ImVec2& min, const ImVec2& max, float rnd, const ImColor& col)
{
	ImGui::GetBackgroundDrawList()->AddRectFilled(min, max, rnd, (col));
}

void Renderer::DrawRoundedRectFilled(const BoundingBox& bb, float rnd, const ImColor& col)
{
	DrawRoundedRectFilled(bb.GetMin(), bb.GetMax(), rnd, col);
}

void Renderer::DrawRoundedRect(const ImVec2& min, const ImVec2& max, float rnd, const ImColor& col)
{
	ImGui::GetBackgroundDrawList()->AddRect(min, max, (col), rnd);
}

void Renderer::DrawRoundedRect(const BoundingBox& bb, float rnd, const ImColor& col)
{
	DrawRoundedRect(bb.GetMin(), bb.GetMax(), rnd, col);
}

void Renderer::DrawRect(const ImVec2& min, const ImVec2& max, const ImColor& col)
{
	ImGui::GetBackgroundDrawList()->AddRect(min, max, (col));
}

void Renderer::DrawRect(const BoundingBox& bb, const ImColor& col)
{
	DrawRect(bb.GetMin(), bb.GetMax(), col);
}

void Renderer::DrawRectOutlined(const ImVec2& min, const ImVec2& max, const ImColor& col, const ImColor& outline)
{
	DrawRect(ImVec2(min.x - 1, min.y - 1), ImVec2(max.x + 1, max.y + 1), outline);
	DrawRect(ImVec2(min.x + 1, min.y + 1), ImVec2(max.x - 1, max.y - 1), outline);
	DrawRect(min, max, col);
}

void Renderer::DrawRectOutlined(const BoundingBox& bb, const ImColor& col, const ImColor& outline)
{
	DrawRectOutlined(ImVec2(bb.left, bb.top), ImVec2(bb.right, bb.bot), col, outline);
}

void Renderer::DrawCircleOutlined(const ImVec2& pos, int rad, int seg, const ImColor& col)
{
	ImGui::GetBackgroundDrawList()->AddCircle(pos, rad - 1, (ImColor::Black(col.Value.w * 255)));
	ImGui::GetBackgroundDrawList()->AddCircle(pos, rad + 1, (ImColor::Black(col.Value.w * 255)));
	ImGui::GetBackgroundDrawList()->AddCircle(pos, rad, (col));
}

void Renderer::DrawCircleProgressBar(const ImVec2& pos, int rad, int seg, float value, float maxValue, const ImColor& color, float thickness, bool outline, ImVec2* lastPointsOut)
{
	if (outline)
		ImGui::GetBackgroundDrawList()->AddCircleProgress(pos, rad, seg, value, maxValue, ImColor::Black(color.Value.w * 255), thickness + 2.0f);
	ImGui::GetBackgroundDrawList()->AddCircleProgress(pos, rad, seg, value, maxValue, color, thickness, lastPointsOut);
}

void Renderer::DrawLine(const ImVec2& pos1, const ImVec2& pos2, const ImColor& col)
{
	ImGui::GetBackgroundDrawList()->AddLine(pos1, pos2, (col));
}

void Renderer::DrawLine(const BoundingBox& bb, const ImColor& col)
{
	DrawLine(bb.GetMin(), bb.GetMax(), col);
}

void Renderer::DrawLine(const std::vector<ImVec2>& points, const ImColor& col)
{
	if (points.size() < 2) return;

	ImGui::GetBackgroundDrawList()->AddPolyline(points.data(), points.size(), (col), false, 1.f);
}

void Renderer::DrawTriangleFilled(const std::array<ImVec2, 3>& points, const ImColor& color )
{
	ImGui::GetBackgroundDrawList()->AddTriangleFilled(points[0], points[1], points[2], (color));
}

void Renderer::DrawTriangle(const std::array<ImVec2, 3>& points, const ImColor& color )
{
	ImGui::GetBackgroundDrawList()->AddTriangle(points[0], points[1], points[2], (color));
}

void Renderer::DrawCountingBar(const ImVec2& center, const ImVec2& size, float value, float maxValue, const ImColor& color )
{
	if (maxValue <= 0 || maxValue <= value) return;
	float lenght = (value * size.x) / maxValue;

	if (lenght > 2)
	{
		//BG
		ImGui::GetForegroundDrawList()->AddRectFilled(
			ImVec2(center.x - size.x / 2, center.y),
			ImVec2(center.x + size.x / 2, center.y + size.y),
			2, ImColor::Black(190));

		//Bar
		ImGui::GetForegroundDrawList()->AddRectFilled(
			ImVec2((center.x - size.x / 2) + 2, (center.y) + 2),
			ImVec2(((center.x - size.x / 2) + 2) + (lenght - 2), (center.y + size.y) - 2),
			2, color);
	}
}

void Renderer::DrawProgressBar(const ImVec2& center, const ImVec2& size, float value, float maxValue, const ImColor& color)
{
	if (maxValue <= 0 || maxValue <= value) return;

	auto lenght = (value * size.x) / maxValue - 2.f;
	auto bb = BoundingBox(ImVec2(center.x - (size.x / 2), center.y), ImVec2(center.x + (size.x / 2), center.y + size.y));
	lenght = std::clamp(lenght, 0.0f, bb.GetSize().x);

	//BG
	DrawRectFilled(bb.GetMin(), bb.GetMax(), ImColor::Black(190));

	//Bar
	DrawRectFilled(
		ImVec2(bb.GetMin().x + 2, center.y + 2), 
		ImVec2(bb.GetMin().x + (lenght + 2), bb.GetMax().y - 2),
		color);
}

void Renderer::DrawImageRotated(ImTextureID tex_id, const ImVec2& center, const ImVec2& size, float angle, const ImColor& color)
{
	auto ImRotate = [](const ImVec2& v, float cos_a, float sin_a) -> ImVec2
	{
		return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
	};

	float cos_a = cosf(angle);
	float sin_a = sinf(angle);
	ImVec2 pos[4] =
	{
		center + ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
		center + ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
		center + ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
		center + ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
	};
	ImVec2 uvs[4] =
	{
		ImVec2(0.0f, 0.0f),
		ImVec2(1.0f, 0.0f),
		ImVec2(1.0f, 1.0f),
		ImVec2(0.0f, 1.0f)
	};

	ImGui::GetBackgroundDrawList()->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3], uvs[0], uvs[1], uvs[2], uvs[3], color);
}

void Renderer::DrawSpeedometer(const ImVec2& pos, float scale, float min, float max, float value)
{
	//That could be improved in many ways...
	static ID3D11ShaderResourceView* pSpeedometer = nullptr;
	static ID3D11ShaderResourceView* pArrow = nullptr;
	if (!pArrow) D3DX11CreateShaderResourceViewFromMemory(
		DX::pDevice, &MenuImages::Arrow, sizeof(MenuImages::Arrow), NULL, NULL, &pArrow, NULL);
	if (!pSpeedometer) D3DX11CreateShaderResourceViewFromMemory(
		DX::pDevice, &MenuImages::Speedometer, sizeof(MenuImages::Speedometer), NULL, NULL, &pSpeedometer, NULL);

	auto spdMeterSize = ImVec2(443, 259);
	auto arrowSize = ImVec2(192, 215);
	spdMeterSize.x *= 0.25f; spdMeterSize.y *= 0.25f;
	arrowSize.x *= 0.25f; arrowSize.y *= 0.25f;

	auto percValue = (value * 100) / max;

	//from 3.8 to 7.3 
	auto radian = (percValue * (7.3f - 3.8f)) / (100);
	radian += 3.8f;
	radian = std::clamp(radian, 3.8f, 7.3f);

	ImGui::GetBackgroundDrawList()->AddImage(pSpeedometer, pos,
		ImVec2(pos.x + spdMeterSize.x, pos.y + spdMeterSize.y), { 0, 0 }, { 1, 1 }, ImColor::White());

	Renderer::DrawImageRotated(pArrow,
		ImVec2(spdMeterSize.x * 0.5f - arrowSize.x * 0.5f + pos.x, spdMeterSize.y - arrowSize.y * 0.5f + pos.y)
		+ ImVec2(arrowSize.x * 0.5f, arrowSize.y * 0.3f),
		arrowSize, radian, ImColor::White());

	char buf[32];
	sprintf_s(buf, 32, "%d", int(max));

	auto txtSize = ImGui::CalcTextSize(buf);
	Renderer::DrawRectFilled(
		ImVec2(pos.x + spdMeterSize.x * 0.5f - txtSize.x, pos.y + spdMeterSize.y - (txtSize.y * 0.5f) + 15),
		ImVec2(pos.x + spdMeterSize.x * 0.5f + txtSize.x, pos.y + spdMeterSize.y + (txtSize.y * 0.5f + 8) + 15),
		ImColor::Black(190));

	Renderer::DrawString(
		ImVec2(pos.x + spdMeterSize.x * 0.5f, pos.y + spdMeterSize.y - (txtSize.y * 0.5f) + 15),
		StringFlag::CENTER_X, ImColor::Cyan(), "%d", int(value));
};

ImVec2 Renderer::GetTextSize(const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);

	return ImGui::CalcTextSize(buf);
}

void Renderer::DrawCircle(const ImVec2& pos, float rad, float step, const ImColor& color )
{
	ImGui::GetBackgroundDrawList()->AddCircle(pos, rad, (color), step);
}

void Renderer::DrawCircleFilled(const ImVec2& pos, float rad, float step, const ImColor& color )
{
	ImGui::GetBackgroundDrawList()->AddCircleFilled(pos, rad, (color), step);
}

ImVec2 Renderer::GetCursorPos()
{
	return ImGui::GetCursorScreenPos();
}

void Renderer::DrawBox(const std::array<ImVec2, 8>& points, const ImColor& color )
{
	for (int i = 0; i < 3; i++)
		DrawLine(points[i], points[i + 1], color);
	DrawLine(points[3], points[0], color);

	for (int i = 4; i < 7; i++)
		DrawLine(points[i], points[i + 1], color);
	DrawLine(points[7], points[4], color);

	DrawLine(points[1], points[5], color);
	DrawLine(points[2], points[4], color);
	DrawLine(points[0], points[6], color);
	DrawLine(points[3], points[7], color);
}

void Renderer::DrawBox(const ImVec2& center, const ImVec2& size, float angle, const ImColor& color)
{
	std::array<ImVec2, 8> points;
	const ImVec2 s = { size.x * 0.5f, size.y * 0.5f };

	auto RotatePoint = [](ImVec2* point, const ImVec2& origin, float angle) -> void
	{
		float s = sin(angle);
		float c = cos(angle);

		// translate point back to origin:
		point->x -= origin.x;
		point->y -= origin.y;

		// rotate point
		float xnew = point->x * c - point->y * s;
		float ynew = point->x * s + point->y * c;

		// translate point back:
		point->x = xnew + origin.x;
		point->y = ynew + origin.y;
	};

	points =
	{
		ImVec2(center.x - s.x, center.y + s.y),
		ImVec2(center.x - s.x, center.y - s.y),
		ImVec2(center.x + s.x, center.y - s.y),
		ImVec2(center.x + s.x, center.y + s.y),

		ImVec2(center.x + s.x, center.y - s.y),
		ImVec2(center.x - s.x, center.y - s.y),
		ImVec2(center.x - s.x, center.y + s.y),
		ImVec2(center.x + s.x, center.y + s.y),
	};

	for (auto& it : points)
		RotatePoint(&it, center, angle);

	DrawBox(points, color);
}

BoundingBox::BoundingBox(const float left, const float top, const float right, const float bot)
{
	this->left = left;
	this->bot = bot;
	this->right = right;
	this->top = top;
}

BoundingBox::BoundingBox(const ImVec2& min, const ImVec2& max)
{
	this->left = min.x;
	this->top = min.y;
	this->right = max.x;
	this->bot = max.y;
}

BoundingBox BoundingBox::Zero() { return BoundingBox(0.f, 0.f, 0.f, 0.f); }

ImVec2 BoundingBox::GetMin() const { return ImVec2(left, top); }

ImVec2 BoundingBox::GetMax() const { return ImVec2(right, bot); }

ImVec2 BoundingBox::GetMinBot() const { return ImVec2(left, bot); }

ImVec2 BoundingBox::GetMaxTop() const { return ImVec2(right, top); }

ImVec2 BoundingBox::GetSize() const { return ImVec2(fabsf(right - left), fabsf(bot - top)); }

ImVec2 BoundingBox::GetCenter() const { return ImVec2(GetSize().x / 2.f, GetSize().y / 2.f); }

bool BoundingBox::IsValid() const { return *this != 0.f; }
