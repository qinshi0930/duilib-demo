#include "StdAfx.h"
#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////////
///

DUI_BEGIN_MESSAGE_MAP(CMainPage, CNotifyPump)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK, OnItemClick)
DUI_END_MESSAGE_MAP()

CMainPage::CMainPage()
{
	m_pPaintManager = NULL;
}

void CMainPage::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CMainPage::OnClick(TNotifyUI& msg)
{

}

void CMainPage::OnSelectChanged(TNotifyUI& msg)
{

}

void CMainPage::OnItemClick(TNotifyUI& msg)
{

}

//////////////////////////////////////////////////////////////////////////
///
DUI_BEGIN_MESSAGE_MAP(CMainWnd, WindowImplBase)
DUI_END_MESSAGE_MAP()

CMainWnd::CMainWnd()
{
	m_MainPage.SetPaintMagager(&m_pm);
	AddVirtualWnd(_T("mainpage"), &m_MainPage);
}

CMainWnd::~CMainWnd()
{
	CMenuWnd::DestroyMenu();
	RemoveVirtualWnd(_T("mainpage"));
}

CControlUI* CMainWnd::CreateControl(LPCTSTR pstrClass)
{
	//if (lstrcmpi(pstrClass, _T("CircleProgress")) == 0) {
	//	return new CCircleProgressUI();
	//}
	return NULL;
}

void CMainWnd::InitWindow()
{
	//SetIcon(IDR_MAINFRAME);
	// 多语言接口
	CResourceManager::GetInstance()->SetTextQueryInterface(this);
	CResourceManager::GetInstance()->LoadLanguage(_T("lan_cn.xml"));

	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn"))); ASSERT(m_pCloseBtn);
	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn"))); ASSERT(m_pMaxBtn);
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn"))); ASSERT(m_pRestoreBtn);
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn"))); ASSERT(m_pMinBtn);

	//init control pointer
	m_pAreaTitle = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("areaTitle"))); ASSERT(m_pAreaTitle);
	m_pAreaPlay = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("areaPlay"))); ASSERT(m_pAreaPlay);
	m_pAreaCtrl = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("areaCtrl"))); ASSERT(m_pAreaCtrl);

	m_pBtnOpen = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnOpen"))); ASSERT(m_pBtnOpen);
	m_pBtnPlay = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnPlay"))); ASSERT(m_pBtnPlay);
	m_pBtnPause = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnPause"))); ASSERT(m_pBtnPause);
	m_pBtnStop = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnStop"))); ASSERT(m_pBtnStop);
	m_pSliderPlay = static_cast<CSliderUI*>(m_pm.FindControl(_T("sliderPlay"))); ASSERT(m_pSliderPlay);
	m_pBtnBackward = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnBackward"))); ASSERT(m_pBtnBackward);
	m_pBtnForward = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnForward"))); ASSERT(m_pBtnForward);
	m_pBtnMute = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnMute"))); ASSERT(m_pBtnMute);
	m_pBtnMuted = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnMuted"))); ASSERT(m_pBtnMuted);
	m_pSliderVolume = static_cast<CSliderUI*>(m_pm.FindControl(_T("sliderVolume"))); ASSERT(m_pSliderVolume);

	m_pTxtDuration = static_cast<CLabelUI*>(m_pm.FindControl(_T("txtDuration"))); ASSERT(m_pTxtDuration);

	//init mediaplay
	m_player.SetHwnd(m_hWnd);
	ShowPlayBtn();

	// 播放时间显示
	SetTimer(m_hWnd, PROGRESSTIMER, 100, NULL);
}

/////////////////////////////////////////////////////////////////////////

//HRESULT STDMETHODCALLTYPE CMainWnd::UpdateUI(void)
//{
//	return S_OK;
//}
//HRESULT STDMETHODCALLTYPE CMainWnd::GetHostInfo(CWebBrowserUI* pWeb,
//	/* [out][in] */ DOCHOSTUIINFO __RPC_FAR* pInfo)
//{
//	if (pInfo != NULL) {
//		pInfo->dwFlags |= DOCHOSTUIFLAG_NO3DBORDER | DOCHOSTUIFLAG_NO3DOUTERBORDER;
//	}
//	return S_OK;
//}
//HRESULT STDMETHODCALLTYPE CMainWnd::ShowContextMenu(CWebBrowserUI* pWeb,
//	/* [in] */ DWORD dwID,
//	/* [in] */ POINT __RPC_FAR* ppt,
//	/* [in] */ IUnknown __RPC_FAR* pcmdtReserved,
//	/* [in] */ IDispatch __RPC_FAR* pdispReserved)
//{
//	return E_NOTIMPL;
//	//返回 E_NOTIMPL 正常弹出系统右键菜单
//	//返回S_OK 则可屏蔽系统右键菜单
//}

