
// ReleaseResourceDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ReleaseResource.h"
#include "ReleaseResourceDlg.h"
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


// CReleaseResourceDlg dialog



CReleaseResourceDlg::CReleaseResourceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RELEASERESOURCE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReleaseResourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CReleaseResourceDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RELEASE_BTN, &CReleaseResourceDlg::OnBnClickedReleaseBtn)
END_MESSAGE_MAP()


// CReleaseResourceDlg message handlers

BOOL CReleaseResourceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	ReleaseRes("��Ů.jpg", (WORD)IDR_JPG1, "jpg");


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReleaseResourceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReleaseResourceDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReleaseResourceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReleaseResourceDlg::OnBnClickedReleaseBtn()
{
	// TODO: Add your control notification handler code here
	if (ReleaseRes("LiBai.txt", (WORD)IDR_TXT2, "TXT")) {
		MessageBox("ጷ��ļ��ɹ�", "��ʾ", MB_OK);
		return;
	}
	MessageBox("ጷ��ļ�ʧ��", "��ʾ", MB_OK);

}

/*
ጷ��YԴ
@param:strFileName
@param:wResID
@param:strFileType
*/
bool CReleaseResourceDlg::ReleaseRes(CString strFileName, WORD wResID, CString strFileType)
{
	// �YԴ��С
	DWORD dwWrite = 0;

	// �����ļ�
	HANDLE hFile = CreateFile(
		strFileName,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	// �����YԴ�ļ�
	HRSRC hrsc = FindResource(NULL, MAKEINTRESOURCE(wResID), strFileType);
	//if (NULL == hrsc) {
	//	MessageBox("�����YԴʧ��", "��ʾ", MB_OK);
	//	return;
	//}

	// �YԴ���d���ڴ�
	HGLOBAL hG = LoadResource(NULL, hrsc);

	// �@ȡ�YԴ��С
	DWORD dwSize = SizeofResource(NULL, hrsc);

	// �����ļ�
	WriteFile(hFile, hG, dwSize, &dwWrite, NULL);

	CloseHandle(hFile);
	return true;
}
