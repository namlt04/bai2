#pragma once

#include <map>
#ifdef _WIN32_WCE
#error "CDHtmlDialog is not supported for Windows CE."
#endif
#include <string>

// CInputDialog dialog

class CInputDialog : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CInputDialog)

public:
	CInputDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CInputDialog();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_DIALOG, IDH = 103 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	virtual void OnDocumentComplete(LPDISPATCH  lpDispatch, LPCTSTR lpStr);

	std::map<std::string , DISPID> m_pid;
	CComPtr<IDispatch> sPScript;
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
