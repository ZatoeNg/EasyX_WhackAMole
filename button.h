#pragma once

#include <string>
#include <functional>
#include <graphics.h>

class Button
{
private:
	RECT rect;
	std::wstring text;
	bool is_pushed = false;
	bool is_hovered = false;
	std::function<void()> on_click;

public:
	Button(const std::wstring& text,const RECT& rect )
	{
		this->text = text;
		this->rect = rect;
	}

	~Button() = default;

public:
	void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			is_hovered = msg.x >=rect.left && msg.x<= rect.right 
				&& msg.y >= rect.top && msg.y <= rect.bottom;
			break;
		case WM_RBUTTONDOWN:
		case WM_LBUTTONDOWN:
			if (is_hovered)
				is_pushed = true;
			break;
		case WM_RBUTTONUP:
		case WM_LBUTTONUP:
			if (is_pushed && on_click)
				on_click();
			is_pushed = false;
			break;
		default:
			break;
		}
	}

	void on_render()
	{
		setlinecolor(RGB(20, 20, 20));
		if (is_pushed)
			setfillcolor(RGB(185, 185, 185));
		else if (is_hovered)
			setfillcolor(RGB(235, 185, 185));
		else
			setfillcolor(RGB(205, 205, 205));

		fillrectangle(rect.left, rect.top, rect.right, rect.bottom);

		setbkmode(TRANSPARENT);
		settextcolor(RGB(20, 20, 20));
		drawtext(text.c_str(), &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}

	void set_on_click(std::function<void()> on_click)
	{
		this->on_click = on_click;
	}
};