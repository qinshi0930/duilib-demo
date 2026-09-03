#pragma once
#include "ShlObj.h"
#include "ControlEx.h"
#include "MediaPlay.h"

//////////////////////////////////////////////////////////////////////////
///

class CMainPage : public CNotifyPump
{
public:
	CMainPage();

public:
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	DUI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(TNotifyUI& msg);
	virtual void OnSelectChanged(TNotifyUI& msg);
	virtual void OnItemClick(TNotifyUI& msg);

private:
	CPaintManagerUI* m_pPaintManager;
};

//////////////////////////////////////////////////////////////////////////
///

class CMainWnd : public WindowImplBase
{
public:
	CMainWnd();
	~CMainWnd();

	

public:// UI初始化
	virtual DuiLib::CDuiString GetSkinFile() override;
	virtual LPCTSTR GetWindowClassName() const override;
	virtual UINT GetClassStyle() const override;
	virtual void InitWindow() override;
	virtual void OnFinalMessage(HWND hWnd) override;

public:// 系统消息
	//LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

public:// 接口回调
	virtual CControlUI* CreateControl(LPCTSTR pstrClass) override;
	virtual LPCTSTR QueryControlText(LPCTSTR lpstrId, LPCTSTR lpstrType) override;

public:// UI通知消息
	DUI_DECLARE_MESSAGE_MAP()
	virtual void Notify(TNotifyUI& msg) override;
	virtual void OnClick(TNotifyUI& msg) override;

protected:
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void OnValueChanged(TNotifyUI& msg);
	void SetupPlayingUI();
	void ShowPlayBtn(bool bShow = true);
	void OnFFPlayerMSG(WPARAM wParam, LPARAM lParam);
	void SetTimeText(LONGLONG position, LONGLONG duration);
	// 打开文件
	void OnOpen();
	// 暂停播放
	void OnPause();
	// 播放
	void OnPlay();
	// 停止
	void OnStop();
	// 前进
	void OnForward();
	// 后退
	void OnBackward();
	// 播放进度调整
	void Seek();
	// 声音调整
	void Volume();
	// 静音
	void OnMute(bool bMute = true);
	// 窗口总在最前

private:// UI变量
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;

	CHorizontalLayoutUI* m_pAreaTitle;
	CHorizontalLayoutUI* m_pAreaCtrl;
	CHorizontalLayoutUI* m_pAreaPlay;
	CButtonUI* m_pBtnOpen;
	CButtonUI* m_pBtnPlay;
	CButtonUI* m_pBtnPause;
	CButtonUI* m_pBtnStop;
	CSliderUI* m_pSliderPlay;
	CButtonUI* m_pBtnBackward;
	CButtonUI* m_pBtnForward;
	CButtonUI* m_pBtnMute;
	CButtonUI* m_pBtnMuted;
	CSliderUI* m_pSliderVolume;

	CLabelUI* m_pTxtDuration;

	CMediaPlay m_player;
	// 音量
	int m_nAudioVolume;

public:
	CMainPage m_MainPage;
};
