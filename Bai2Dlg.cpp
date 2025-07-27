
// Bai2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Bai2.h"
#include "Bai2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBai2Dlg dialog

BEGIN_DHTML_EVENT_MAP(CBai2Dlg)
	DHTML_EVENT_ONCLICK(_T("add"), OnButtonAdd)
	DHTML_EVENT_ONCLICK(_T("edit"), OnButtonEdit)
	DHTML_EVENT_ONCLICK(_T("remove"), OnButtonEdit)
END_DHTML_EVENT_MAP()


CBai2Dlg::CBai2Dlg(CWnd* pParent /*=nullptr*/)
	: CDHtmlDialog(IDD_BAI2_DIALOG, IDR_HTML_BAI2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBai2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBai2Dlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CBai2Dlg message handlers

BOOL CBai2Dlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	//CComPtr<IHTMLDocument2> sPDoc = GetDHtmlDocument(); 



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBai2Dlg::OnDocumentComplete(LPDISPATCH lpDis, LPCTSTR pStr)
{
	CComPtr<IHTMLDocument2> sPDoc; 
	GetDHtmlDocument(&sPDoc); 

	CComPtr<IHTMLElement> sPEle;
	GetElement(_T("table"), &sPEle); // Lấy ID và truyền vào smart pointer element

	// smart poiter table
	CComPtr<IHTMLTable> sPTab;
	CComPtr<IHTMLTableRow> sPRow;
	// query interface 
	sPTab.Release(); 
	sPEle->QueryInterface(IID_IHTMLTable, (void**)(&sPTab.p)); 

	// create a new row
	sPRow.Release(); 
	sPTab->insertRow( -1, (IDispatch**)(&sPRow.p));

	CComPtr<IHTMLTableCell> sPCell;

	CComPtr<IHTMLElement> sPElement;


	for (int i = 0; i < 8; i++)
	{
		// create 8 cell 
		sPCell.Release(); 
		sPElement.Release(); 
		sPRow->insertCell(-1, (IDispatch**)&sPCell.p);
		// QueryInterface;
		sPCell->QueryInterface(IID_IHTMLElement, (void**)(&sPElement)); 
		CString cStr = _T("Le Thanh Nam"); 
		CComBSTR sPstr(cStr); 
		sPElement->put_innerText(sPstr);
	}



}

void CBai2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBai2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBai2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CBai2Dlg::OnButtonAdd(IHTMLElement* /*pElement*/)
{
	CInputDialog dlg; 
	if (dlg.DoModal() == IDOK)
	{

	}
	return S_OK;
}

HRESULT CBai2Dlg::OnButtonEdit(IHTMLElement* /*pElement*/)
{
	return S_OK;
}
HRESULT CBai2Dlg::OnButtonRemove(IHTMLElement* /*pElement*/) 
{


	return S_OK; 
}

