#include "Header.h"

#include <iostream>
#include <random>
#include "Model.h"
#include "View.h"

int main()
{
	MainView* view = MainView::getObj();
	view->begin();
}