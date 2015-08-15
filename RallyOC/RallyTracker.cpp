#include "stdafx.h"
#include "RallyTracker.h"
#include "DogRun.h"

CRallyTracker::CRallyTracker()
{
	// This empty constructor should be used by serialization only
}
void CRallyTracker::DrawTrackerRect( LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd ) {
	if (this->m_size_to_fit) {
		RECT adjust_rect;
		adjust_rect = *lpRect;
		this->ChangeDCToSizeToWindow(pDC,pWnd);
		this->FixRectInFitScreenModeLPtoDP(&adjust_rect,pDC);
		CString rect_dim;
		rect_dim.Format("Top: %d:  Left: %d, Bottom: %d, Right: %d",lpRect->top, lpRect->left, lpRect->bottom, lpRect->right);
		pDC->TextOut(10,40,rect_dim);
		CRectTracker::DrawTrackerRect(&adjust_rect, pWndClipTo, pDC, pWnd);
	}
	else 
		CRectTracker::DrawTrackerRect((RECT*)lpRect, pWndClipTo, pDC, pWnd);
}
void CRallyTracker::ChangeDCToSizeToWindow(CDC* pDC, CWnd* pWnd) {

	CRect window_rect;
	// seting the mode to MM_ISOTROPIC makes the scale x-y same
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetViewportOrg(0, 0);
	pDC->SetWindowOrg(0, 0);
	// The window is the logical size of the course map
	CSize window_extent = pDC->SetWindowExt(m_sizeTotal.cx, m_sizeTotal.cy);

	pWnd->GetClientRect(&window_rect);
	// The viewport is the size of the client window.

	pDC->SetViewportExt(window_rect.right - window_rect.left, window_rect.bottom - window_rect.top);
}
void CRallyTracker::FixRectInFitScreenModeLPtoDP(RECT *rect, CDC *pDC) {
	CPoint top_left, bottom_right;
	RECT new_rect;
	int new_width, new_height;
	int old_width, old_height;
	top_left.x = rect->left;
	top_left.y = rect->top;
	pDC->LPtoDP(&top_left);
	new_rect.left = top_left.x;
	new_rect.top = top_left.y;

	bottom_right.x = rect->right;
	bottom_right.y = rect->bottom;
	pDC->LPtoDP(&bottom_right);
	new_rect.right = bottom_right.x;
	new_rect.bottom = bottom_right.y;

	new_width = new_rect.right - new_rect.left;
	new_height = new_rect.bottom - new_rect.top;

	old_width = rect->right - rect->left;
	old_height = rect->bottom - rect->top;
	rect->left = rect->left + ((old_width - new_width)/2);
	rect->right = rect->left + new_width;
	rect->top = rect->top + ((old_height - new_height)/2);
	rect->bottom = rect->top + new_height;

}