#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextBlock>

#include "SimulatorInterface.h"

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
        QPushButton* load_automate;

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
        void loadAutomate();
};

#endif // HOMEVIEW_H
