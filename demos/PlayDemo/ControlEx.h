#pragma once
#include <iostream>

class CWndUI : public CControlUI
{
	DECLARE_DUICONTROL(CWndUI)
public:
	CWndUI()
	{
		std::cout << "CWndUI Created" << std::endl;
	}

	LPCTSTR GetClass() const
	{
		return _T("Wnd");
	}
public:
	void Attach(HWND hWnd)
	{
		m_hWnd = hWnd;
		AdjustPos();
	}

	HWND Detach()
	{
		HWND hWnd = m_hWnd;
		m_hWnd = NULL;
		return hWnd;
	}

	virtual void SetVisible(bool bVisible = true)
	{
		CControlUI::SetVisible(bVisible);
		AdjustPos();
	}

	virtual void SetInternVisible(bool bVisible = true)
	{
		CControlUI::SetInternVisible(bVisible);
		AdjustPos();
	}

	virtual void SetPos(RECT rc, bool bNeedInvalidate /* = true */)
	{
		CControlUI::SetPos(rc, bNeedInvalidate);
		AdjustPos();
	}

	void AdjustPos()
	{
		if (::IsWindow(m_hWnd)) {
			if (m_pManager) {
				RECT rcItem = m_rcItem;
				if (!::IsChild(m_pManager->GetPaintWindow(), m_hWnd)) {
					RECT rcWnd = { 0 };
					::GetWindowRect(m_pManager->GetPaintWindow(), &rcWnd);
					::OffsetRect(&rcItem, rcWnd.left, rcWnd.top);
				}
				SetWindowPos(m_hWnd, NULL, rcItem.left, rcItem.top, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top, SWP_NOACTIVATE | SWP_NOZORDER);
			}
			ShowWindow(m_hWnd, IsVisible() ? SW_SHOW : SW_HIDE);
		}
	}

protected:
	HWND m_hWnd;
};