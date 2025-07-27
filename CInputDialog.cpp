// CInputDialog.cpp : implementation file
//

#include "pch.h"
#include "Bai2.h"
#include "CInputDialog.h"


// CInputDialog dialog

IMPLEMENT_DYNCREATE(CInputDialog, CDHtmlDialog)

CInputDialog::CInputDialog(CWnd* pParent /*=nullptr*/)
	: CDHtmlDialog(IDD_INPUT_DIALOG, 103, pParent)
{

}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}
void CInputDialog::OnDocumentComplete(LPDISPATCH  lpDispatch, LPCTSTR lpStr)
{
	CComPtr<IHTMLDocument2> sPDoc;
	GetDHtmlDocument(&sPDoc);

	sPDoc->get_Script(&sPScript);

	OLECHAR* name[] = {L"onOk"};
	DISPID l_disP[1]; 
	sPScript->GetIDsOfNames(IID_NULL, name, 1, LOCALE_USER_DEFAULT, l_disP); 
	m_pid["onOk"] = l_disP[0]; 
}
BOOL CInputDialog::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CInputDialog, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CInputDialog)
	DHTML_EVENT_ONCLICK(_T("okButton"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CInputDialog message handlers

HRESULT CInputDialog::OnButtonOK(IHTMLElement* /*pElement*/)
{
	//OnOK();
	// sau khi an ok thi goi ham onOK javascript
	// doi ket qua tra ve
	DISPPARAMS dp = { nullptr, nullptr, 0, 0 }; 
	VARIANT result; 
	sPScript->Invoke(m_pid["onOk"], IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_METHOD, &dp, &result, nullptr, nullptr);
	if (!(result.vt & VT_ARRAY))
	{
		CStringW cStrW(result.bstrVal); 
		// Đây là 1 String
		AfxMessageBox(cStrW); 
	}
	else
	{
		// Tra ve OnOk
		// luu gia tri vao truoc khi tra ve 
		CDHtmlDialog::OnOK(); 
	}
	
	return S_OK;
}

HRESULT CInputDialog::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