DuiLib::CDuiString CMainWnd::GetSkinFile()
{
	return _T("XML_MAIN");
}

LPCTSTR CMainWnd::GetWindowClassName() const
{
	return _T("MainWnd");
}

UINT CMainWnd::GetClassStyle() const
{
	return CS_DBLCLKS;
}

void CMainWnd::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

LPCTSTR CMainWnd::QueryControlText(LPCTSTR lpstrId, LPCTSTR lpstrType)
{
	CDuiString sLanguage = CResourceManager::GetInstance()->GetLanguage();
	if (sLanguage == _T("en")) {
		if (lstrcmpi(lpstrId, _T("titletext")) == 0) {
			return _T("Duilib Demo v1.1");
		}
		else if (lstrcmpi(lpstrId, _T("hometext")) == 0) {
			return _T("{a}Home Page{/a}");
		}
	}
	else {
		if (lstrcmpi(lpstrId, _T("titletext")) == 0) {
			return _T("Duilib 使用演示 v1.1");
		}
		else if (lstrcmpi(lpstrId, _T("hometext")) == 0) {
			return _T("{a}开源官网{/a}");
		}
	}

	return NULL;
}

void CMainWnd::Notify(TNotifyUI& msg)
{
	CDuiString name = msg.pSender->GetName();
	if (msg.sType == _T("windowinit")) {
	}
	else if (msg.sType == _T("click")) {
		if (msg.pSender == m_pCloseBtn)
		{
			::DestroyWindow(m_hWnd);
			return;
		}
		else if (msg.pSender == m_pMinBtn) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pMaxBtn) {
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pRestoreBtn) {
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			return;
		}
	}
	else if (msg.sType == DUI_MSGTYPE_VALUECHANGED || msg.sType == DUI_MSGTYPE_VALUECHANGED_MOVE)
	{
		OnValueChanged(msg);
	}

	return WindowImplBase::Notify(msg);
}
void CMainWnd::OnClick(TNotifyUI& msg)
{
	CDuiString sCtrlName = msg.pSender->GetName();
	if (msg.pSender == m_pBtnOpen)
	{
		OnOpen();
		return;
	}
	else if (msg.pSender == m_pBtnPause)
	{
		OnPause();
		return;
	}
	else if (msg.pSender == m_pBtnPlay)
	{
		OnPlay();
		return;
	}
	else if (msg.pSender == m_pBtnStop)
	{
		OnStop();
		return;
	}
	else if (msg.pSender == m_pBtnBackward)
	{
		OnBackward();
		return;
	}
	else if (msg.pSender == m_pBtnForward)
	{
		OnForward();
		return;
	}
	else if (msg.pSender == m_pBtnMute)
	{
		OnMute();
		return;
	}
	else if (msg.pSender == m_pBtnMuted)
	{
		OnMute(false);
		return;
	}
	WindowImplBase::OnClick(msg);
}

LRESULT CMainWnd::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	//m_trayIcon.DeleteTrayIcon();
	bHandled = FALSE;
	// 退出程序
	PostQuitMessage(0);
	return 0;
}

LRESULT CMainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg)
	{
	case WM_TIMER:
	{
		lRes = OnTimer(uMsg, wParam, lParam, bHandled);
		break;
	}
	default:
		bHandled = FALSE;
		break;
	}

	if (bHandled)
		return lRes;
	else
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 关闭窗口，退出程序
	if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		bHandled = FALSE;
	}
	else if (uMsg == WM_SHOWWINDOW)
	{
		bHandled = FALSE;
		m_pMinBtn->NeedParentUpdate();
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
	else if (uMsg == WM_SYSKEYDOWN || uMsg == WM_KEYDOWN) {
		int a = 0;
	}
	else if (uMsg == MSG_FFPLAYER) {
		OnFFPlayerMSG(wParam, lParam);
	}

	bHandled = FALSE;
	return 0;
}
LRESULT CMainWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	if (wParam == PROGRESSTIMER)
	{
		if (m_player.IsPlaying())
		{
			LONGLONG position = m_player.GetCurPosition();
			LONGLONG duration = m_player.GetVideoDuration();
			SetTimeText(position, duration);

			m_pSliderPlay->SetValue((int)(position / 1000));
		}

		bHandled = TRUE;
	}

	return 0;
}
void CMainWnd::OnValueChanged(TNotifyUI& msg)
{
	if (msg.pSender == m_pSliderPlay)
	{
		Seek();
	}
	else if (msg.pSender == m_pSliderVolume)
	{
		Volume();
	}
}
//
//LRESULT CMainWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//{
//	bHandled = FALSE;
//	return 0;
//}

