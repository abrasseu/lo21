QT += core gui widgets

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
	interface/interf.cpp \
#	interface/inter_1d.cpp \
	interface/inter_2d.cpp \
	interface/SimulatorInterface.cpp \
    interface/HomeView.cpp

HEADERS += \
	autocell/Cell.h \
	autocell/Rule.h \
	autocell/Simulator.h \
	autocell/Simulator1D.h \
	autocell/Simulator2D.h \
	autocell/SimulatorLifeGame.h \
	autocell/State.h \
	autocell/SimulatorManager.h \
	interface/inclu_fich.h \
	interface/interf.h \
#	interface/inter_1d.h \
	interface/inter_2d.h \
	interface/SimulatorInterface.h \
    interface/HomeView.h