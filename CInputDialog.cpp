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


	// Nếu như nó có dữ liệu ban đầu yêu cầu ( tức sửa ) 
	// Đẩy thông tin vào ô nhập
	if (vt_str.size() != 0)
	{
		nlohmann::json j = vt_str;
		std::string strRecord = j.dump(); 
		
		CStringW cStrW(CA2W(strRecord.c_str(), CP_UTF8)); 
		CComVariant cVar(cStrW); 


		CComPtr<IHTMLDocument2> spDoc; 
		GetDHtmlDocument(&spDoc); 

		CComPtr<IDispatch> spScript; 
		spDoc->get_Script(&spScript); 

		OLECHAR* pName = L"onInit"; 
		DISPID pid; 
		spScript->GetIDsOfNames(IID_NULL, &pName, 1, LOCALE_USER_DEFAULT, &pid ); 

		CComVariant result; 
		DISPPARAMS dp = { &cVar, nullptr, 1, 0 }; 
		spScript->Invoke(pid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result, nullptr, nullptr); 


	}

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
	CComPtr<IHTMLDocument2> spDoc; 
	GetDHtmlDocument(&spDoc);
	CComPtr<IDispatch> spScript; 
	spDoc->get_Script(&spScript); 

	OLECHAR* pName = L"onOk"; 
	DISPID pid; 
	spScript->GetIDsOfNames(IID_NULL, &pName, 1, LOCALE_USER_DEFAULT, &pid); 

	DISPPARAMS dp = { nullptr, nullptr, 0, 0 };  // dùng để truyền tham số 
	CComVariant result; 
	spScript->Invoke(pid, IID_NULL,LOCALE_USER_DEFAULT,DISPATCH_METHOD, &dp, &result, nullptr, nullptr);
	if (result.vt == VT_BSTR) // sử dụng == không phải la &
	{
		CStringW cStrW(result.bstrVal);
	
		CW2A utf8str(cStrW, CP_UTF8);
		std::string jsonStr(utf8str);

		if (nlohmann::json::accept(jsonStr)) {
			if (vt_str.size() >= 2)
				vt_str.erase(vt_str.begin() + 2, vt_str.end());
			nlohmann::json j = nlohmann::json::parse(jsonStr);

			for (auto& item : j)
			{
				vt_str.push_back(item.get<std::string>()); 
			}
			CDHtmlDialog::OnOK();

		}
		else {
			// Không hợp lệ, in chuỗi ra MessageBox
			AfxMessageBox(cStrW);
		}
	}
		
	return S_OK;
}

std::vector<std::string> CInputDialog::GetInformation()
{
	return vt_str;
}
void CInputDialog::SetInformation(std::vector<std::string> vt)
{
	// Thiết lập dữ liệu ban đầu 
	for (std::string item : vt)
	{
		vt_str.push_back(item); 
	}

}
HRESULT CInputDialog::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
