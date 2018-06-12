#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextBlock>

#include "SimulatorInterface.h"
//#include "inter_1d.h"
#include "inter_2d.h"

using suint = short unsigned int;

class HomeView : public QWidget
{
	Q_OBJECT
	private:
		static const suint nb_automates = 2;

		// Layout
		QVBoxLayout* main_layout;
		QHBoxLayout* automate_layout;
		QVBoxLayout** automate_layouts;

		// Buttons
		QPushButton* quit_bt;
		QPushButton** automate_bts;

		// Labels
		QLabel* title;
		QLabel* subtitle;
		QLabel** automate_titles;
		QLabel** automate_texts;


	public:
		HomeView();
		~HomeView();
	private slots:
		void simulate1D();
		void simulate2D();
};

#endif // HOMEVIEW_H