void CMainWnd::SetupPlayingUI()
{
	// get desktop workarea,resize window
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	int cx = rect.right - rect.left;
	int cy = rect.bottom - rect.top;

	int TitleHeight = m_pAreaTitle->GetHeight();
	int CtrlHeight = m_pAreaCtrl->GetHeight();
	int width = m_player.GetVideoWidth();
	int height = m_player.GetVideoHeight();
	int width_ = (width <= cx) ? width : cx;
	SIZE szMin = m_pm.GetMinInfo();
	width_ = width_ < szMin.cx ? szMin.cx : width_;
	int height_ = ((height + TitleHeight + CtrlHeight) <= cy) ? (height + TitleHeight + CtrlHeight) : cy;
	height_ = height_ < szMin.cy ? szMin.cy : height_;

	POINT pt = { 0, 0 };
	ClientToScreen(m_hWnd, &pt);
	RECT rc;
	rc.right = (pt.x + width_) > rect.right ? rect.right : (pt.x + width_);
	rc.left = rc.right - width_;
	rc.bottom = (pt.y + height_) > rect.bottom ? rect.bottom : (pt.y + height_);
	rc.top = rc.bottom - height_;
	MoveWindow(m_hWnd, rc.left, rc.top, width_, height_, TRUE);
	RECT displayRect = { 0, TitleHeight, width_, height_ - CtrlHeight };
	m_player.SetDisplayArea(displayRect);

	// setup UI
	m_pSliderPlay->SetMaxValue(static_cast<int>(m_player.GetVideoDuration() / 1000));
	m_pSliderPlay->SetValue(0);
	//m_pLblTitle->SetText(m_player.GetPlayingFileName().GetData());
	//m_pAreaLogo->SetVisible(false);
	ShowPlayBtn(false);
}

void CMainWnd::ShowPlayBtn(bool bShow)
{
	m_pBtnPlay->SetVisible(bShow);
	m_pBtnPause->SetVisible(!bShow);
}

void CMainWnd::OnFFPlayerMSG(WPARAM wParam, LPARAM lParam)
{
	if (wParam == PLAY_COMPLETED)
	{
		LONGLONG position = 0;
		LONGLONG duration = m_player.GetVideoDuration();
		SetTimeText(position, duration);

		m_player.Stop();

		//m_pAreaLogo->SetVisible(true);
		ShowPlayBtn();
		m_pSliderPlay->SetValue(0);
	}
}

void CMainWnd::SetTimeText(LONGLONG position, LONGLONG duration)
{
	CDuiString strTime;
	strTime.Format(_T("%.2I64u:%.2I64u:%.2I64u/%.2I64u:%.2I64u:%.2I64u"),
		position / 1000 / 60 / 60 % 60, position / 1000 / 60 % 60, position / 1000 % 60,
		duration / 1000 / 60 / 60 % 60, duration / 1000 / 60 % 60, duration / 1000 % 60);
	m_pTxtDuration->SetText(strTime);
}

void CMainWnd::OnOpen()
{
	int nIndex = m_player.GetPlayListCount();
	//open file to play
	vector<CDuiString> vecFileNames;
	if (CFileUtil::OpenFile(L"All\0*.*\0", m_hWnd, vecFileNames))
	{
		m_player.AddToPlayList(vecFileNames);
		if (m_player.Play(nIndex))
			SetupPlayingUI();
	}
}

void CMainWnd::OnPause()
{
	m_player.Pause();

	ShowPlayBtn();
}

void CMainWnd::OnPlay()
{
	if (m_player.IsOpenFile())//continue
	{
		m_player.Play();

		ShowPlayBtn(false);
	}
	else
	{
		if (m_player.Play(m_player.GetCurIndex()))
		{
			//play list
			SetupPlayingUI();
		}
		else
		{
			//play a new file
			OnOpen();
		}
	}
}

void CMainWnd::OnStop()
{
	m_player.Stop();

	m_pSliderPlay->SetValue(0);
}

void CMainWnd::OnForward()
{
	LONGLONG position = m_player.GetCurPosition();
	m_player.Seek(position + 10 * 1000);
}

void CMainWnd::OnBackward()
{
	LONGLONG position = m_player.GetCurPosition();
	m_player.Seek(position - 10 * 1000);
}

void CMainWnd::Seek()
{
	m_player.Seek(m_pSliderPlay->GetValue() * 1000);
}

void CMainWnd::Volume()
{
	m_player.SetAudioVolume(m_pSliderVolume->GetValue() - 182);
}

void CMainWnd::OnMute(bool bMute)
{
	if (bMute)
	{
		// 静音
		m_nAudioVolume = m_player.GetAudioVolume() + 182;
		m_pSliderVolume->SetValue(0);
	}
	else
	{
		// 静音恢复
		m_pSliderVolume->SetValue(m_nAudioVolume);
	}
	m_player.SetAudioVolume(m_pSliderVolume->GetValue() - 182);
	m_pBtnMute->SetVisible(!bMute);
	m_pBtnMuted->SetVisible(bMute);
}
