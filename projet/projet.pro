QT += core gui widgets uitools

TEMPLATE = app

SOURCES += \
	main.cpp \
	autocell/Cell.cpp \
	autocell/Rule.cpp \
	autocell/Simulator.cpp \
	autocell/Simulator1D.cpp \
	autocell/Simulator2D.cpp \
	autocell/SimulatorLifeGame.cpp \
	autocell/State.cpp \
	autocell/SimulatorManager.cpp \
	interface/qt_designer.cpp \
	interface/interf.cpp \
	interface/inter_1d.cpp \
	interface/inter_2d.cpp

HEADERS += \
	autocell/Cell.h \
	autocell/Rule.h \
	autocell/Simulator.h \
	autocell/Simulator1D.h \
	autocell/Simulator2D.h \
	autocell/SimulatorLifeGame.h \
	autocell/State.h \
	autocell/SimulatorManager.h \
	interface/qt_designer.h \
	interface/inclu_fich.h \
	interface/interf.h \
	interface/inter_1d.h \
	interface/inter_2d.h

FORMS += \
	interface/qt_designer.ui
