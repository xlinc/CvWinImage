
// CvWinImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CvWinImage.h"
#include "CvWinImageDlg.h"
#include "afxdialogex.h"
#include "Utils.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCvWinImageDlg dialog




CCvWinImageDlg::CCvWinImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCvWinImageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCvWinImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCvWinImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_BTN, &CCvWinImageDlg::OnBnClickedLoadBtn)
END_MESSAGE_MAP()


// CCvWinImageDlg message handlers

BOOL CCvWinImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCvWinImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCvWinImageDlg::OnPaint()
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
HCURSOR CCvWinImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCvWinImageDlg::OnBnClickedLoadBtn()
{
	// TODO: Add your control notification handler code here
	CString		ImgFileName;
	//char		szFileters[]="(*.*)|*.*||"; 
	CFileDialog     fileDlg   (TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,NULL,this);   
	if(fileDlg.DoModal()==IDOK)
	{
		ImgFileName=fileDlg.GetPathName();   

		IplImage* image;

		CStringA ImgFileNameA(ImgFileName);
		image=cvLoadImage(ImgFileNameA.GetString());//,CV_LOAD_IMAGE_GRAYSCALE);

		DrawToImageArea(image);
	}
}

void CCvWinImageDlg::DrawToImageArea(IplImage* img)
{
	CDC* imgShow=GetDlgItem(IDC_IMAGE)->GetDC();
	HDC imgDC=imgShow->GetSafeHdc();

	CRect rect;
	GetDlgItem(IDC_IMAGE)->GetClientRect(rect);
	CBrush br(0xf0f0f0f0);
	imgShow->FillRect(rect,&br);

	GetDlgItem(IDC_IMAGE)->GetWindowRect(&rect);

	DrawImgToCtrlsAdaptively(imgDC,img,rect);

	ReleaseDC(imgShow);

}