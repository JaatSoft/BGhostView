/****************************************************************************
**
** Name       : AToolBar
** Author     : Andreas Raquet
** Copyright  : (C) 8/23/1998 by Andreas Raquet
** Description: A simple, generic toolbar. Add BViews or AToolBarIcons.
**							Resizing and icon-centering is automatic.
**
** This code is freely distributable under the GNU Public License.
**
*****************************************************************************/
#include "AToolBar.h"

AToolBar::AToolBar( BRect frame, const char *name ) 
  : BView(frame,name,B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP,B_WILL_DRAW) {
	SetViewColor(BeBackgroundGrey);
	rightEdge=2;
};

void AToolBar::AddIcon(char *filename, const char *name, BMessage *msg, bool enabled) {
	AToolBarIcon *icon = new AToolBarIcon(BRect(0,0,10,10), filename, name, msg);
	icon->SetEnabled(enabled);
	AddView(icon);
};

void AToolBar::AddView(BView *view) {
	AddChild(view);
};

void AToolBar::AllAttached() {
	int32 children = CountChildren();
	rightEdge=2;
	for (int i=0; i<children; i++) {
		BView *child = ChildAt(i);
		child->ResizeToPreferred();
		if (child->Bounds().Height()+5>Bounds().Height()) 
			ResizeTo(Bounds().Width(),child->Bounds().Height()+5);};
	for (int i=0; i<children; i++) {
		BView *child = ChildAt(i);
		child->MoveTo(rightEdge+2,(Bounds().Height()-child->Bounds().Height())/2);
		rightEdge+=child->Bounds().Width()+5;
		};
};

void AToolBar::Draw(BRect frame) {
	SetHighColor(White);
	StrokeLine(BPoint(0,Bounds().bottom-1),BPoint(0,0));
	StrokeLine(BPoint(0,0),BPoint(rightEdge+1,0));
	SetHighColor(BeLightShadow);
	StrokeLine(BPoint(1,Bounds().bottom-1),BPoint(rightEdge+2,Bounds().bottom-1));
	StrokeLine(BPoint(rightEdge+2,Bounds().bottom-1),BPoint(rightEdge+2,0));
	SetHighColor(BeShadow);
	StrokeLine(BPoint(0,Bounds().bottom),BPoint(Bounds().right,Bounds().bottom));
};
