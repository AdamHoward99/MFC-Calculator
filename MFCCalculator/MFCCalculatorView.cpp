
// MFCCalculatorView.cpp : implementation of the CMFCCalculatorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCCalculator.h"
#endif

#include "MFCCalculatorDoc.h"
#include "MFCCalculatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCCalculatorView

IMPLEMENT_DYNCREATE(CMFCCalculatorView, CView)

BEGIN_MESSAGE_MAP(CMFCCalculatorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCCalculatorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCCalculatorView construction/destruction

CMFCCalculatorView::CMFCCalculatorView() noexcept
{
	// TODO: add construction code here

}

CMFCCalculatorView::~CMFCCalculatorView()
{
}

BOOL CMFCCalculatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCCalculatorView drawing

void CMFCCalculatorView::OnDraw(CDC* /*pDC*/)
{
	CMFCCalculatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCCalculatorView printing


void CMFCCalculatorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCCalculatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCCalculatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCCalculatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCCalculatorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCCalculatorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCCalculatorView diagnostics

#ifdef _DEBUG
void CMFCCalculatorView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCCalculatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCCalculatorDoc* CMFCCalculatorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCCalculatorDoc)));
	return (CMFCCalculatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCCalculatorView message handlers
